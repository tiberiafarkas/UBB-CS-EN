#
# Write the implementation for A5 in this file
#

import cmath
from random import randint
from unicodedata import digit

#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_nr(re_part: int, img_part: int) -> list:
    """
    function to create a complex nr
    :param re_part: the real part of the complex number
    :param img_part: the imaginary part of the complex number
    :return: return a list containing the complex nr
    """
    if type(re_part) != int:
        raise ValueError("real part of the number must be a real value")
    if type(img_part) != int:
        raise ValueError("imaginary part of the number must be a real value! The imaginary number 'i' will be added lately")
    return [re_part, img_part]

def get_real_part(z: list) -> int:
    """
    function to get the real part of the complex number
    :param z: the complex number z
    :return: the real part of the complex number z
    """
    return z[0]

def get_imag_part(z: list) -> int:
    """
    function to get the imaginary part of the complex number
    :param z: the complex number z
    :return: the imaginary part of the complex number z
    """
    return z[1]

def test_complex_nr():
    z = create_complex_nr(1, 2)
    #print(get_real_part(z), get_imag_part(z))
    assert get_real_part(z) == 1
    assert get_imag_part(z) == 2

    try:
        z1 = create_complex_nr('a', 2)
        assert False  #if execution reaches this point, there was no ValueError raised in the function!
    except ValueError:
        assert True   #the code does its job

test_complex_nr()

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_nr_dict(re_part: int, img_part: int) -> dict:
    """
    function to create a complex nr
    :param re_part: the real part of the nr
    :param img_part: the imaginary part of the nr
    :return: return a dictionary containing the complex nr
    """
    if type(re_part) != int:
        raise ValueError("real part of the number must be a real value")
    if type(img_part) != int:
        raise ValueError("imaginary part of the number must be a real value! The imaginary number 'i' will be added lately")
    return {"re_part": re_part, "img_part": img_part}

def get_real_part_dict(z: dict) -> int:
    """
    function to get the real part of the complex number which is store as a dictionary
    :param z: the complex number
    :return: the real part of the complex nr
    """
    return z["re_part"]

def get_imag_part_dict(z: dict) -> int:
    """
    function to get the imaginary part of the complex number which is store as a dictionary
    :param z: the complex number
    :return: the imaginary part of the complex nr
    """
    return z["img_part"]

def test_complex_nr_dict():
    z = create_complex_nr_dict(1, 2)
    assert get_real_part_dict(z) == 1
    assert get_imag_part_dict(z) == 2

    try:
        z1 = create_complex_nr_dict('a', 2)
        assert False
    except ValueError:
        assert True

test_complex_nr_dict()

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def compare_digits(previous_digits: set, actual_digits: set) -> bool:
    """
    function to compare if 2 different complex numbers have the same digits in base 10
    :param previous_digits: digits of the previous complex number
    :param actual_digits: digits of the actual complex number
    :return: true if the digits of the actual complex number can be found in the digits of the previous complex number
             false otherwise
    """
    prev_digits = list(previous_digits) #transform the set into a list so it can be sorted
    act_digits = list(actual_digits)
    prev_digits.sort()
    act_digits.sort()
    i = 0
    j = 0
    while j < len(act_digits) and i < len(prev_digits):
        #check if the digits in actual number can be found in the digits of the previous number
        if prev_digits[i] < act_digits[j]:
            while i < len(prev_digits) and prev_digits[i] < act_digits[j]:
                i += 1
        elif prev_digits[i] == act_digits[j]:
            j += 1
            i += 1
        else:
            return False

    return j == len(act_digits)


def memorize_digits(z) -> set:
    """
    function to memorize the digits of the complex number
    :param z: the complex number
    :return: a set containing the digits of the complex number
    """
    uniq_digits = set()
    real_part = abs(get_real_part(z))
    img_part = abs(get_imag_part(z))
    while real_part > 0:
        uniq_digits.add(real_part % 10)
        real_part = real_part // 10

    while img_part > 0:
        uniq_digits.add(img_part % 10)
        img_part = img_part // 10

    return uniq_digits

def longest_subarray(complex_nr_list: list, complex_nr_dict: dict) -> tuple:
    """
    function to determine the longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digits
    :param complex_nr_list:
    :param complex_nr_dict:
    :return: the indices of the beginning and end of the longest subarray
    """
    max_contor = 0
    for i in range(len(complex_nr_list)):
        previous_digits = memorize_digits(complex_nr_list[i])
        contor = 1
        j = i + 1

        while j < len(complex_nr_list):
            actual_digits = memorize_digits(complex_nr_list[j])
            if compare_digits(previous_digits, actual_digits):
                contor += 1
            else:
                break
            j += 1

        if contor > max_contor:
            max_contor = contor
            start = i
            stop = j - 1

    return start, stop

#TODO -> i have to change this function to compute the maximum subsequence sum
def max_subarray_sum(complex_nr_list: list, complex_nr_dict: dict) -> int:
    """
    function to determine the maximum subarray (subsequence) sum when considering each number's real part
    :param complex_nr_list:
    :param complex_nr_dict:
    :return: maximum sum
    """

    """
    1+i 2-6i -3+9i
    """
    #sum = 0
    #data_list = []

    max_sum = [0] * len(complex_nr_list)
    max_sum[0] = get_real_part(complex_nr_list[0])

    for i in range(len(complex_nr_list)):
        max_sum[i] = max(get_real_part(complex_nr_list[i]), max_sum[i - 1] + get_real_part(complex_nr_list[i]))

    #if max_sum > 0:
    data_list = []
    #for i in range(len(complex_nr_list)):
        #if len(dp) > 1 and get_real_part(complex_nr_list[i]) + dp[-1] > dp[len(dp) - 1]:
         #   dp[len(dp) - 1].append(get_real_part(complex_nr_list[i]) + dp[-1])
        # if get_real_part(complex_nr_list[i]) > 0:
        #     sum += get_real_part(complex_nr_list[i])
        #     data_list.append(complex_nr_list[i])

    return max(max_sum)

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def exit_program(complex_nr_list, complex_nr_dict) -> None:
    exit(0)

def read_numbers(complex_nr_list: list, complex_nr_dict: list) -> None:
    """
    function to read the numbers
    :param complex_nr_list: list formed from the complex numbers stored in a list
    :param complex_nr_dict: list formed from the complex numbers stored in a dictionary
    :return: it does not return anything
    """
    print("Introduce 10 complex numbers \n Your input would look like: \n Introduce real part: 2\n Introduce imaginary part: 1\n Please note you don't need to add the imaginary number 'i'")

    for i in range(10):
        while True:
            try:
                real_part = int(input(f"Introduce the real part of the {i + 1} complex number: "))
                break
            except ValueError:
                print("The value introduced must be an integer, please try again!")

        while True:
            try:
                imag_part = int(input(f"Introduce the imaginary part of the {i + 1} complex number: "))
                break
            except ValueError:
                print("The value introduced must be an integer, please try again! \n Don't forget to introduce only the real value for the imaginary part of the number (eg: 3i, you should introduce only '3'")

        complex_nr_list.append(create_complex_nr(real_part, imag_part))
        complex_nr_dict.append(create_complex_nr_dict(real_part, imag_part))

def generate_numbers(complex_nr_list: list, complex_nr_dict: list):
    """
    function to generate random numbers
    :param complex_nr_list: list formed from the complex numbers stored in a list
    :param complex_nr_dict: list formed from the complex numbers stored in a dictionary
    :return: does not return anything
    """
    for i in range(10):
        real_part = randint(-20, 20)
        img_part = randint(-20, 20)
        complex_nr_list.append(create_complex_nr(real_part, img_part))
        complex_nr_dict.append(create_complex_nr_dict(real_part, img_part))

def display_numbers(complex_nr_list: list, complex_nr_dict: dict) -> None:
    """
    function to display the complex numbers stored as lists and dictionaries
    :param complex_nr_list: list formed from the complex numbers stored in a list
    :param complex_nr_dict: list formed from the complex numbers stored in a dictionary
    :return: does not return anything
    """
    print("Complex numbers stored in a list: ")
    for z in complex_nr_list:
        print(to_str(z))

    print("Complex numbers stored in a dictionary: ")
    for z in complex_nr_dict:
        print(to_str_dict(z))

def to_str(z):
    return str(get_real_part(z)) + "+" + str(get_imag_part(z)) + "i" if get_imag_part(z) >= 0 else str(get_real_part(z)) + str(get_imag_part(z)) + "i"

def to_str_dict(z):
    return str(get_real_part_dict(z)) + "+" + str(get_imag_part_dict(z)) + "i" if get_imag_part_dict(z) >= 0 else str(get_real_part_dict(z)) + str(get_imag_part_dict(z)) + "i"

def display_longest_subarray(complex_nr_list: list, complex_nr_dict: dict) -> None:
    """
    function to display the longest subarray of numbers which have the same digits in base 10
    :param complex_nr_list:
    :param complex_nr_dict:
    :return: it does not return anything
    """
    start, stop = longest_subarray(complex_nr_list, complex_nr_dict)

    print("The longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digit is: ")

    while start <= stop:
        print(to_str(complex_nr_list[start]))
        start += 1

def display_max_subarray_sum(complex_nr_list: list, complex_nr_dict: dict):
    """
    function to display the maximum subarray (subsequence) sum when considering each number's real part
    :param complex_nr_list:
    :param complex_nr_dict:
    :return: it does not return anything
    """
    max_sum = max_subarray_sum(complex_nr_list, complex_nr_dict)
     #, data_list) = max_subarray_sum(complex_nr_list, complex_nr_dict)

    print("The maximum subarray sum of the real part of the complex number is: ", max_sum)
    #print("The subarray is:", data_list)


def get_command() -> dict:
    commands = {
        "0": exit_program,
        "1": read_numbers,
        "2": generate_numbers,
        "3": display_numbers,
        "4": display_longest_subarray,
        "5": display_max_subarray_sum
    }

    return commands

def print_menu() -> None:
    print("0. Exit")
    print("1. Read a list of complex numbers from the console")
    print("2. Generate multiple random complex numbers")
    print("3. Display the list of complex numbers")
    print("4. A longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digits")
    print("5. A maximum subarray sum, when considering each number's real part.")

def start():
    complex_nr_list = []
    complex_nr_dict = []

    while True:
        try:
            print_menu()
            commands = get_command()
            option = input(">>> ")
            if option in commands:
                commands[option](complex_nr_list, complex_nr_dict)
            else:
                print("Invalid command")
                exit(0)

        except ValueError as ve:
            print(ve)

start()


if __name__ == "__main__":
    print("Make magic happen")



