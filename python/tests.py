#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -*- Python -*-

import msikeyboard
from MSIKeyboard import MSIKeyboard
from MSIKeyboard.exception import MSIKeyboardException
from Region import Region
import os

if __name__ == '__main__':
    regions = msikeyboard.get_regions()
    for region in regions:
        print("Region: %s" % region)

    colors = msikeyboard.get_colors()
    for color in colors:
        print("Color: %s" % color)

    modes = msikeyboard.get_modes()
    for mode in modes:
        print("Mode: %s" % mode)

    intensities = msikeyboard.get_intensities()
    for intensity in intensities:
        print("Intensity: %s" % intensity)

    keyboard = MSIKeyboard(mode="normal")
    keyboard.set_region(Region("left", "white", "high"))
    keyboard.set_region(Region("middle", "white", "high"))
    keyboard.set_region(Region("right", "white", "high"))

    try:
        keyboard.send()
    except MSIKeyboardException as ex:
        print("Unable to send data to MSI keyboard: %s" % ex)
        os._exit(1)

    result = msikeyboard.set_color("left", "purple", "high")
    if result != 0:
        raise Exception("set color failed")