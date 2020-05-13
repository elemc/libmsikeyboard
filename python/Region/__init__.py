class Region(object):
    _name: str
    _color: str
    _intensity: str
    _r: int
    _g: int
    _b: int

    def __init__(self,
                 name: str = "",
                 color: str = "",
                 intensity: str = "",
                 r: int = 0,
                 g: int = 0,
                 b: int = 0,
                 ):
        super(Region, self).__init__()
        self.name = name
        self.color = color
        self.intensity = intensity
        self.R = r
        self.G = g
        self.B = b

    @property
    def name(self): return self._name

    @name.setter
    def name(self, value: str): self._name = value

    @property
    def color(self): return self._color

    @color.setter
    def color(self, value: str): self._color = value

    @property
    def intensity(self): return self._intensity

    @intensity.setter
    def intensity(self, value: str): self._intensity = value

    @property
    def R(self): return self._r

    @R.setter
    def R(self, value: int): self._r = value

    @property
    def G(self): return self._g

    @G.setter
    def G(self, value: int): self._g = value

    @property
    def B(self): return self._b

    @B.setter
    def B(self, value: int): self._b = value