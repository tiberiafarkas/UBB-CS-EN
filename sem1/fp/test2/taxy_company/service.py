from src.repository import TextFileTaxiRepo, TextFileAddressRepo


class Service:
    def __init__(self, taxi_repo, address_repo):
        self._taxi_repo = TextFileTaxiRepo(taxi_repo)
        self._address_repo = TextFileAddressRepo(address_repo)

    @staticmethod
    def distance(x1, y1, x2, y2):
        return abs(x1 - x2) + abs(y1 - y2)

    def get_closest_taxi(self, x, y):
        taxis = self._taxi_repo.get_taxis()
        min_distance = 1000000
        closest_taxi = None
        for taxi in taxis:
            distance = Service.distance(x, y, int(taxi.x), int(taxi.y))
            if distance < min_distance:
                min_distance = distance
                closest_taxi = taxi
        return closest_taxi, min_distance

    def sort_closest_taxi(self):
        addresses = self._address_repo.get_address()
        relative_addresses = []
        for address in addresses:
            closest_taxi, distance = self.get_closest_taxi(address.x, address.y)
            relative_addresses.append((address, closest_taxi, distance))

        relative_addresses.sort(key=lambda item: item[2])
        return relative_addresses

    def sort_taxi_by_name(self):
        taxis = self._taxi_repo.get_taxis()
        taxis.sort(key=lambda taxi: taxi.name)
        return taxis

    def sort_address_by_name(self):
        addresses = self._address_repo.get_address()
        addresses.sort(key=lambda address: address.address)
        return addresses

    def sort_taxi_by_relative_distance(self, x, y):
        taxis = self._taxi_repo.get_taxis()
        taxis.sort(key=lambda taxi: self.distance(taxi.x, taxi.y, x, y))
        return taxis