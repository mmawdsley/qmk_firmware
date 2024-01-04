#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PIL import Image, ImageColor, ImageDraw, ImageFont
from keycodes import KEYCODES
from layout_map import ACTIONS
from argparse import ArgumentParser
from map_generator import LAYOUT_MAP
import json
import os
import sys

class Layout(object):
    """Builds an image of the keyboard layout."""

    KEY_WIDTH = 50
    NUM_COLS = 12
    NUM_ROWS = 6
    KEYBOARD_GUTTER = 10
    TITLE_GUTTER = 80
    IMAGE_PADDING = 10
    KEY_GUTTER = 5
    BOTTOM_OFFSET = 240
    GAP = 100
    BIG_GAP = GAP + 4 * (KEY_WIDTH + KEY_GUTTER)
    ROW_INDENT = round((KEY_WIDTH + KEY_GUTTER) * 2.4)
    ROW_OFFSET = KEY_WIDTH + KEY_GUTTER
    BOTTOM_GAP = 220
    TTF_FONT_PATH = '/usr/share/fonts/truetype/ttf-bitstream-vera/Vera.ttf'
    FONT_SIZE = 10
    OFFSETS = {
        ACTIONS['OFFSET_1']: -round(ROW_OFFSET * 0.636),
        ACTIONS['OFFSET_2']: -round(ROW_OFFSET * 0.986),
        ACTIONS['OFFSET_3']: -round(ROW_OFFSET * 0.636),
        ACTIONS['OFFSET_4']: -round(ROW_OFFSET * 0.60),
    }
    MAX_OFFSET = OFFSETS[max(OFFSETS, key=OFFSETS.get)] * -1
    MIN_OFFSET = OFFSETS[min(OFFSETS, key=OFFSETS.get)] * -1
    LAYER_TITLES = {
        0: 'Base',
        2: 'Raise',
        3: 'Lower',
        4: 'Debug'
    }
    KEYBOARD_WIDTH = KEY_WIDTH * NUM_COLS + (NUM_COLS - 1) * KEY_GUTTER + BIG_GAP
    KEYBOARD_HEIGHT = KEY_WIDTH * NUM_ROWS + (NUM_ROWS - 1) * KEY_GUTTER + MIN_OFFSET

    def __init__(self):
        self.dir = os.path.dirname(os.path.abspath(__file__))
        self.image_key_map = {
            'KC_TRNS': {
                'filename': os.path.join(self.dir, 'transparent.png')
            },
            'KC_NO': {
                'filename': os.path.join(self.dir, 'noop.png')
            }
        }
        self.layout_image = None
        self.key_image = Image.open(os.path.join(self.dir, 'key.png'))
        self.draw = None
        self.color = None
        self.font = None
        self.x = None
        self.y = None
        self.offset = None

    def generate(self, with_base_layers, base_layer, skip_layers):
        """Generate an image of the keyboard layout."""

        with open('keymap.json', 'r') as f:
            keyboard = json.loads(f.read())

        layers = keyboard['layers']
        layer_count = len(layers) - len(skip_layers)

        if with_base_layers:
            layer_count = layer_count - with_base_layers + 1

            for layer_idx in range(0, with_base_layers):
                if layer_idx != base_layer:
                    skip_layers.append(layer_idx)

        image_width = Layout.KEYBOARD_WIDTH + Layout.IMAGE_PADDING * 2
        image_height = Layout.KEYBOARD_HEIGHT * layer_count \
            + (layer_count - 1) * Layout.KEYBOARD_GUTTER \
            + Layout.IMAGE_PADDING * 2 \
            + layer_count * Layout.TITLE_GUTTER \
            - Layout.MAX_OFFSET

        self.layout_image = Image.new('RGB', (image_width, image_height), color = 'white')

        for keycode in self.image_key_map:
            self.image_key_map[keycode]['image'] = Image.open(self.image_key_map[keycode]['filename'])

        self.draw = ImageDraw.Draw(self.layout_image)
        self.color = ImageColor.getrgb("#ff0000")
        self.font = ImageFont.truetype(Layout.TTF_FONT_PATH, Layout.FONT_SIZE)

        self.x = Layout.IMAGE_PADDING
        self.y = Layout.IMAGE_PADDING
        self.offset = 0

        for layer_idx in list(i for i in range(0, len(keyboard['layers'])) if i not in skip_layers):
            text = Layout.LAYER_TITLES[layer_idx]
            layer = keyboard['layers'][layer_idx]

            _, _, text_width, _ = self.draw.textbbox((0, 0), text)
            text_x = image_width / 2 - text_width / 2

            self.draw.text((text_x, self.y), text, fill=(0,0,0,128), font=self.font, align='center')
            self.y += Layout.TITLE_GUTTER

            key_idx = 0

            for text in layer:
                actions = LAYOUT_MAP[key_idx]
                key_idx += 1

                self._draw_key(self.x, self.y + self.offset, text)
                self._process_actions(actions)

            self.x = Layout.IMAGE_PADDING
            self.y += Layout.KEYBOARD_GUTTER + Layout.KEY_WIDTH + Layout.KEY_GUTTER

        self.layout_image.save(os.path.join(self.dir, 'layout.png'))

    def _process_actions(self, actions):
        """Modify the x, y, and offset variables based on the actions."""

        self.offset = 0

        if actions & ACTIONS['END']:
            self.x = Layout.IMAGE_PADDING
            self.y += Layout.KEY_WIDTH + Layout.KEY_GUTTER
        if actions & ACTIONS['KEY']:
            self.x += Layout.KEY_WIDTH + Layout.KEY_GUTTER
        if actions & ACTIONS['GAP']:
            self.x += Layout.KEY_WIDTH + Layout.GAP
        if actions & ACTIONS['BIG_GAP']:
            self.x += Layout.KEY_WIDTH + Layout.BIG_GAP
        if actions & ACTIONS['BOTTOM_GAP']:
            self.x += Layout.BOTTOM_GAP
        if actions & ACTIONS['BOTTOM_OFFSET']:
            self.x += Layout.BOTTOM_OFFSET
        if actions & ACTIONS['ROW']:
            self.x += Layout.ROW_INDENT

        for offset in Layout.OFFSETS:
            if actions & offset:
                self.offset = Layout.OFFSETS[offset]

    def _draw_key(self, x, y, keycode):
        """Draw the keyboard at the given coordinates."""

        self.layout_image.paste(self.key_image, (x, y))

        try:
            text_width, text_height = self.image_key_map[keycode]['image'].size
            text_x = int(x + Layout.KEY_WIDTH / 2 - text_width / 2)
            text_y = int(y + Layout.KEY_WIDTH / 2 - text_height / 2)

            self.layout_image.paste(self.image_key_map[keycode]['image'], (text_x, text_y))
        except KeyError:
            try:
                text = KEYCODES[keycode]
            except KeyError:
                text = keycode

            _, _, text_width, text_height = self.draw.textbbox((0, 0), text)
            text_x = x + Layout.KEY_WIDTH / 2 - text_width / 2
            text_y = y + Layout.KEY_WIDTH / 2 - text_height / 2

            self.draw.text((text_x, text_y), text, fill=(0,0,0,128), font=self.font, align='center')

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument('--with-base-layers', help='number of base layers', type=int)
    parser.add_argument('--base-layer', help='base layer ID', type=int)
    parser.add_argument('--skip-layers', help='IDs of layers to skip', type=str)

    args = parser.parse_args()

    if args.with_base_layers and args.base_layer is None:
        print("Base layer ID is required when managing base layers\n")
        parser.print_help()
        sys.exit(1)

    try:
        skip_layers = args.skip_layers.split(",")
    except AttributeError:
        skip_layers = []

    try:
        skip_layers = [int(layer_idx) for layer_idx in skip_layers]
    except ValueError:
        print("Skip layers can only be numbers\n")
        sys.exit(1)

    Layout().generate(args.with_base_layers, args.base_layer, skip_layers)
