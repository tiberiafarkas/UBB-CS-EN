#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
import random

from ui import display_participants, display_to_score, display_sorted, display_top_participants, \
    display_top_part_problem, receive_scores, get_position, remove_one_participant, remove_more_participants, \
    receive_replace_parameters, receive_criteria, receive_top_by_problem
import string

def create_participant_scores(index: int, p1: int, p2: int, p3: int) -> dict:
    """
    function to create a new participant with p1, p2, p3 scores - int values
    :return: a dictionary with the scores
    """
    return { "index": index, "p1": p1, "p2": p2, "p3": p3}

def get_p1(participant: dict) -> int:
    """
    function to get the score of the p1 solved by the participant
    :param participant: participant having the scores p1, p2, p3
    :return: the score of the p1 of the participant
    """
    return participant["p1"]

def get_p2(participant: dict) -> int:
    """
    function to get the score of the p1 solved by the participant
    :param participant: participant having the scores p1, p2, p3
    :return: the score of the p2 of the participant
    """
    return participant["p2"]

def get_p3(participant: dict) -> int:
    """
    function to get the score of the p1 solved by the participant
    :param participant: participant having the scores p1, p2, p3
    :return: the score of the p3 of the participant
    """
    return participant["p3"]

def get_index(participant: dict) -> int:
    """
    function to return the index of the participant
    :param participant: participant having the scores p1, p2, p3
    :return: the index of the participant
    """
    return participant["index"]

def validate_participant(participant: dict):
    """
    function that checks if the scores of the participant are integers between 0 and 10
    :param participant: participant having the scores p1, p2, p3
    :return: -
    :raise: ValueError with message
            "index invalid\n", if index is not valid
            "p1 invalid\n", if p1 is not valid
            "p2 invalid\n", if p2 is not valid
            "p3 invalid\n", if p3 is not valid
    """
    errors = ""
    if get_p1(participant) < 0 or get_p1(participant) > 10 or type(get_p1(participant)) != int:
        errors += "p1 invalid\n"
    if get_p2(participant) < 0 or get_p2(participant) > 10 or type(get_p2(participant)) != int:
        errors += "p2 invalid\n"
    if get_p3(participant) < 0 or get_p3(participant) > 10 or type(get_p3(participant)) != int:
        errors += "p3 invalid\n"
    if len(errors) > 0:
        raise ValueError(errors)


def exit_program(participants_list: list, history):
    """
    function to exit program
    :return: -
    """
    exit(0)

def add_participant(participants_list: list, history: list):
    """
    function to add a new participant with scores for P1, P2, P3
    :param participants_list: a participant with scores p1, p2, p3
    :param history: a list containing all the actions that have been done before
    :return: -
    """
    history.append(participants_list.copy())
    p1, p2, p3 = receive_scores()
    participant = create_participant_scores(len(participants_list), p1, p2, p3)

    try:
        validate_participant(participant)
        participants_list.append(participant)
    except ValueError as ve:
        print(f"Error: {ve}")

def insert_score(participants_list: list, history: list):
    """
    function to insert a list of scores at a certain position
    :param participants_list: a list containing the scores of the participants
    :param history: a list containing all the actions that have been done before
    :return: -
    :raise: ValueError if the position is invalid
    """
    history.append(participants_list.copy())
    position = get_position()
    try:
        if 0 <= position <= len(participants_list):  # Ensure the position is valid
            p1, p2, p3 = receive_scores()
            participant = create_participant_scores(len(participants_list), p1, p2, p3)
            validate_participant(participant)
            participants_list.insert(position, participant)
        else:
            raise ValueError("invalid position!")
    except ValueError as ve:
        print(f"Error: {ve}")

def remove_participants(participants_list: list, start: int, end: int, history):
    """
    function to set the scores of the given participant / more participants to 0
    :param start: from where to start to remove participants
    :param end: where to stop removing participants
    :raise ValueError: raise value error if it's an invalid range
    :return: -
    """
    history.append(participants_list.copy())
    try:
        if 0 <= start <= end < len(participants_list):
            for i in range(start, end + 1):  # Iterate through the range and reset scores
                participants_list[i]["p1"] = 0
                participants_list[i]["p2"] = 0
                participants_list[i]["p3"] = 0
        else:
            raise ValueError("invalid range!")
    except ValueError as ve:
        print(f"Error: {ve}")


def replace_score(participants_list: list, history):
    """
    function to replace the score obtained by a participant at a certain problem
    :return: -
    """
    history.append(participants_list.copy())
    try:
        # Receive the parameters
        index_participant, problem, new_score = receive_replace_parameters()

        # Validate the index
        if index_participant < 0 or index_participant >= len(participants_list):
            raise IndexError(f"Error: Participant {index_participant} does not exist")

        if problem not in ("p1", "p2", "p3"):
            raise ValueError(f"Error: Problem {problem} does not exist")

        if new_score < 0 or new_score > 10:
            raise ValueError(f"Error: Score {new_score} is invalid")

        participants_list[index_participant][problem] = new_score

    except (IndexError, ValueError) as ve:
        # Catching exceptions and printing the error message
        print(ve)

def calculate_average_score(participant: dict):
    """
    function to calculate the average score of a participant
    :param participant: a participant having scores p1, p2, p3
    :return: the average score of the participant
    """
    return (get_p1(participant) + get_p2(participant) + get_p3(participant)) / 3

def certain_score(participants_list: list):
    """
    function to return participants with a certain average score
    :param participants_list: a list containing participants having scores p1, p2, p3
    :return: a list with participants that respect the criteria
    """
    while True:
        criteria, value = receive_criteria()
        try:
            if criteria not in ("=", "<", ">"):
                raise ValueError(f"Invalid criteria: {criteria}. Expected '=', '<', or '>'.")

        except ValueError as ve:
            print(ve)

        try:
            if not (0 <= value <= 10):
                raise ValueError(f"Invalid value: {value}. It must be between 0 and 10.")

        except ValueError as ve:
            print(ve)

        if criteria in ("=", "<", ">") and 0 <= value <= 10:
            break

    criteria_participants = []
    for participant in participants_list:
        average_score = calculate_average_score(participant)
        if criteria == "=":
            if average_score == value:
                criteria_participants.append(participant)
        elif criteria == "<":
            if average_score < value:
                criteria_participants.append(participant)
        elif criteria == ">":
            if average_score > value:
                criteria_participants.append(participant)

    return criteria_participants

def sorted_score(participants_list: list):
    """
    function to sort the average score in decreasing order
    :return: a sorted list of the scores
    """
    sorted_list = sorted(
        participants_list,
        key = lambda participant: calculate_average_score(participant),
        reverse = True
    )
    return sorted_list

def top_part_problem(participants_list: list):
    """
    function to return the top n participants with the highest score for a certain problem
    :return:
    """
    problem, top = receive_top_by_problem()
    function_name = f"get_{problem.lower()}"

    try:
        get_problem_score = globals()[function_name]
    except KeyError:
        raise ValueError(f"Function {function_name} does not exist.")

    top_problem_participants = sorted(
        participants_list,
        key = lambda participant: get_problem_score(participant),
        reverse = True
    )

    return top_problem_participants[:top]

def remove_based_on_average(participants_list: list, history):
    """
    function to set the scores of participants to 0 based on their average score:

    """
    history.append(participants_list.copy())
    while True:
        criteria, value = receive_criteria()
        try:
            if criteria not in ("=", "<", ">"):
                raise ValueError(f"Invalid criteria: {criteria}. Expected '=', '<', or '>'.")

        except ValueError as ve:
            print(ve)

        try:
            if not (0 <= value <= 10):
                raise ValueError(f"Invalid value: {value}. It must be between 0 and 10.")

        except ValueError as ve:
            print(ve)

        if criteria in ("=", "<", ">") and 0 <= value <= 10:
            break

    for i in range(len(participants_list)):
        average_score = calculate_average_score(participants_list[i])

        if criteria == "=":
            if average_score == value:
                remove_participants(participants_list, i, i, history)
        elif criteria == "<":
            if average_score < value:
                remove_participants(participants_list, i, i, history)
        elif criteria == ">":
            if average_score > value:
                remove_participants(participants_list, i, i, history)

def undo(participants_list: list, history):
    """
    Undo the last operation performed on a participant's data.
    :return: -
    """
    if not history:
        print("Error: No actions to undo.")
        raise ValueError("No actions to undo")
    else:
        last_state = history.pop()
        participants_list.clear()
        participants_list.extend(last_state)
        print("Undo successful. The last operation has been reverted.")

def generate_participants():
    participants = []
    for index in range(10):
        p1 = random.randint(0, 10)
        p2 = random.randint(0, 10)
        p3 = random.randint(0, 10)
        participant = {'index': index, 'p1': p1, 'p2': p2, 'p3': p3}
        participants.append(participant)
    return participants

def get_command() -> dict:
    """
    function to create a dictionary with all the commands that can be received from the user
    :return: a dictionary containing the commands
    """
    commands = {
        "0": exit_program,
        "1.1": add_participant,
        "1.2": insert_score,
        "2.1": remove_one_participant,
        "2.2": remove_more_participants,
        "2.3": replace_score,
        "3.1": display_participants,
        "3.2": display_to_score,
        "3.3": display_sorted,
        "4.1": display_top_participants,
        "4.2": display_top_part_problem,
        "4.3": remove_based_on_average,
        "5": undo
    }

    return commands

"""
Section designated to test functions
"""

def tests():
    def test_create_participant_scores():
        index = 1
        p1 = 10
        p2 = 20
        p3 = 30

        participant = create_participant_scores(index, p1, p2, p3)
        assert index == participant["index"]
        assert p1 == participant["p1"]
        assert p2 == participant["p2"]
        assert p3 == participant["p3"]

    def test_validate_participant():
        index = 1
        p1 = 8
        p2 = 7
        p3 = 6
        participant = create_participant_scores(index, p1, p2, p3)
        validate_participant(participant)  # Should pass without exception

        invalid_index = -6
        invalid_p1 = -1
        invalid_p2 = 15
        invalid_p3 = 3.5
        invalid_participant = create_participant_scores(invalid_index, invalid_p1, invalid_p2, invalid_p3)

        try:
            validate_participant(invalid_participant)
            assert False  # Should not reach this line
        except ValueError as ve:
            assert str(ve) == "invalid_index\np1 invalid\np2 invalid\np3 invalid\n"

    def test_undo():
        participants_list = [
            create_participant_scores(1, 10, 2, 3),
            create_participant_scores(2, 5, 2, 5),
            create_participant_scores(3, 2, 3, 4),
        ]
        history = []

        history.append([participant.copy() for participant in participants_list])  # Save current state
        new_participant = create_participant_scores(4, 7, 8, 9)
        participants_list.append(new_participant)

        assert len(participants_list) == 4
        assert participants_list[-1] == new_participant

        history.append([participant.copy() for participant in participants_list])
        removed_participant = participants_list.pop(1)

        assert len(participants_list) == 3
        assert removed_participant["index"] == 2
        assert not any(p["index"] == 2 for p in participants_list)

        undo(participants_list, history)
        assert len(participants_list) == 4
        assert participants_list[1] == removed_participant

        undo(participants_list, history)
        assert len(participants_list) == 3
        assert not any(p["index"] == 4 for p in participants_list)

        try:
            undo(participants_list, history)
            assert False  # Should not reach here
        except ValueError as e:
            assert str(e) == "Error: No actions to undo."

    test_create_participant_scores()
    test_validate_participant()
    test_undo()

#tests()