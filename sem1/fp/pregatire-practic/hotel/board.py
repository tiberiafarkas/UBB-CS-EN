from texttable import Texttable

"""
Create a console-based application that helps manage the reservation process in a hotel for 2023. 
The hotel has 5 rooms, numbered from 01 to 05. Rooms can be single rooms (1 person), double rooms (2 persons), or family rooms (4 persons). 
Each Reservation is identified by a unique number and includes the room number, a non-empty name, number of guests, arrival and departure dates.
Display all reservations for a given dd.mm-dd.mm interval (e.g., 25.06-12.07). Reservations are displayed in ascending order of the arrival date. 
Reservations with the same arrival date are sorted in ascending order of the family name. Show each calendar month's reservations in a separate table, 
as shown below. For reservations spanning across a month boundary, display them in all relevant tables

February 2023   Name    Guests
------------------------------
01.02-05.02     John    2
02.18-14.02     Alice   1

Monthly report. Given a month (between 01 - 12), the program will display the 2023 calendar for the given month in tabular form as shown below. 
The header includes the days of the week, according to the actual month of year 2023. 
Each cell includes the date followed by the number of available rooms (e.g., 15/3 means 3 available rooms on the night of February 15th) 

M   T   W   T   F   S   S
--------------------------
       1/5 2/3 3/4 4/5 5/5
6/5 7/5 8/5 9/1 10/1 11/5 12/5
13/5 14/5 15/3 16/5 17/5 18/5 19/2
20/5 21/5 22/5 23/5 24/5 25/5 26/5
27/2 28/2


"""

class Reservation:
    def __init__(self, room, name, guests, arrival, departure):
        self.__room = room
        self.__name = name
        self.__guests = guests
        self.__arrival = arrival
        self.__departure = departure

    @property
    def room(self):
        return self.__room

    @property
    def name(self):
        return self.__name

    @property
    def guests(self):
        return self.__guests

    @property
    def arrival(self):
        return self.__arrival

    @property
    def departure(self):
        return self.__departure

class Board:
    def __init__(self):
        self.__data = {str(i).zfill(2): [] for i in range(1, 13)}
        self.__months = {
            "01": "January",
            "02": "February",
            "03": "March",
            "04": "April",
            "05": "May",
            "06": "June",
            "07": "July",
            "08": "August",
            "09": "September",
            "10": "October",
            "11": "November",
            "12": "December"
        }

    def get_month(self, date):
        return date.split(".")[1]

    def monthly_reservations(self, reservations: list):
        """
        This function format the data to display the reservations between an interval date
        It will contain the month, name and guests of the reservation for the header and the data of the reservation
        with the name of the person and the number of guests for the reservation
        :param reservations:
        :return:
        """
        print(len(reservations))
        for reservation in reservations:
            print(reservation)
            name = reservation.name
            guests = reservation.guests
            date_arrival = reservation.arrival
            date_departure = reservation.departure
            if self.get_month(reservation.arrival) == self.get_month(reservation.departure):
                month = self.get_month(reservation.arrival)
                self.__data[month].append([f"{date_arrival}-{date_departure}", name, f"{guests} guests"])
            else:
                month_arrival = self.get_month(reservation.arrival)
                month_departure = self.get_month(reservation.departure)
                self.__data[month_arrival].append([f"{date_arrival}-{date_departure}", name, f"{guests} guests"])
                self.__data[month_departure].append([f"{date_arrival}-{date_departure}", name, f"{guests} guests"])

        print("something1")
        for month in self.__data:
            print(self.__data[month])

    def __str__(self):
        """
        This function display the reservations in a table format for each month
        month name guests
        date person_name no_guests
        :return:
        """
        t = Texttable()
        result = ""
        for month in self.__data:
            t.add_row([self.__months[month], "Name", "Guests"])
            for data in self.__data[month]:
                t.add_row(data)
                print(data)
            result += t.draw() + "\n"
            t.reset()

        return result

