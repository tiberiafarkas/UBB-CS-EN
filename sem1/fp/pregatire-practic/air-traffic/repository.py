from datetime import datetime

from src.domain import Flights

class DuplicateIdError(Exception):
    def __init__(self, message):
        self.__message = message

    def __str__(self):
        return self.__message

class TextFileRepo:
    def __init__(self, file_name):
        self.__file_name = file_name
        self.__data = []
        self.load_from_file()

    def load_from_file(self):
        try:
            with open(self.__file_name, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    if line != "":
                        line = line.split(",")
                        flight = Flights(line[0], line[1], datetime.strptime(line[2], "%H%M"), line[3], datetime.strptime(line[4], "%H%M"))
                        self.__data.append(flight)
        except FileNotFoundError:
            raise FileNotFoundError("File not found")

    def save_to_file(self):
        with open(self.__file_name, "w") as file:
            for flight in self.__data:
                file.write(str(flight) + "\n")

    def find_by_id(self, identifier):
        for flight in self.__data:
            if flight.id.lower() == identifier.lower():
                return flight
        raise ValueError("Flight not found")

    def add_flight(self, flight):
        if flight.id in [f.id for f in self.__data]:
            raise DuplicateIdError("Duplicate id")

        for f in self.__data:
            if f.departure_time == flight.departure_time and flight.departure_city == f.departure_city:
                raise ValueError("An airport can handle a single operation during each minute")
            if f.arrival_time == flight.arrival_time and flight.arrival_city == f.arrival_city:
                raise ValueError("An airport can handle a single operation during each minute")

        self.__data.append(flight)
        self.save_to_file()

    def delete_flight(self, identifier):
        flight = self.find_by_id(identifier)
        self.__data.remove(flight)
        self.save_to_file()

    def get_flights(self):
        return self.__data
