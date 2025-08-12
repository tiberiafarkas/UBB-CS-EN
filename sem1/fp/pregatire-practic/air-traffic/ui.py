from datetime import time, datetime


class UI:
    def __init__(self, service):
        self.__service = service
        self.__commannds = {
            "1": self.add_flight,
            "2": self.delete_flight,
            "3": self.print_flights,
            "4": self.display_airports_sorted
        }

    def add_flight(self):
        identifier = input("Enter the flight identifier: ")
        departure_city = input("Enter the departure city: ")
        departure_time_str = input("Enter the departure time (HH:MM): ")
        departure_time = datetime.strptime(departure_time_str, "%H:%M").time()
        arrival_city = input("Enter the arrival city: ")
        arrival_time_str = input("Enter the arrival time: ")
        arrival_time = datetime.strptime(arrival_time_str, "%H:%M").time()
        print(type(arrival_time))
        self.__service.add_flight(identifier, departure_city, departure_time, arrival_city, arrival_time)

    def delete_flight(self):
        identifier = input("Enter the flight identifier: ")
        self.__service.delete_flight(identifier)

    def print_flights(self):
        flights = self.__service.get_flights()
        for flight in flights:
            print(flight)

    def display_airports_sorted(self):
        sorted_airports = self.__service.airports_sorted()
        for airport in sorted_airports:
            print(airport)

    def print_menu(self):
        print("1. Add flight")
        print("2. Delete flight")
        print("3. Print flights")
        print("4. Display airports sorted by number of actions")
        print("0. Exit")

    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            if command == "0":
                break
            if command in self.__commannds:
                try:
                    self.__commannds[command]()
                except ValueError as ve:
                    print(ve)
                except Exception as ex:
                    print(ex)
            else:
                print("Invalid command")
