"""
-write a menu based program
-practice python list, dict types
-how to represent program entities? --lists vs dict
-how to structure the program

problem statement
-- manage a list of cities, each city has a name, population and a county

program requirements
-- sort them by any of their features (name, pop or county)
-- add a city from the console
-- generate some random cities
-- search for a city, using case-insensitive partial string matching
-- exit the program

!!!!!!!!!!DONT USE GLOBAL VARIABLES!!!!!!!!!!
"""
from itertools import filterfalse


#from venv import create

# --- functions that deal with how a city is represented

#my_city = ["Constanta", 200000, "Constanta"] #represented by a list

# a dict is a set of key to value mappings, keys must be unique, values not necessarely
#my_city2 = { "name" : "Braila", "population" : 150_000, "county" : "Braila"} #represented a python dict

#function that creates the city list
def create_city(name : str, population : int, county : str):
    #list representation
    #return [name, population, county]
    #dict representation
    return {"name" : name, "population" : population, "county" : county}

#function that returns tha name of the city
def get_name(city) -> str:
    #list representation
    #return city[0]
    #dict representation
    return city["name"]

#function that returns the population of the city
def get_population(city) -> int:
    #return city[1]
    return city["population"]

#function that returns the county in witch is the city
def get_county(city) -> str:
    #return city[2]
    return city["county"]

def to_str(city) -> str:
    return get_name(city) + " with the population of " + str(get_population(city)) +  " is in " + get_county(city)

# --- functions that implement program requirements (search & sorting)

#function that search for the city
def search_for_city(cities: list) -> None:
    search_term = input("What city to search for? ")
    search_term = search_term.lower()

    results = []

    for i in cities:
        if search_term in get_name(i).lower():
            results.append(i)

    for i in results:
        print(to_str(i))

#all of these functions are sorting the values in ascending order!!

def cmp_by_name(city1, city2) -> bool:
    return get_name(city1) > get_name(city2)

def cmp_by_population(city1, city2) -> bool:
    return get_population(city1) > get_population(city2)

def cmp_by_county(city1, city2) -> bool:
    return get_county(city1) > get_county(city2)

#function that sort the cities depending on the user's preference
def sort_cities(cities: list, cmp_function) -> None:
    #let do a bubble sort
    sort_flag = False

    while not sort_flag:
        sort_flag = True
        for i in range(0, len(cities) - 1):
            if cmp_function(cities[i], cities[i + 1]) is True:
                #swap
                # aux = cities[i]
                # cities[i] = cities[i+1]
                # cities[i+1] = aux

                cities[i], cities[i+1] = cities[i+1], cities[i] #a smarter way to do a sort
                sort_flag = False


# --- user interface functions()
#NOTE the only place where are we allowed to write print(), input() statements

# new_city = create_city("Simeria", 12000, "Hunedoara")
# print(get_name(new_city), get_population(new_city))
# print(to_str(new_city))

#function that prints the list of the cities
def print_cities(cities: list) -> None:
    print("list of cities:")
    for i in cities:
        print(to_str(i))

#function that adds a city to the list
def add_city(cities: list) -> None:
    name = input("What is the name of the city? ")

    while True:
        try:
            population = int(input("What is the population of the city? "))
            break
        except ValueError: #valueerror is the type of error when failing to convert an str to an int
            print("Population must be an integer!")

    county = input("From witch county is this city? ")
    county = county.lower()

    cities.append(create_city(name, population, county))

#function that let the user choose the parameter the list should be sorted by
def sorting_option(cities: list) -> str:
    print("By what parameter do you want to sort the list of cities?")
    print("a. By name")
    print("b. By population")
    print("c. By county")

    option = input("Please enter your option: ")

    if option == "a":
        sort_cities(cities, cmp_by_name)
    elif option == "b":
        sort_cities(cities, cmp_by_population)
    elif option == "c":
        sort_cities(cities, cmp_by_county)

def run():
    cities = []  # this is the list of the cities

    #add a few cities from the beginning
    cities.append(create_city("Deva", 60000, "HD"))
    cities.append(create_city("Cluj Napoca", 500000, "CJ"))

    while True:
        print("0. Exit")
        print("1. Show all cities")
        print("2. Add a city")
        print("3. Search for a city")
        print("4. Sort the cities")

        command = input("***  ")

        if command == "1":
            # NOTE we write functions so that the main loop is not to complicated
            print_cities(cities)
            #pass

        elif command == "0":
            #break
            #return
            exit(0)

        elif command == "2":
            add_city(cities)

        elif command == "3":
            search_for_city(cities)

        elif command == "4":
            sorting_option(cities)

        else:
            print("Invalid command")

run()
