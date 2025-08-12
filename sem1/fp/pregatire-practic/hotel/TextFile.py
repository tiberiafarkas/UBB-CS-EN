from hotel.board import Reservation


class TextFile:
    def __init__(self, filename_rooms, filename_reservations):
        self.__filename_rooms = filename_rooms
        self.__filename_reservations = filename_reservations
        self.__rooms = {}
        self.__reservations = []
        self.load()

    def get_rooms(self):
        return self.__rooms

    def get_reservations(self):
        return self.__reservations

    def load(self):
        with open(self.__filename_rooms, "r") as f:
            for line in f:
                line = line.strip()
                room_id = int(line[0])
                room_type = line[1]
                self.__rooms[room_id] = room_type

            f.close()

        with open(self.__filename_reservations, "r") as f:
            for line in f:
                line = line.strip()
                parts = line.split(",")
                room_id = int(parts[0])
                name = parts[1]
                guests = int(parts[2])
                arrival = parts[3]
                departure = parts[4]
                self.__reservations.append(Reservation(room_id, name, guests, arrival, departure))

            f.close()