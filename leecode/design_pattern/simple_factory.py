# Parent
class Person:
    def __init__(self):
        self.name = None
        self.gender = None
    
    def getName(self):
        return self.name
    
    def getGender(self):
        return self.gender

# Child
class Male(Person):
    def __init__(self, name):
        print("hello Mr." + name)

# Child
class Female(Person):
    def __init__(self, name):
        print("hello Miss." + name)

# Interface
class Factory:
    def getPerson(self, name, gender):
        if gender == "M":
            return Male(name)
        elif gender == "F":
            return Female(name)
        return None

# User case
if __name__ == "__main__":
    factory = Factory()
    person = factory.getPerson("Henry", "M")
