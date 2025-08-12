from hotel.service import Service


class UI:
    def __init__(self, filename_rooms, filename_reservations):
        self.__service = Service(filename_rooms, filename_reservations)
        self.command = {
            "1": self.display_all_reservations,
            "2": self.create_reservation,
            "3": self.remove_reservation_by_id,
            "4": self.remove_reservation_by_room,
            "5": self.monthly_report,
            "6": self.cancel_reservation
        }

    def print_menu(self):
        print("1. Display all reservations for a given interval")
        print("2. Create a reservation")
        print("3. Remove a reservation by id")
        print("4. Remove a reservation by room")
        print("5. Monthly report")
        print("6. Cancel a reservation")
        print("0. Exit")

    def display_all_reservations(self):
        start_date = input("Enter start date %dd.mm%: ")
        end_date = input("Enter end date %dd.mm%: ")
        reservations = self.__service.get_reservations_by_interval(start_date, end_date)
        print(reservations)

    def create_reservation(self):
        room = int(input("Enter room: "))
        name = input("Enter name: ")
        guests = int(input("Enter number of guests: "))
        arrival = input("Enter arrival date: ")
        departure = input("Enter departure date: ")
        self.__service.add_reservation(room, name, guests, arrival, departure)

    def remove_reservation_by_id(self):
        reservation_id = int(input("Enter reservation id: "))
        self.__service.remove_reservation_by_id(reservation_id)

    def remove_reservation_by_room(self):
        room = int(input("Enter room: "))
        self.__service.remove_reservation_by_room(room)

    def monthly_report(self):
        reservations = self.__service.get_reservations()
        self.__service.monthly_reservations(reservations)
        self.__service.display_monthly_reservations()

    def cancel_reservation(self):
        reservation_id = int(input("Enter reservation id: "))
        self.__service.cancel_reservation(reservation_id)

    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            if command == "0":
                break
            if command in self.command:
                try:
                    self.command[command]()
                except Exception as e:
                    print(e)
            else:
                print("Invalid command")