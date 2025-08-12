from hotel.TextFile import TextFile
from hotel.board import Reservation, Board


class Service:
    def __init__(self, filename_rooms, filename_reservations):
        self.__repo = TextFile(filename_rooms, filename_reservations)
        self.__board = Board()

    def get_reservations_by_interval(self, start_date, end_date):
        reservations = self.__repo.get_reservations()
        result = []
        # print(reservations)
        for reservation in reservations:
            # print(type(reservation.arrival), type(start_date))
            if reservation.arrival >= start_date and reservation.departure <= end_date:
                result.append(reservation)
                # print(reservation)

        self.__board.monthly_reservations(result)
        return self.__board


