"""
Write a function that generates 1000 pseudo-random reservations for 2023 and writes them to a text-file.
The function will read the room configuration at point 1.
The reservations will be valid, will use real names (have at least 100 different names to choose from,
where name = family + given, e.g., Popescu loan) as well as realistic and different arrival/departure dates.
This functionality is called separately from the program itself, and we will use it to generate input data [1p].
"""
import random
from datetime import datetime

from faker.proxy import Faker

from hotel.ui import UI

file_name = "file.txt"
reservation_file = "reservation.txt"
rooms = {}

def room_configurations():
    with open(file_name, 'r') as f:
        line = f.readlines()
        for i in range(1, 6):
            rooms[i] = line[i-1].split(" ")[1]

        f.close()

def generate_reservations():
    room_configurations()
    fake = Faker()
    with open(reservation_file, 'w') as f:
        for i in range(100):
            room = random.randint(1, 5)
            name = fake.name()
            guests = int(rooms[room])
            arrival = fake.date_this_year(after_today=True)
            departure = fake.date_this_year(after_today=True)
            arrival_formatted = datetime.strptime(str(arrival), '%Y-%m-%d').strftime('%d.%m')
            departure_formatted = datetime.strptime(str(departure), '%Y-%m-%d').strftime('%d.%m')
            f.write(f"{room},{name},{guests},{arrival_formatted},{departure_formatted}\n")

        f.close()

generate_reservations()

if __name__ == "__main__":
    ui = UI(file_name, reservation_file)
    ui.run()