import tempfile
from unittest import TestCase
from unittest.mock import MagicMock

from src.domain import Taxi, Address
from src.repository import TextFileTaxiRepo, TextFileAddressRepo
from src.service import Service


class Tests:
    def __init__(self):
        # Create temporary taxi file
        self.taxi_file = tempfile.NamedTemporaryFile(delete=False, mode="w")
        self.taxi_file.write("Taxi1,3,3\nTaxi2,5,5\nTaxi3,1,1\n")
        self.taxi_file.close()

        # Create temporary address file
        self.address_file = tempfile.NamedTemporaryFile(delete=False, mode="w")
        self.address_file.write("1,Home,2,2\n2,Work,6,6\n")
        self.address_file.close()

        # Create repositories and service
        self.__test_service = Service(self.taxi_file.name, self.address_file.name)

    def tearDown(self):
        # Clean up temporary files
        import os
        os.remove(self.taxi_file.name)
        os.remove(self.address_file.name)

    def test_distance(self):
        assert self.__test_service.distance(1, 1, 4, 5) == 7
        assert self.__test_service.distance(0, 0, 0, 0) == 0
        assert self.__test_service.distance(5, 5, 10, 10) == 10

    def test_get_closest_taxi(self):
        closest_taxi, distance = self.__test_service.get_closest_taxi(2, 2)
        assert closest_taxi.name == "Taxi1"
        assert distance == 2

    def test_sort_taxi_by_name(self):
        sorted_taxis = self.__test_service.sort_taxi_by_name()
        sorted_names = [taxi.name for taxi in sorted_taxis]
        assert sorted_names == ["Taxi1", "Taxi2", "Taxi3"]

    def test_sort_address_by_name(self):
        sorted_addresses = self.__test_service.sort_address_by_name()
        sorted_names = [address.address for address in sorted_addresses]
        assert sorted_names == ["Home", "Work"]

    def test_sort_taxi_by_relative_distance(self):
        sorted_taxis = self.__test_service.sort_taxi_by_relative_distance(2, 2)
        sorted_name = [taxi.name for taxi in sorted_taxis]
        assert sorted_name == ["Taxi1", "Taxi3", "Taxi2"]

    def run(self):
        self.test_distance()
        self.test_get_closest_taxi()
        self.test_sort_taxi_by_name()
        self.test_sort_address_by_name()
        self.test_sort_taxi_by_relative_distance()

Tests().run()





