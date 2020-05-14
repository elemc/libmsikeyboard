import msikeyboard
from MSIKeyboard.region import Region
from MSIKeyboard.exception import MSIKeyboardException


class MSIKeyboard(object):
    _regions: dict
    _mode: str

    def __init__(self, mode="", regions: dict = None):
        super(MSIKeyboard, self).__init__()
        if regions is not None:
            self._regions = regions
        else:
            self._regions = dict()
        self._mode = mode

    def set_region(self, region: Region):
        self._regions[region.name] = region

    def send(self):
        if self._mode == "":
            return
        result = msikeyboard.set_mode(self._mode)
        if result != 0:
            raise MSIKeyboardException("unable to set mode, code: %d" % result)

        for region in self._regions:
            if region.color != "":
                result = msikeyboard.set_color(region.name, region.color, region.intensity)
                if result != 0:
                    raise MSIKeyboardException("unable to set color by name, code: %d" % result)
            else:
                result = msikeyboard.set_rgb_color(region.name, region.R, region.G, region.B, region.intensity)
                if result != 0:
                    raise MSIKeyboardException("unable to set color by RGB, code: %d" % result)

