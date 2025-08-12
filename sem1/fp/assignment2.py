"""
    - a menu-driven console application
    - to implement one searching algorithm and two sorting algorithms
    - generate a list of n random natural numbers
    - search for an item in the list
    - sort the list using a sorting algorithm and then the other
    - exit the program

NB!! The search algorithms require a sorted list as input.
In this case, make sure the user first sorted the list before being able to call the search algorithm.
"""

import random

#--- function that generates the list of n random numbers

def generate_nr(nr: int) -> list:
    random_nr = []
    for i in range(nr):
        random_nr.append(random.randint(0, 1000))

    return random_nr


# --- functions that implement program requirements (search & sorting)

#function to sort the list of numbers using the exchange sort algorithm
#iterates through each element starting from the first one
#compares it with all subsequent elements in the list
#after the x-th iteration, on the position x will be the element in its correct sorted position
def exchange_sort(nr_list: list) -> None:
    for i in range(len(nr_list) - 1):
        for j in range(i + 1, len(nr_list)):
            if nr_list[i] > nr_list[j]:
                nr_list[i], nr_list[j] = nr_list[j], nr_list[i]


#function to sort the list of numbers using the shell sort algorithm
#takes a gap, witch is periodically reduced by dividing it by 2
#for each gap, it compares elements that are a 'gap' distance apart
def shell_sort(nr_list: list) -> None:
    gap = len(nr_list) // 2

    while gap > 0:
        j = gap
        while j < len(nr_list):
            i = j - gap
            while i >= 0:

                if nr_list[i] > nr_list[i+gap]:
                    nr_list[i], nr_list[i+gap] = nr_list[i+gap], nr_list[i]
                else:
                    break

                i -= gap
            j += 1
        gap //= 2


#function to search for an element in the list using the exponential search
#finds an interval [exp/2, exp] where the searched element might be found
#applies binary search within the interval [exp/2, exp] to find the exact position of the element
def exponential_search(item: int, nr_list: list) -> int:
    if nr_list[0] == item:
        return 0

    exp = 1
    while exp < len(nr_list) and nr_list[exp] <= item:
        exp *= 2

    left = exp / 2
    right = min(exp, len(nr_list) - 1)

    while left < right:
        mid = int((left + right) // 2)

        if nr_list[mid] == item:
            return mid
        elif nr_list[mid] < item:
            left = mid + 1
        elif nr_list[mid] > item:
            right = mid - 1

    return -1

#--- user interface functions()
#NB! the only place where we are allowed to input and output things

def print_list(nr_list: list) -> None:
    print("List of numbers")
    print(nr_list)

def print_searched_item(item: int, position: int) -> None:
    if position != -1:
        print("number", item, " can be found in the list at the position ", position + 1)
    else:
        print("number", item, " can't be found in the list")

def get_item() -> int:

    while True:
        try:
            item = int(input("What is the number do you want to find in the list? "))
            break
        except ValueError:  # valueerror is the type of error when failing to convert a str to an int
            print("The value introduced must be an integer!")

    return item

def run():

    while True:
        try:
            command = int(input("How long to be the list of the numbers? = "))
            break
        except ValueError:
            print("The value introduced must be an integer!")

    nr_list = generate_nr(command)

    while True:
        print("Choose a task")
        print("0. Exit")
        print("1. Print the list")
        print("2. Sort the list using EXCHANGE SORT")
        print("3. Sort the list using SHELL SORT")
        print("4. Search an item in the list using EXPONENTIAL SEARCH")
        print("!!!To search an item in the list, this should be sorted!!!")

        command = input("*** ")

        if command == "0":
            exit(0)

        elif command == "1":
            print_list(nr_list)

        elif command == "2":
            exchange_sort(nr_list)

        elif command == "3":
            shell_sort(nr_list)

        elif command == "4":
            item = get_item()
            print_searched_item(item,exponential_search(item, nr_list))

        else:
            print("Invalid command")

run()







