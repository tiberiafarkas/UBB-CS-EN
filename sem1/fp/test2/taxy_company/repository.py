from src.domain import Taxi, Address


class TextFileTaxiRepo:
    def __init__(self, file_name: str):
        self.__file_name = file_name
        self.__taxi = []
        self.__load_file()

    def __load_file(self):
        try:
            with open(self.__file_name, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    name, x, y = line.split(",")
                    taxi = Taxi(name, int(x), int(y))
                    if line != "":
                        self.__taxi.append(taxi)
        except FileNotFoundError:
            raise FileNotFoundError(f"File {self.__file_name} not found")

    def get_taxis(self):
        return self.__taxi

class TextFileAddressRepo:
    def __init__(self, file_name: str):
        self.__file_name = file_name
        self.__address = []
        self.__load_file()

    def __load_file(self):
        try:
            with open(self.__file_name, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    id, address, x, y = line.split(",")
                    address = Address(int(id), address, int(x), int(y))
                    if line != "":
                        self.__address.append(address)
        except FileNotFoundError:
            raise FileNotFoundError(f"File {self.__file_name} not found")

    def get_address(self):
        return self.__address