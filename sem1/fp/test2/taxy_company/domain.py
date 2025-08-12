class Taxi:
    def __init__(self, name: str, x: int , y: int):
        self.__name = name
        self.__x = x
        self.__y = y

    @property
    def name(self):
        return self.__name

    @property
    def coordinates(self):
        return self.__x, self.__y

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    def __str__(self):
        return f"{self.__name} - ({self.__x}, {self.__y})"

class Address:
    def __init__(self, id: int, address: str, x: int, y: int):
        self.__id = id
        self.__address = address
        self.__x = x
        self.__y = y

    @property
    def id(self):
        return self.__id

    @property
    def address(self):
        return self.__address

    @property
    def coordinates(self):
        return self.__x, self.__y

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    def __str__(self):
        return f"{self.__address} - ({self.__x}, {self.__y})"
