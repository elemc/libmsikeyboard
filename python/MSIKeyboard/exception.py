class MSIKeyboardException(Exception):
    _msg: str

    def __init__(self, msg: str = ""):
        super(Exception, self).__init__()
        self._msg = msg

    @property
    def message(self): return self._msg

    def __str__(self): return self.message

