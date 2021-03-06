import abc

class IFactory:
    @abc.abstractmethod
    def create(self) -> Fruit:
        pass

class AppleFactory(IFactory):
    def create(self) -> Fruit:
        return Apple()

class User:
    def eat(self):
        appleFactory = AppleFactory()
        apple = appleFactory.create()
        apple.eat()
