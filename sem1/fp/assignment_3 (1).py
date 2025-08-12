"""
    - a menu-driven console application
    - to implement one searching algorithm and two sorting algorithms
    - generate a list of n random natural numbers
    - search for an item in the list
    - sort the list using a sorting algorithm and then the other
    - compute the best, the average and the worst case for the implemented algorithms
    - the program will time and illustrate the runtime of the algorithms for 5 data structures (each having twice the nr of elements of the previous)
    - exit the program

"""

import timeit
from random import *
from datetime import *
from texttable import Texttable

#function to generate a list for the average case when it comes to shell sort
def random_sorted(length: int) -> list:
    nr_list = list(range(length))
    shuffle(nr_list)
    return nr_list

#function to generate a list for the best case when it comes to shell sort
def already_sorted(length: int) -> list:
    return list(range(0, length))

#function to generate a list for the worst case when it comes to shell sort
def sorted_in_reverse(length: int) -> list:
    return list(range(length, 0, -1))


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

#T(n) = log_2(n) * (2n-1) = 2n * log_2(n) - log_2(n) => Theta(nlogn)
def shell_sort(nr_list: list) -> None:
    gap = len(nr_list) // 2
    # let take n = length of nr_list
    while gap > 0:  # runs log_2(n) times
        j = gap
        while j < len(nr_list):  # n/2 + n/4 + n/8 + ... + 1 = (q^n-1)/(q-1) (geometric progression) = 2n-1 => O(n)
            i = j - gap
            while i >= 0:
                # the worst case happens when the condition nr_list[i] > nr_list[i+gap] is true multiple times
                if nr_list[i] > nr_list[i + gap]:
                    nr_list[i], nr_list[i + gap] = nr_list[i + gap], nr_list[i]
                else:
                    break

                i -= gap
            j += 1
        gap //= 2


#function to search for an element in the list using the exponential search
#finds an interval [exp/2, exp] where the searched element might be found
#applies binary search within the interval [exp/2, exp] to find the exact position of the element
def exponential_search(nr_list: list, item: int) -> tuple:
    if nr_list[0] == item:
        return item, 0

    exp = 1
    while exp < len(nr_list) and nr_list[exp] <= item:
        exp *= 2

    left = exp / 2
    right = min(exp, len(nr_list) - 1)

    while left <= right:
        mid = int((left + right) // 2)

        if nr_list[mid] == item:
            return item, mid
        elif nr_list[mid] < item:
            left = mid + 1
        elif nr_list[mid] > item:
            right = mid - 1

    return item, -1

#function to build the table that will illustrate the runtime of the exponential_search
def build_result_table(algorithms: list, list_lengths: list):
    table = Texttable()
    table.add_row(['algorithm'] + list_lengths)

    for algorithm in algorithms:
        table_row = [algorithm.__name__]
        for list_length in list_lengths:
            data = already_sorted(list_length)
            t1 = timeit.default_timer()
            # (list_length // 2) is at the middle of the list
            algorithm(data, list_length//2)
            t2 = timeit.default_timer()
            table_row.append(t2 - t1)
        table.add_row(table_row)
    return table

if __name__ == "__main__":
    list_lengths = [1000, 2000, 4000, 8000, 16000]
    algorithms = [exponential_search]
    print(build_result_table(algorithms, list_lengths).draw())

#function to calculate the time interval between two datetime, returning the difference as an integer value in milliseconds
def mil_interval(tstart, tend) -> int:
    dif = tend - tstart
    mil = dif.days * 24 * 60 * 60 * 1000
    mil += dif.seconds * 1000
    mil += dif.microseconds / 1000
    return int(mil)

#function to get commands from the user
def get_commands() -> dict:
    print("Which case do you want to compute the complexity for?")
    print("-> for an already sorted list -> type 'already_sorted'")
    print("-> for a random sorted list -> type 'random_sorted'")
    print("-> for a sorted in reverse list -> type 'sorted_in_reverse'")

    commands = {
        "already_sorted": already_sorted,
        "random_sorted": random_sorted,
        "sorted_in_reverse": sorted_in_reverse
    }

    return commands

#function that compute the sorting comparison and build a table to illustrate the runtime
def sort_comparison() -> None:
    commands = get_commands()
    command = input("*** ")
    command = command.strip()
    command_part = command.split()
    command_name = command_part[0]

    if command_name in commands:
        try:
            lists_generators = commands[command_name]
        except Exception as e:
            print(e)
    else:
        print("Invalid command")
        exit(0)

    sort_functions = [shell_sort, exchange_sort]
    list_lengths = [1000, 2000, 4000, 8000, 16000]

    print("Current data: " + lists_generators.__name__)
    table = Texttable()
    table.add_row(['Algorithms/size'] + list_lengths)
    for sort_function in sort_functions:
        row = [sort_function.__name__]
        for length in list_lengths:
            nr_list = lists_generators(length)
            tstart = datetime.now()
            sort_function(nr_list)
            tend = datetime.now()
            row = row + [mil_interval(tstart, tend)]
        table.add_row(row)
    print(table.draw())

sort_comparison()

