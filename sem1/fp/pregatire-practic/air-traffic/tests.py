from unittest import TestCase

from src.domain import FlightValidator
from src.repository import TextFileRepo
from src.services import Service


class Test(TestCase):
    def __init__(self):
        self.__file_name = "test_flights.txt"
        self.__text_repo = TextFileRepo(self.__file_name)
        self.__validator = FlightValidator()
        self.__service = Service(self.__text_repo, self.__validator)
        self.test_add_flight()

    def test_add_flight(self):
        self.__service.add_flight("1", "Cluj", "12:00", "Bucuresti", "14:00")
        flights = self.__service.get_flights()
        assert len(flights) == 1

        try:
            self.__service.add_flight("1", "Bucuresti", "12:00", "Cluj", "14:00")
            self.__service.add_flight("2", "Cluj", "12:00", "Bucuresti", "14:05")
            self.__service.add_flight("3", "Cluj", "12:10", "Bucuresti", "14:00")
            assert False
        except Exception:
            assert True

    def run_tests(self):
        self.test_add_flight()