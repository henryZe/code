import abc

class Mask:
    def __init__(self):
        return
    def __str__(self):
        return self.toString()

class SurgicalMask(Mask):
    def toString(self) -> str:
        return "这是医用口罩"

class N95Mask(Mask):
    def toString(self) -> str:
        return "这是 N95 口罩"

class IFactory:
    @abc.abstractmethod
    def create(self) -> Mask:
        pass

class SurgicalMaskFactory(IFactory):
    def create(self) -> Mask:
        return SurgicalMask()

class N95MaskFactory(IFactory):
    def create(self) -> Mask:
        return N95Mask()

# User case
class Client:
    def test(self):
        surgicalMaskFactory = SurgicalMaskFactory()
        print(surgicalMaskFactory.create())
        n95MaskFactory = N95MaskFactory()
        print(n95MaskFactory.create())


# factory
Client().test()
