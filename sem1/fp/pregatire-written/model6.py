"""
Given the following code fragment, what is the result of the execution?
explain your answer.

def g(f, n):
    if n == 0:
        return f() + " 0"
    if type(f) == str:
        return f
    return f() + " " + g(f, n-1)

def f():
    return "f"

print(g(g(f,2), 3))

Explanation:
g(f, 2) -> "f" _ g(f, 1)                               -> "f" "f" "f" "0"
                  "f" _ g(f, 0)      ->  "f" "f" "0"
                        "f" + " 0"
"""

# def g(f, n):
#     if n == 0:
#         return f() + " 0"
#     if type(f) == str:
#         return f
#     return f() + " " + g(f, n-1)
#
# def f():
#     return "f"
#
# print(g(g(f,2), 3))

"""
A sparse data structure is one where we presume most of the elements have a common value (eg 0)
Write the SparseList class, which implements a sparse list data structure so that the code below works according to the comments
Elements not explicitly set must have the default value 0
The list's length is given by the largest index of a non-zero element. Use the __iter__, __next__ and __len__ methods appropriately.
Do not represent 0 values in memory!

# initialize a sparse list having 6 elements
data = SparseList()
# add elements
data.set(1, 1)
# set element at index 3 to value 2
data.set(3, 2)
data.set(5, 3)
data.set(9, 99)

# 10th element of the list is now 100
data.set(9, data.get(9) + 1)

# prints
# 0 1 0 2 0 3 0 0 0 100
for elem in data:
    print(elem)
"""

# class SparseList:
#     def __init__(self):
#         self.data = {}
#
#     def set(self, index, value):
#         self.data[index] = value
#
#     def get(self, index):
#         return self.data.get(index, 0)
#
#     def __iter__(self):
#         self.iter_index = 0
#         return self
#
#     def __next__(self):
#         if self.iter_index > max(self.data.keys(), default=0):
#             raise StopIteration
#         value = self.get(self.iter_index)
#         self.iter_index += 1
#         return value
#
#     def __len__(self):
#         return max(self.data.keys(), default=0) + 1

# class SparseIterator:
#     def __init__(self, elements, max_index):
#         self.__elements = elements
#         self.__max_index = max_index
#         self.__pos = -1
#
#     def __next__(self):
#         self.__pos += 1
#         if self.__pos > self.__max_index:
#             raise StopIteration()
#
#         return self.__elements.get(self.__pos, 0)
#
# class SparseList:
#     def __init__(self):
#         self.__data = {}
#         self.__max_index = 0
#
#     def get(self, pos):
#         return self.__data.get(pos, 0)
#
#     def set(self, pos, value):
#         if value == 0:
#             del self.__data[pos]
#         else:
#             self.__data[pos] = value
#             self.__max_index = max(self.__max_index, pos)
#
#     def __len__(self):
#         return self.__max_index
#
#     def __iter__(self):
#         return SparseIterator(self.__data, self.__max_index)
#
#
# data = SparseList()
# data.set(1, 1)
# data.set(3, 2)
# data.set(5, 3)
# data.set(9, 99)
# data.set(9, data.get(9) + 1)
#
# for elem in data:
#     print(elem)

"""
Analyze the best case and worst case time complexity as well as the extra-space complexity of the following function

def f(data: list):
    if len(data) == 1:
        return data[0]
    if data[0] % 2 = 0:
        return -1
    return f(data[1:])
    
Time complexity:
Best case: O(1) when the first element is even or the initial list sent as parameter has only one element
Worst case: O(n) where n is the length of the list and there are no even numbers in the list

Extra-space complexity: O(n) in case of worst case, O(1) in case of best case

"""
