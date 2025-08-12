#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from os import PathLike

from texttable import Texttable

def receive_scores() -> tuple:
    while True:
        try:
            p1 = int(input("p1 = "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    while True:
        try:
            p2 = int(input("p2 = "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    while True:
        try:
            p3 = int(input("p3 = "))
            break
        except ValueError:
            print("The value introduced must be an integer!")
    return p1, p2, p3

def remove_one_participant(participants_list: list, history):
    from functions import remove_participants
    while True:
        try:
            position = int(input("the position at which to remove the participant: "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    remove_participants(participants_list, position, position, history)

def receive_replace_parameters():
    while True:
        try:
            index_participant = int(input("The index of the participant in the list: "))
            break
        except ValueError:
            print("The value introduced must be an integer")

    while True:
        try:
            problem = str(input("The problem for which the score needs to be updated: "))
            break
        except ValueError:
            print("The value introduced must be a string: p1, p2 or p3")

    while True:
        try:
            new_score = int(input("The new score: "))
            break
        except ValueError:
            print("The value introduced must be an integer")

    return index_participant, problem, new_score

def remove_more_participants(participants_list: list, history):
    from functions import remove_participants
    while True:
        try:
            start_position = int(input("remove participants beginning with: "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    while True:
        try:
            end_position = int(input("remove participants until: "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    remove_participants(participants_list, start_position, end_position, history)

def get_position():
    while True:
        try:
            position = int(input("the position at which to insert the participant: "))
            break
        except ValueError:
            print("The input must be an integer!")

    return position

def receive_criteria():
    while True:
        try:
            criteria = str(input("criteria after to show the participants: "))
            criteria.lower()
            break
        except ValueError:
            print("The input must be: =, < or >")

    while True:
        try:
            value = int(input("the comparison number for the average score: "))
            break
        except ValueError:
            print("The input must be an integer!")

    return criteria, value

def display_participants(participants_list, history):
    """
    function to display the participants and all their score
    :return: -
    """
    print(to_str(participants_list))


def to_str(participants_list: list) -> str:
    list_index_width = 5
    index_width = 18
    p1_width = 10
    p2_width = 10
    p3_width = 10

    table = "-" * (list_index_width + index_width + p1_width + p2_width + p3_width + 21) + "\n"
    table += f"| {'List Index':{list_index_width}} | {'index participant':{index_width}} | {'p1':^{p1_width}} | {'p2':^{p2_width}} | {'p3':^{p3_width}} |\n"
    table += "-" * (list_index_width + index_width + p1_width + p2_width + p3_width + 21) + "\n"

    for i, participant in enumerate(participants_list):
        table += f"| {i:>{list_index_width + 5}} | {participant['index']:{index_width}} | {participant['p1']:{p1_width}} | {participant['p2']:{p2_width}} | {participant['p3']:{p3_width}} |\n"

    table += "-" * (list_index_width + index_width + p1_width + p2_width + p3_width + 21)  # Close the table
    return table



def display_to_score(participants_list, history):
    from functions import certain_score
    criteria_participants = certain_score(participants_list)
    print(to_str(criteria_participants))

def display_sorted(participants_list, history):
    from functions import sorted_score
    sorted_list = sorted_score(participants_list)
    #display index of participant, and after that the scores
    print(to_str(sorted_list))

def display_top_participants(participants_list, history):
    from functions import sorted_score
    sorted_list = sorted_score(participants_list)
    top = int(input("From how many participants is made the podium? "))
    print(to_str(sorted_list[:top]))

def receive_top_by_problem():
    while True:
        try:
            problem = str(input("the problem after to sort the participants: "))
            problem.lower()
            break
        except ValueError:
            print("The input must be a string: p1, p2 or p3")

    while True:
        try:
            top = int(input("From how many participants is made the podium?: "))
            break
        except ValueError:
            print("The input must be an integer!")

    return problem, top

def display_top_part_problem(participants_list, history):
    from functions import top_part_problem
    top_problem_participants = top_part_problem(participants_list)
    #display index of the participants, then the rest of the scores
    print(to_str(top_problem_participants))


def print_menu() -> None:
    """
    function to print the menu
    :return: -
    """
    print("0. Exit program")
    print("1. Add the result of a new participant\n"
          "     1.1. Add a new participant\n"
          "     1.2. Insert scores of a participant")
    print("2. Modify scores\n"
          "     2.1. Remove score of one participant\n"
          "     2.2. Remove scores of several participants\n"
          "     2.3. Replace the scored obtain by one participant at a certain problem")
    print("3. Display participants whose score has different properties'\n"
          "     3.1. Display participants and all their scores\n"
          "     3.2. Display participants with a certain average score\n"
          "     3.3. Display participants sorting in a certain order of average score")
    print("4. Establish the podium\n"
          "     4.1. Display top participants\n"
          "     4.2. Display top participants who obtained the highest score at a certain problem\n"
          "     4.3. Remove participants with a certain average score")
    print("5. Undo")
    print("eg: Type 1.1 to add a new participant, if you type 1 or 1.1., the command will not be recognized")


