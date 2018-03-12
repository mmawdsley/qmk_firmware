#!/usr/bin/env bash

avrdude -c avr109 -p atmega32u4 -P /dev/ttyACM0 -U flash:w:.build/keebio_nyquist_rev1_default.hex

