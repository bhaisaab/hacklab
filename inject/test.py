import inject

@inject.appscope
class Config(object): pass
class A(object): pass
class B(object): pass

class Controller(object):

    config = inject.attr('config', Config)
    a = inject.attr('a', A)

    @inject.param('b', B)
    def __init__(self, b):
        self.b = b

c = Controller()
