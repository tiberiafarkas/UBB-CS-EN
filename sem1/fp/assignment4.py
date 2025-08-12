"""
Backtracking problems P11
    Two natural numbers m and n are given.
    Display in all possible modalities the numbers from 1 to n,
    such that between any two numbers on consecutive positions, the difference in absolute value is at least m.
    If there is no solution, display a message.
    Make a check function to see if the result returned by the recursive back function and iterative back function are the same or not, using assert
"""

"""
Dynamic programming problems P5
    Maximize the profit when selling a rod of length n. 
    The rod can be cut into pieces of integer lengths and pieces can be sold individually. 
    The prices are known for each possible length. 
    For example, if rod length n = 7, and the price array is price = [1, 5, 8, 9, 10, 17, 17] (the price of a piece of length 3 is 8), 
    the maximum profit is 18, and is obtained by cutting the rod into 3 pieces, two of length two and one of length 3. 
    Display the profit and the length of rod sections sold to obtain it.
"""


#function for recursive backtracking
def recursive_back(k: int, stack: list, n: int, m: int, list_back_rec: list) -> None:
    for i in range(1, n + 1):
        #check if this choice is valid
        if k == 0 or abs(stack[k-1] - i) >= m:
            if k < len(stack):
                stack[k] = i
            else:
                stack.append(i)
            if len(stack) < n:
                #backtrack for the next elements
                recursive_back(k + 1, stack, n, m, list_back_rec)
            else:
                #we have a complete valid solution
                #print(stack[:n])
                list_back_rec.append(stack[:n])
            stack.pop()

#function for interactive backtracking
def interactive_back(n: int, m: int, list_back_int: list) -> None:
    stack = []
    choices = [0] * n  #track the last tried number for each position
    index = 0

    while True:
        if index < n:
            #set the start based on choices (last tried number + 1) for each position
            start = choices[index] + 1
            found = False

            for i in range(start, n + 1):
                #check if this choice is valid
                if index == 0 or abs(stack[index - 1] - i) >= m:
                    if index < len(stack):
                        stack[index] = i
                    else:
                        stack.append(i)

                    #update the last choice tried for this index
                    choices[index] = i
                    index += 1
                    found = True
                    break

            #if no valid number is found, backtrack
            if not found:
                choices[index] = 0  #reset the choice for this index
                if index == 0:
                    break
                index -= 1
                stack.pop()
        else:
            #we have a complete valid solution
            #print(stack[:n])
            list_back_int.append(stack[:n])
            #backtrack to look for more solutions
            index -= 1
            stack.pop()

#function to check if the result returned by the recursive back function and iterative back function are the same or not
def check_functions(list_back_rec: list, list_back_int: list) -> bool:
    if len(list_back_rec) != len(list_back_int):
        return False
    for i in range(len(list_back_rec)):
        if list_back_rec[i] != list_back_int[i]:
            return False

    return True

#function to get command - what problem to be solved
def get_command() -> dict:
    print("For backtracking: run_back")
    print("For dynamic programming: run_dynamic or run_naive_dynamic")

    commands = {
        "run_back": run_back,
        "run_dynamic": run_dynamic,
        "run_naive_dynamic": run_naive_dynamic
    }
    return commands

#function to run the backtracking problem
def run_back():
    n = int(input("n = "))
    m = int(input("m = "))

    stack = []
    list_back_rec = []
    list_back_int = []
    # print("recursive_back:")
    recursive_back(0, stack, n, m, list_back_rec)
    # print("interactive_back:")
    interactive_back(n, m, list_back_int)
    test_back(list_back_rec, list_back_int)

def get_price_list() -> tuple:
    n = int(input("n = "))
    price_list = []
    for i in range(0, n):
        price_list.append(int(input(f"price[{i}] = ")))
    return n, price_list

def run_dynamic():
    n, price_list = get_price_list()
    dp = [0] * (n + 1)
    path = [0] * (n + 1)

    for i in range(1, n + 1):
        for j in range(1, i + 1):
            if dp[i] < price_list[j - 1] + dp[i - j]:
                dp[i] = price_list[j - 1] + dp[i - j]
                path[i] = j

    print("maximum value is:", dp[n])
    print("lengths of rod sections sold to achieve maximum profit:")

    #n -= 1
    while n > 0:

        print(path[n], end=" ")
        n -= path[n]

def cut_rod(price_list, index, n, path):
    #base case
    if index == 0:
        path[n] = [1] * n
        return n * price_list[0]

    if n == 0 :
        return 0  #we cant cut the road anymore

    rod_length = index + 1

    #we can either cut the rod of this length or let it the way it is
    not_cut = cut_rod(price_list, index - 1, n, path)

    if rod_length <= n:
        cut = price_list[index] + cut_rod(price_list, index, n - rod_length, path)

        if cut > not_cut:

            #keep in mind the current cut
            if n not in path:
                path[n] = []

            path[n] = path[n-rod_length] + [rod_length]

            return cut

    return not_cut

    #return max(cut_rod(price_list, index - 1, n), price_list[index] + cut_rod(price_list, index, n - rod_length)) if rod_length <= n else cut_rod(price_list, index - 1, n)

def run_naive_dynamic():
    n, price_list = get_price_list()
    path = {0: []}  #base case
    print("maximum value is: ", cut_rod(price_list, n - 1, n, path))
    print("lengths of rod sections sold to achieve maximum profit:")
    print(path.get(n, []))

def run():
    commands = get_command()
    command = input("choose the problem to solve: ")
    command = command.strip()
    command_part = command.split()
    command_name = command_part[0]

    if command_name in commands:
        commands[command_name]()
    else:
        print("invalid command")
        exit(0)


def test_back(list_back_rec: list, list_back_int: list):
    list1 = [[1, 2, 3], [2, 4, 5]]
    list2 = [[1, 2, 3, 4], [2, 3, 4, 5]]
    assert(check_functions(list_back_rec, list_back_int) == True )
    assert(check_functions(list1, list2) == False )

run()
