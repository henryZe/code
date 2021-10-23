class ParkingSystem:

    def __init__(self, big: int, medium: int, small: int):
        self.park = [big, medium, small]

    def addCar(self, carType: int) -> bool:
        if carType > len(self.park):
            return False

        if self.park[carType - 1]:
            self.park[carType - 1] -= 1
            return True
        else:
            return False
