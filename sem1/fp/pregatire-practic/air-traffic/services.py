from src.domain import Flights


class Service:
    def __init__(self, text_repo, validator):
        self.__text_repo = text_repo
        self.__validator = validator

    def add_flight(self, identifier, departure_city, departure_time, arrival_city, arrival_time):
        """
        Function that adds a flight to the list of flights
        :param identifier:
        :param departure_city:
        :param departure_time:
        :param arrival_city:
        :param arrival_time:
        :return:
        """

        flight = Flights(identifier, departure_city, departure_time, arrival_city, arrival_time)
        self.__validator.validate_flight(flight)
        self.__text_repo.add_flight(flight)

    def delete_flight(self, identifier):
        self.__text_repo.delete_flight(identifier)

    def get_flights(self):
        return self.__text_repo.get_flights()

    def airports_sorted(self):
        flights = self.get_flights()
        airports = {}
        for flight in flights:
            if flight.departure_city not in airports:
                airports[flight.departure_city] = 0
            if flight.arrival_city not in airports:
                airports[flight.arrival_city] = 0
            airports[flight.departure_city] += 1
            airports[flight.arrival_city] += 1

        sorted_airports = sorted(airports.items(), key=lambda x: x[1], reverse=True)
        return sorted_airports


