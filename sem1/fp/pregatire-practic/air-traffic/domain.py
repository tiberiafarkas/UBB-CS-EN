from datetime import datetime


class Flights:
    def __init__(self, identifier, departure_city, departure_time: datetime, arrival_city, arrival_time: datetime):
        self.__id = identifier
        self.__departure_city = departure_city
        self.__departure_time = departure_time
        self.__arrival_city = arrival_city
        self.__arrival_time = arrival_time

    def __str__(self):
        return f"{self.__id},{self.__departure_city},{self.__departure_time},{self.__arrival_city},{self.__arrival_time}"

    @property
    def id(self):
        return self.__id

    @property
    def departure_city(self):
        return self.__departure_city

    @property
    def departure_time(self):
        return self.__departure_time

    @property
    def arrival_city(self):
        return self.__arrival_city

    @property
    def arrival_time(self):
        return self.__arrival_time

class FlightValidator:
    @staticmethod
    def validate_flight(flight):
        errors = []
        if flight.id == "":
            errors.append("Invalid id")
        if flight.departure_city == "":
            errors.append("Invalid departure city")
        if flight.departure_time == "":
            errors.append("Invalid departure time")
        if flight.arrival_city == "":
            errors.append("Invalid arrival city")
        if flight.arrival_time == "":
            errors.append("Invalid arrival time")
        if (flight.arrival_time - flight.departure_time).total_minutes() / 60 < 15 or (flight.arrival_time - flight.departure_time).total_minutes() / 60 > 90:
            errors.append("Invalid flight time length")
        print(type(flight.departure_time), type(flight.arrival_time))
        if flight.departure_time > flight.arrival_time:
            errors.append("Invalid flight time")

        if len(errors) > 0:
            raise ValueError(errors)
