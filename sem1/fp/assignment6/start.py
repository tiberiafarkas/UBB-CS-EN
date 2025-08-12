#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from src.functions import get_command, generate_participants
from src.ui import print_menu


def start():
    participants_list = generate_participants()
    history = []
    while True:
        try:
            print_menu()
            commands = get_command()
            option = input(">>> ")
            if option in commands:
                commands[option](participants_list, history)
            else:
                raise ValueError("Invalid command!")

        except ValueError as ve:
            print(ve)

start()

