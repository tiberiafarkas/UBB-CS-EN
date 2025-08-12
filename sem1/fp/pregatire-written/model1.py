"""
Given the following code fragment, what is the result of the execution?
explain your answer.

a = A()
print(a)    // a
b = B(a)
print(b)    // aba
c = B(b)
print(c)    // ababa
"""

# class A:
#     def __str__(self):
#         return "a"
#
# class B(A):
#     def __init__(self, a = None):
#         self._a = a
#     def __str__(self):
#         return str(self._a) + "b" + A.__str__(self)
#
# a = A()
# print(a)
# b = B(a)
# print(b)
# c = B(b)
# print(c)

# Explanation:
# The code defines two classes, A and B.
# A has a __str__ method that returns "a", and B has a __str__ method that returns the string representation of the object it was initialized with (self._a), followed by "b" and the string representation of class A.
# When the code is executed, it creates an instance of class A (a) and prints its string representation, which is "a".
# str() method and print works the same way, so when we initialize in the class B the object a, it will print the string representation of a, which is "a"

"""
2. Write the FibMatrix class that represents a square matrix whose elements are the Fibonacci numbers in increasing  order, so that the example code below works according to the comments. 
Extra-space complexity must be 0(1) for  all operations except __str__. 
There are no restrictions on the size of n or time complexity [3p].  

fm = FibMatrix(2)  
# Will print 
# 0 1 
# 1 2  
print (fm)  

fm = FibMatrix(3)  
print (fm)  
# Will print  
# 0 1 1 
# 2 3 5  
# 8 13 21  

fm2 = fm + 10  
print(fm2)  
# Will print (add 10 to each element)  
# 10 11 11  
# 12 13 15  
# 18 23 31 
 
# Will print 10 11 11 12 13 15 18 23 31  
for i in fm2:  
    print (i)  
"""

# class FibMatrix:
#     def __init__(self, n):
#         self.n = n  # Size of the matrix
#
#     def _fibonacci(self, count):
#         """Generate the first `count` Fibonacci numbers."""
#         a, b = 0, 1
#         for _ in range(count):
#             yield a
#             a, b = b, a + b
#
#     def __str__(self):
#         """Return a string representation of the matrix."""
#         size = self.n * self.n
#         fibs = list(self._fibonacci(size))  # Generate Fibonacci numbers
#         result = ""
#         for i in range(self.n):
#             for j in range(self.n):
#                 result += str(fibs[i * self.n + j]) + " "
#             result += "\n"
#         return result  # Remove the trailing newline
#
#     def __add__(self, value):
#         """Add a scalar value to each element of the matrix and return a new FibMatrix object."""
#
#         # Modify __str__ to use the updated Fibonacci numbers
#         class FibMatrixWithOffset(FibMatrix):
#             def __init__(self, n, offset):
#                 super().__init__(n)
#                 self.offset = offset
#
#             def _fibonacci(self, count):
#                 for fib in super()._fibonacci(count):
#                     yield fib + self.offset
#
#         return FibMatrixWithOffset(self.n, value)
#
#     def __iter__(self):
#         """Iterate through all elements of the matrix in row-major order."""
#         size = self.n * self.n
#         return self._fibonacci(size)
#
# fm = FibMatrix(2)
# print(fm)
#
# fm = FibMatrix(3)
# print(fm)
#
# fm2 = fm + 10
# print(fm2)
#
# for i in fm2:
#     print(i, end = " ")

"""
Specify the following function. 
Build a test function that uses the randint function of the random module to generate 100 lists on which it checks the implementation below.
Tests no not have to conform to PyUnit

def f(data: list):
    if data == None or data == []:
        raise ValueError()
    aux = data[0]
    for elem in data:
        if aux - elem > 0:
            return False
        aux = elem
    return True
"""

# def f(data: list):
#     if data == None or data == []:
#         raise ValueError()
#     aux = data[0]
#     for elem in data:
#         if aux - elem > 0:
#             return False
#         aux = elem
#     return True

#The function checks if the list is sorted in ascending order

# from random import randint
#
# def test_f():
#     for i in range(100):
#         data = [randint(0, 100) for _ in range(10)]
#         data.sort()
#         assert f(data) == True
#         data.sort(reverse = True)
#         assert f(data) == False
#
# test_f()

"""
Given an array of n integers, find the start and end positions of the subarray having maximum sum.
For the array [2, -3, 10, 1, -2, -4, 12, -2], the subarray with the maximum sum is [10, 1, -2, -4, 12], with start 2 and end 6.
Provide two solutions - one that works in O(n) time complexity, and one that works in O(n^2) time complexity.
"""

# O(n) time complexity solution
# def max_subarray_sum(arr = [2, -3, 10, 1, -2, -4, 12, -2]):
#     max_sum = float('-inf')
#     current_sum = 0
#     start = 0
#     end = 0
#     current_start = 0
#
#     for i, num in enumerate(arr):
#         current_sum += num
#
#         if current_sum > max_sum:
#             max_sum = current_sum
#             start = current_start
#             end = i
#
#         if current_sum < 0:
#             current_sum = 0
#             current_start = i + 1
#
#     print(start, end)
#
# max_subarray_sum()
#
# def max_sum(filename="secvsummax.in", output_file="secvsummax.out"):
#     #de testat pe pbinfo
#     # Read the input file
#     with open(filename, "r") as file:
#         lines = file.readlines()
#
#     # Parse the first line for the number of elements (n)
#     n = int(lines[0].strip())
#
#     # Read the rest of the lines, split by spaces, and convert to integers
#     data = []
#     for line in lines[1:]:
#         data.extend(map(int, line.split()))
#
#     # Implementing Kadane's Algorithm
#     start = 0
#     end = 0
#     max_s = -100000000
#     s = 0
#     pos = 0
#
#     for i in range(len(data)):
#         if s > max_s:
#             max_s = s
#             end = i - 1
#             start = pos
#
#         if s + data[i] > 0:
#             s += data[i]
#         else:
#             s = 0
#             pos = i + 1
#
#     # Output the result
#     with open(output_file, "w") as file:
#         file.write("{0} {1}\n".format(start + 1, end + 1))
#
# max_sum()

# O(n^2) time complexity solution
# def max_subarray_sum(arr = [2, -3, 10, 1, -2, -4, 12, -2]):
#     max_sum = float('-inf')
#     start = 0
#     end = 0
#
#     for i in range(len(arr)):
#         current_sum = 0
#         for j in range(i, len(arr)):
#             current_sum += arr[j]
#             if current_sum > max_sum:
#                 max_sum = current_sum
#                 start = i
#                 end = j
#
#     print(start, end)

# def max_sum(data = [2, -3, 10, 1, -2, -4, 12, -2]):
#     start = 0
#     end = 0
#     max_s = -1000000000
#     s = 0
#     for i in range(len(data)):
#         pos = i
#         s = 0
#         for j in range(i, len(data)):
#             if s + data[j] < 0:
#                 break
#             s += data[j]
#         if s > max_s:
#             start = pos
#             end = j - 1
#             max_s = s
#     print(start, end)
#
# max_sum()