# class AppleFactory:
#     def create(self) -> Fruit:
#         return Apple()

class AppleFactory:
    def create(self) -> Fruit:
        appleSeed = AppleSeed()
        sunlight = Sunlight()
        water = Water()
        return Apple(appleSeed, sunlight, water)

class PearFactory:
    def create(self) -> Fruit:
        return Pear()

class User:
    def eat(self):
        appleFactory = AppleFactory()
        apple = appleFactory.create()
        pearFactory = PearFactory()
        pear = pearFactory.create()

        apple.eat()
        pear.eat()
        return
