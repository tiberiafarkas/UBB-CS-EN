"""
Given the following code fragment, what is the result of the execution?
explain your answer.

def f(a, b):
    b.append(a)
    a = [a]
    b = b + a
    return b

x = 1
y = [2]
z = f(x, y)     y = [2,1], z = [2,1,1]
print([1] == x)    False
print(id(y) == id(z))   False
print(y == z[0:2])  True

id() returns the identity of the object, which is unique and constant for this object during its lifetime.
z[0:2] returns the first two elements of the list z, which are [2, 1].

"""

# def f(a, b):
#     b.append(a)
#     a = [a]
#     b = b + a
#     return b
#
# x = 1
# y = [2]
# z = f(x, y)
# print([1] == x)
# print(id(y) == id(z))
# print(y == z[0:2])

"""
A sparse data structure is one where we presume most of the elements have a common value (e.g 0).
Write the SparseList and SparseListIterator classes co that the code below works according to the comments.
Elements not explicitly set must have the default value 0.
The list's length is given by the largest index set to a non-zeo value.
Use the __setitem__, __getitem__, __iter__ and __next__ methods appropiately.
Do not represent 0 values in memory!

# initialize a sparse list
datal = SparseList()
# add elements
datal[0] = 1
# set element at index 2 to value 2
datal[2] = 2

#prints 
1 1 
1 0 
1 2 
0 1 
0 0 
0 2 
2 1 
2 0 
2 2

datal = [1, 0, 2]

for iter1 in datal:
    for iter2 in datal:
        print(iter1, iter2)


"""

# class SparseList:
#     def __init__(self):
#         self.data = []
#
#     def __setitem__(self, key, value):
#         if key >= len(self.data):
#             self.data.extend([0] * (key - len(self.data) + 1))
#         self.data[key] = value
#
#     def __getitem__(self, key):
#         return self.data[key]
#
#     def __iter__(self):
#         return SparseListIterator(self.data)
#
# class SparseListIterator(SparseList):
#     def __init__(self, data):
#         self.data = data
#         self.index = 0
#
#     def __next__(self):
#         if self.index >= len(self.data):
#             raise StopIteration()
#         result = self.data[self.index]
#         self.index += 1
#         return result

# class SparseListIterator:
#     def __init__(self, elements):
#         self.__elements = elements
#         self.__pos = -1
#
#     def __next__(self):
#         self.__pos += 1
#         if self.__pos >= len(self.__elements):
#             raise StopIteration()
#
#         return self.__elements[self.__pos]
#
#
# class SparseList:
#     def __init__(self):
#         self.__data = []
#
#     def __setitem__(self, pos, value):
#         if pos >= len(self.__data):
#             self.__data.extend([0] * (pos - len(self.__data) + 1))   #!!!!!
#         self.__data[pos] = value
#
#     def __getitem__(self, pos):
#         return self.__data[pos]
#
#     def __iter__(self):
#         return SparseListIterator(self.__data)
#
#
# datal = SparseList()
# datal[0] = 1
# datal[2] = 2
#
# for iter1 in datal:
#     for iter2 in datal:
#         print(iter1, iter2)


"""
Analyse the time and extra space complexity of the following function.
Disregard the call stack space

def f(count: int, data: list):
    if count != 1:
        if len(data) < 10: 
            data.append(count)
        
        f(count - 1, data)
        f(count - 1, data)
    else:
        print(count, data)
        
Time complexity:
let n = count
T(n) = 2T(n-1) + O(1)
T(n) = 2(2T(n-2) + O(1)) + O(1) = 4T(n-2) + 2O(1)
T(n) = 8T(n-3) + 4O(1)
...
T(1) = O(1)

=> T(n) = 2^kT(n-k) + 2^kO(1)
=> n - k = 1 => k = n - 1
=> T(n) = 2^(n-1)T(1) + 2^(n-1)O(1) = 2^(n-1) + 2^(n-1)O(1) = O(2^n)

The append operation is executed at most 10 times, so it is O(1)

Extra space complexity:
O(1) because of the if statement 
"""

"""
Given the following problem statement, state which of the studied problem solving methods provides the best time complexity to solve it and explain why.
Show how the method represents intermediate data (if applicable), and how the solution(s) is/are reached.
Writing source code is not required.

Given a rod of length n and an array of prices for all pieces smaller than n, determine the maximum value obtainable 
by cutting up the into integer-sized pieces and selling them.
Exemplify solving the problem for a rod of length n = 8, having the following arrays of length (1, 2, 3, 4, 5, 6, 7, 8) and prices 
(1, 5, 8, 9, 10, 17, 17, 20) respectively (e.g. the price for a rod of length 4 is 9).


The best time complexity is O(n^2) using dynamic programming. The intermediate data is represented by a list of the maximum values for each rod length.
The solution is reached by computing the maximum value for each rod length by considering all possible cuts. 
When considering a cut of length i, the maximum value is the maximum between the value of the cut and the maximum value for the remaining rod length.
For the rod of length 8, the maximum value is 22, obtained by cutting the rod into pieces of length 2 and 6, with prices 5 and 17 respectively.
How would be computed the solution:
dp[i] = max(dp[i], dp[i - j] + prices[j - 1]), where i is the rod length and j is the cut length

"""
