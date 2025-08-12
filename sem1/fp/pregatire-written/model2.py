"""
Given the following code fragment, what is the result of the execution?
explain your answer.

a = 1
def f(a):
    a = 2
def g(a):
    a[0] = 2


x = 3
f(x)
print(a)   ->   prints 1
print(x)   ->   prints 2
x = [3, 3]
g(x)
print(x)   ->   prints [2, 3]

"""

# a = 1
# def f(a):
#     a = 2     # Local reassignment, does not affect the argument passed.
# def g(a):
#     a[0] = 2  # Modifies the first element of the passed list in place.
#
#
# x = 3
# f(x)
# print(a)
# print(x)
# x = [3, 3]
# g(x)
# print(x)

"""
A sparse data structure is one where we presume most of the elements have a common value (eg 0)
Write the SparseMatrix class, which implements a sparse matrix data structure.
Elements not explicitly set have the default value 0
The matrix size is given in the constructor
Do not represent 0 values in memory!

# initialize a 3x3 sparse matrix
m1 = SparseMatrix(3, 3)
# value at [1,1] is 2
m1.set(1, 1, 2)
# value at [2,2] is 4
m1.set(2, 2, 4)

# prints
# 0 0 0
# 0 2 0
# 0 0 4

print(m1)

# prints '<class 'ValueError'>'

try:
    m1.set(3, 3, 99)
except Exception as e:
    print(type(e))
    
# update value at [1,1] to 3
m1.set(1, 1, mi1.get(1,1) + 1)

#prints
# 0 0 0
# 0 3 0
# 0 0 4

print(m1)

"""

# class SparseMatrix():
#     def __init__(self, n, m):
#         self.n = n
#         self.m = m
#         self.data = {}
#
#     def set(self, i, j, value):
#         if i >= self.n or j >= self.m:
#             raise ValueError("Index out of bounds")
#         if value == 0:
#             if (i, j) in self.data:
#                 del self.data[(i, j)]
#         else:
#             self.data[(i, j)] = value
#
#     def get(self, i, j):
#         return self.data.get((i, j), 0)
#
#     def __str__(self):
#         result = ""
#         for i in range(self.n):
#             for j in range(self.m):
#                 result += str(self.get(i, j)) + " "
#             result += "\n"
#         return result

# class SparseMatrix:
#     def __init__(self, n, m):
#         self._n = n
#         self._m = m
#         self._matrix = {}
#
#     def get(self, n, m):
#         return self._matrix.get((n, m), 0)
#
#     def set(self, n, m, value):
#         if n >= 0 and n < self._n and m >= 0 and m < self._m:
#             if value == 0:
#                 del self._matrix[(n, m)]
#             else:
#                 self._matrix[(n, m)] = value
#         else:
#             raise ValueError("Out of bounds")
#
#     def __str__(self):
#         output = ""
#         for row in range(self._n):
#             for col in range(self._m):
#                 output = output + str(self.get(row, col)) + " "
#             output += '\n'
#         return output
#
#
# # initialize a 3x3 sparse matrix
# m1 = SparseMatrix(3, 3)
# # value at [1,1] is 2
# m1.set(1, 1, 2)
# # value at [2,2] is 4
# m1.set(2, 2, 4)
#
# print(m1)
#
# try:
#     m1.set(3, 3, 99)
# except Exception as e:
#     print(type(e))
#
# # update value at [1,1] to 3
# m1.set(1, 1, m1.get(1, 1) + 1)
#
# print(m1)

"""
Analyse the time and extra-space complexity of the following function when called with an empty list

def f(n: int, data: list):
    if n > 1:
        data += [n]     #this takes O(1) time
        f(n//2, data)
        for j in range(1, n + 1):
            print(j)
    else:
        print(data)
        
Time Complexity:
T(n) = T(n/2) + n + 1
T(n/2) = T(n/4) + n/2 + 1
T(n/4) = T(n/8) + n/4 + 1
...
T(1) = 1

T(n) = n + 1 + n/2 + 1 + n/4 + 1 + ... + 1 + = n(1 + 1/2 + 1/4 + ... + 1/n) + log_2(n) = n * 2 + log_2(n) = 2n + log_2(n)
=> O(n)

Space Complexity:
The extra space is the list data, which has a length of log(n) + 1

"""

"""
Given the following problem statement, state which of the studied problem solving methods provides the best time complexity
to solve it and explain why. Describe the mathematical solution (if applicable) and intermediate data representation (if applicable), 
and how the solution(s) is/are reached.
Writing source code is not required.

A stair can be climbed by going up either one, two or three steps at a time.
How many ways to climb a stair of n steps are there? For instance, 3 steps can be climbed
as 1-1-1, 1-2, 2-1, 3, so there are 4 ways to climb 3 steps. 
Exemplify solving the problem for a stair having n= 10 steps

Determine the algorithm's time and extra space complexity   

Solution:

The method which provides the best time complexity to solve it is dynamic programming because the result can be obtain in a linear time O(n). 
We will use memoization to store the results of the subproblems and avoid redundant calculations. In this way, we can use the results calculated before to 
calculate the result of the current step. The extra space complexity is O(n) because we need to use a list of n elements to store this results.
To solve the problem for n = 10, we will calculate the number of ways to climb 10 steps based on the previous results.
We will start with dp[1] = 1, dp[2] = 2, dp[3] = 4, and then calculate dp[4], dp[5], ..., dp[10] based on the previous results.
We know that the current result depend in how many ways you can get to that step by climbing 1, 2 or 3 steps, thus the result is the sum of the results of the previous 3 steps.
So, the dynamic formula is: dp[i] = dp[i-1] + dp[i-2] + dp[i-3]

"""