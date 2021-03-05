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

class MaskFactory:
    def create(self, type: str) -> Mask:
        if type == "Surgical":
            return SurgicalMask()
        if type == "N95":
            return N95Mask()

class SurgicalMaskFactory:
    def create(self) -> Mask:
        return SurgicalMask()

class N95MaskFactory:
    def create(self) -> Mask:
        return N95Mask()

# User case
class simpleFactory_Client:
    def test(self):
        factory = MaskFactory()
        print(factory.create("Surgical"))
        print(factory.create("N95"))

class factory_Client:
    def test(self):
        surgicalMaskFactory = SurgicalMaskFactory()
        print(surgicalMaskFactory.create())
        n95MaskFactory = N95MaskFactory()
        print(n95MaskFactory.create())


# simple factory
simpleFactory_Client().test()
# factory
factory_Client().test()
