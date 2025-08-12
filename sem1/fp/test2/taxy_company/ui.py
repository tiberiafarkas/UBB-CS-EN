from src.domain import Address
from src.repository import TextFileAddressRepo
from src.service import Service


class UI:
    def __init__(self):
        self.__taxi_repo = "taxi.txt"
        self.__address_repo = "address.txt"
        self.__service = Service(self.__taxi_repo, self.__address_repo)
        self.command = {
            "1": self.display_address_and_taxi,
            "2": self.sort_taxi_for_address,
            "3": self.closest_taxi,
        }

    def print_menu(self):
        print("1. Display the list of all known addresses and all known taxis")
        print("2. Print the list of drivers sorted by the distance to a given address")
        print("3. Print the closest driver to a given address")
        print("0. Exit")

    def display_address_and_taxi(self):
        taxis = self.__service.sort_taxi_by_name()
        addresses = self.__service.sort_address_by_name()

        print("Taxis:")
        for taxi in taxis:
            print(taxi)

        print("Addresses")
        for address in addresses:
            print(address)

    def get_address(self):
        address = input("Address: ")
        self.validate_address(address)
        id, name_address, x, y = address.split(",")
        address = Address(int(id), name_address, int(x), int(y))
        return address

    def validate_address(self, address):
        try:
            id, name_address, x, y = address.split(",")
            if len(name_address) < 3:
                print("Address name is too short")
                self.get_address()
            int(id)
            int(x)
            int(y)
        except ValueError:
            print("Invalid address! Format address: id, name, x, y")
            self.get_address()

    def sort_taxi_for_address(self):
        address = self.get_address()
        taxis = self.__service.sort_taxi_by_relative_distance(address.x, address.y)

        for taxi in taxis:
            print(taxi)

    def closest_taxi(self):
        relative_addresses = self.__service.sort_closest_taxi()

        for elem in relative_addresses:
            print(f"{elem[0]} -> {elem[1]} - {elem[2]}")


    def run(self):
        while True:
            self.print_menu()
            option = input(">>>")
            if option == "0":
                exit(0)
            if option in self.command:
                self.command[option]()
            else:
                print("invalid option")


if __name__ == "__main__":
    ui = UI()
    ui.run()





