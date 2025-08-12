#
# Functions section
#

"""
Aplicatie de tip consola cu comenzi
-add_candidate 1 gigi - adauga un candidat cu numele gigi si id-ul 1 fara sa apara meniu
idul sa fie unic, numar intreg pozitiv, si numele sa fie string nevid - lucruri validate
-show_candidates - afiseaza toti candidatii
-vote select a random position in the list of candidates and increment the votes for that candidate
-tests for add_candidate and show_candidates and vote
-keep the tiktok_votes separated from the votes but when you print them you print the sum of both
-second round: top 2 candidates sorting descendently by votes
-simulate election(nr of candidates, nr of votes, nr of tiktok votes)
"""
import time
from venv import create
import random


def create_candidate(id, name, candidates):
    if validate_candidate(id, name) and id_exists(id, candidates):
        return {
            "id": id,
            "name": name,
            "votes": 0,
            "tiktok_votes": 0
        }
    else :
        raise ValueError("Invalid candidate")

def validate_candidate(id, name):
    if id < 0 or type(id) != int:
        raise ValueError("Id must be a positive integer")
    if name == "":
        raise ValueError("Name must not be empty")
    return True

def id_exists(id, candidates):
    for candidate in candidates:
        if get_id(candidate) == id:
            raise ValueError("Id already exists")
    return True

def get_id(candidate):
    return candidate["id"]

def get_name(candidate):
    return candidate["name"]

def get_votes(candidate):
    return candidate["votes"]

def get_tiktok_votes(candidate):
    return candidate["tiktok_votes"]

def add_candidate(id, name, candidates):
    try:
        candidate = create_candidate(id, name, candidates)
        candidates.append(candidate)
    except ValueError as ve:
        raise ValueError(ve)

def test_add_candidate():
    candidates = []
    add_candidate(1, "Ciolacu", candidates)
    assert len(candidates) == 1
    assert get_id(candidates[0]) == 1
    assert get_name(candidates[0]) == "Ciolacu"
    assert get_votes(candidates[0]) == 0
    add_candidate(2, "Georgescu", candidates)
    assert len(candidates) == 2
    assert get_id(candidates[1]) == 2
    assert get_name(candidates[1]) == "Georgescu"
    assert get_votes(candidates[1]) == 0
    try:
        add_candidate(-1, "Elena", candidates)
        assert False
    except ValueError as ve:
        assert True
    try:
        add_candidate(3, "", candidates)
        assert False
    except ValueError as ve:
        assert True
    try:
        add_candidate(1, "Ciolacu", candidates)
        assert False
    except ValueError as ve:
        assert True

test_add_candidate()

def generates_candidates():
    candidates = []
    candidates.append(create_candidate(1, "Ciolacu", candidates))
    candidates.append(create_candidate(2, "Georgescu", candidates))
    candidates.append(create_candidate(3, "Elena", candidates))
    candidates.append(create_candidate(4, "Gabi Mircea", candidates))
    return candidates

def vote(candidates):
    candidate = random.choice(candidates)
    candidate["votes"] += 1
    return candidate["id"]

def test_vote():
    candidates = []
    add_candidate(1, "Ciolacu", candidates)
    add_candidate(2, "Georgescu", candidates)
    add_candidate(3, "Elena", candidates)
    vote(candidates)
    vote(candidates)
    count = 0
    for candidate in candidates:
        count += get_votes(candidate)
    assert count == 2

test_vote()

def tiktok_vote(candidates, id, tiktok_votes):
    if valid_id(id, candidates) and valid_votes(tiktok_votes):
        for candidate in candidates:
            if get_id(candidate) == id:
                candidate["tiktok_votes"] += tiktok_votes

def valid_id(id, candidates):
    if id < 0 or type(id) != int:
        raise ValueError("Id must be a positive integer")
    for candidate in candidates:
        if get_id(candidate) == id:
            return True

    raise ValueError("Id does not exist")

def valid_votes(votes):
    if votes < 0 or type(votes) != int:
        raise ValueError("Votes must be a positive integer")
    return True

def test_tiktok_vote():
    candidate = create_candidate(1, "Ciolacu", [])
    tiktok_vote([candidate], 1, 2)
    assert get_tiktok_votes(candidate) == 2
    try:
        tiktok_vote([candidate], 2, 100)
        assert False
    except ValueError as ve:
        assert True

test_tiktok_vote()

def sort_candidates(candidates):
    return sorted(candidates, key=lambda candidate: get_tiktok_votes(candidate)/get_votes(candidate) if get_votes(candidate) != 0 else 0, reverse = True)

def test_sort_candidates():
    candidates = []
    add_candidate(1, "Ciolacu", candidates)
    add_candidate(2, "Georgescu", candidates)
    add_candidate(3, "Elena", candidates)
    add_candidate(4, "Gabi Mircea", candidates)
    candidates[0]["votes"] = 1
    candidates[1]["votes"] = 100
    candidates[2]["votes"] = 1000
    candidates[3]["votes"] = 1
    tiktok_vote(candidates, 1, 210)
    tiktok_vote(candidates, 2, 300)
    tiktok_vote(candidates, 3, 100)
    tiktok_vote(candidates, 4, 599)
    sorted_candidates = sort_candidates(candidates)
    assert get_id(sorted_candidates[0]) == 4
    assert get_id(sorted_candidates[1]) == 1
    assert get_id(sorted_candidates[2]) == 2
    assert get_id(sorted_candidates[3]) == 3

test_sort_candidates()

def simulate_election(nr_candidates, nr_votes, nr_tiktok_votes):
    time.sleep(1)
    print("Dragi romani, tineti-va bine, incep alegerile! - SA CASTIGE CEL MAI SMECHER SAU CEL MAI PROST!")
    print("--------------------------------------------------------------------------------------------->")
    print()
    candidates = []
    time.sleep(1)
    while len(candidates) < nr_candidates:
        while True:
            index = random.randint(0, 15)
            if index not in [get_id(candidate) for candidate in candidates]:
                break
        #index = random.randint(0, 15)
        name = random.choice(["Gabi Mircea", "Marcel Ciolacu", "Calin Georgescu", "Elena Lasconi", "George Simion", "Mircea Geoana", "Diana Sosoaca"])
        if name not in [get_name(candidate) for candidate in candidates]:
            candidates.append(create_candidate(index, name, candidates))
            print(f"-> Candidatul {name} cu id-ul {index} intra in cursa pentru titlul de PRESIDENT EXPERT DOBITOC!")
            time.sleep(1)

    print()
    print("--------------------------------------------------------------------------------------------->")
    for i in range(nr_votes):
        index = vote(candidates)
        for candidate in candidates:
            if get_id(candidate) == index:
                print(f"*** S-a inregistrat un vot pentru nimeni altul decat {get_name(candidate)}!!! ***")
                time.sleep(0.5)
                break

    print()
    print("-------------------------------------------------------------------------------------------------------->")
    print("Noaptea a venit, cetatenii s-au culcat, DAR TIKTOKERI S-AU TREZIT, iar voturile au inceput sa curga.....")
    print("-------------------------------------------------------------------------------------------------------->")
    print()

    for i in range(nr_tiktok_votes):
        while True:
            index = random.randint(0, 15)
            if index in [get_id(candidate) for candidate in candidates]:
                break
        tiktok_votes = random.randint(0, 1000)
        tiktok_vote(candidates, index, tiktok_votes)
        for candidate in candidates:
            if get_id(candidate) == index:
                print(f"Un numar divin de {tiktok_votes} tiktokuri voturi s-au inregistrat pentru {get_name(candidate)} printr-un miracol Dumnezeiesc!")
                time.sleep(0.5)

    print()
    print("--------------------------------------------------------------------------------------------------------->")
    print("Cei 2 norocosi calificati in turul 2 al alegerilor, dupa multe pacturi spirituale sunt:")
    print("--------------------------------------------------------------------------------------------------------->")
    print()
    print_top_candidates(candidates)

#
# User interface section
#

def show_candidates(candidates):
    for candidate in candidates:
        print(f"{get_id(candidate)} {get_name(candidate)} {get_votes(candidate) + get_tiktok_votes(candidate)}")

def print_top_candidates(candidates):
    sorted_candidates = sort_candidates(candidates)
    print("Top candidates:")
    print(f"First candidate: {get_id(sorted_candidates[0])} {get_name(sorted_candidates[0])} with {get_votes(sorted_candidates[0])} votes and {get_tiktok_votes(sorted_candidates[0])} tik tok votes")
    print(f"Second candidate: {get_id(sorted_candidates[1])} {get_name(sorted_candidates[1])} with {get_votes(sorted_candidates[1])} votes and {get_tiktok_votes(sorted_candidates[1])} tik tok votes")

def main():
    candidates = generates_candidates()
    while True:
        try:
            command = input("Command: ")
            parts = command.strip().split()
            option = parts[0]
            #show_candidates(candidates)
            if option == "add_candidate":
                id = int(parts[1])
                name = parts[2]
                add_candidate(id, name, candidates)
            elif option == "show_candidates":
                show_candidates(candidates)
            elif option == "exit":
                exit(0)
            elif option == "vote":
                vote(candidates)
            elif option == "tiktok_vote":
                id = int(parts[1])
                votes = int(parts[2])
                tiktok_vote(candidates, id, votes)
            elif option == "print_top_candidates":
                print_top_candidates(candidates)
            elif option == "simulate_election":
                nr_candidates = int(parts[1])
                nr_votes = int(parts[2])
                nr_tiktok_votes = int(parts[3])
                simulate_election(nr_candidates, nr_votes, nr_tiktok_votes)
            else:
                print("Invalid command")
        except ValueError as ve:
            print(ve)

main()