"""
Given the following code fragment, what is the result of the execution?
explain your answer.

class X:
    def f(self):
        print("X")

class Y(X):
    def __init__(self, a):
        self._a = a

    def f(self):
        print("Y")
        self._a.f()


class Z(Y):
    def __init__(self, a):
        super().__init__(a)

for _ in [Y(Y(X())), Z(Y(X()))]:
    _.f()

# Explanation:
# The code defines three classes: X, Y, and Z.
# X has a method f that prints "X".
# Y inherits from X and has an __init__ method that initializes an attribute _a with the passed argument, and a method f that prints "Y" and calls the f method of the _a attribute.
# Z inherits from Y and has an __init__ method that calls the __init__ method of the superclass (Y).

# When the code is executed, it creates instances of Y and Z with nested instances of X.
# For the first iteration, the instance of Y calls its f method, which prints "Y" and calls the f method of Y(x) (the nested instance of X), which prints "Y" and calls the f method of the nested instance of X, which prints "X".
# For the second iteration, the instance of Z calls its f method, which prints "Y" and calls the f method of Y(x) (the nested instance of X), which prints "Y" and calls the f method of the nested instance of X, which prints "X".

# Therefore, the output of the code will be:
# Y
# Y
# X
# Y
# Y
# X

"""

# class X:
#     def f(self):
#         print("X")
#
#
# class Y(X):
#     def __init__(self, a):
#         self._a = a
#
#     def f(self):
#         print("Y")
#         self._a.f()
#
#
# class Z(Y):
#     def __init__(self, a):
#         super().__init__(a)
#
#
# for _ in [Y(Y(X())), Z(Y(X()))]:
#     _.f()

"""
Write the PrimeList class, which has the property that its ith element holds the ith prime number.
The list must grow dynamically, based on __getitem__ requests. Implement the required exception class.
Make sure the code below can be executed according to the comments.

data = PrimeList()
# Print 2 3 5 7 11 13 17 19 23 29
for i in range(10):
    print(data[i])
    
# Print 547
print(data[100])

#Prints 'List is read-only'
try:
    data[5] = 10
except PrimeListException as ple:
    print(ple)

"""

# class PrimeListException(Exception):
#     pass
#
# class PrimeList:
#     def __init__(self):
#         self.data = [2]
#
#     def __getitem__(self, index):
#         if index < len(self.data):
#             return self.data[index]
#         else:
#             while len(self.data) <= index:
#                 n = self.data[-1] + 1
#                 while not all(n % d for d in self.data):
#                     n += 1
#                 self.data.append(n)
#             return self.data[index]
#
#     def __setitem__(self, index, value):
#         raise PrimeListException("List is read-only")


# class PrimeListException(Exception):
# 	def __init__(self, message):
# 		self.__message = message
#
#
# 	def __str__(self):
# 		return self.__message

#with dictionary instance
# class PrimeList:
# 	def __init__(self):
# 		self.__data = {0: 2}
# 		self.__last_prime = 2
#
# 	def __getitem__(self, ord):
# 		if ord in self.__data:
# 			return self.__data.get(ord)
# 		else:
# 			last_prime = self.__last_prime + 1 if self.__last_prime % 2 == 0 else self.__last_prime + 2
# 			count = len(self.__data)
# 			while count <= ord:
# 				ok = 1
# 				d = 2
# 				n = last_prime
#
# 				while n > 1 and ok:
# 					if n % d == 0:
# 						ok = 0
# 					while n % d == 0:
# 						n /= d
# 					d += 1
# 					if d * d > n and n > 1:
# 						n = 1
#
# 				if ok:
# 					self.__data[count] = last_prime
# 					count += 1
#
# 				last_prime += 2
#
# 			self.__last_prime = self.__data[ord]
# 			return self.__data.get(ord)
#
# 	def __setitem__(self, pos, val):
# 		raise PrimeListException("List is read only")

#with list instance
# from math import sqrt
#
# class PrimeList:
# 		def __init__(self):
# 			self.__data = [2]
#
# 		def __getitem__(self, pos):
# 			if pos < len(self.__data):
# 				return self.__data[pos]
# 			else:
# 				last_prime = self.__data[-1] + 1 if self.__data[-1] % 2 == 0 else self.__data[-1] + 2
# 				count = len(self.__data)
# 				while count <= pos:
# 					d = 2
# 					n = last_prime
# 					ok = 1
#
# 					for i in range(2, int(sqrt(n)) + 1):
# 						if n % i == 0:
# 							ok = 0
# 							break
#
# 					if ok:
# 						self.__data.append(last_prime)
# 						count += 1
#
# 					last_prime += 2
#
# 				return self.__data[pos]
#
# 		def __setitem__(self, pos, val):
# 			raise PrimeListException("List is read only")
#
# data = PrimeList()
# for i in range(10):
#     print(data[i])
# print(data[100])
# try:
#     data[5] = 10
# except PrimeListException as ple:
#     print(ple)

"""
Analyse the time complexity of the following function

def f(n):
	sum = 0
	for i in range(1, n ** 3):
		aux = 0
		while i != 0:
			aux += i % 2
			i // = 10
		sum += aux
	return sum
	
Time complexity:
The for loop is executed of n^3 times, and the while loop is executed of log_10(i) times
Therefore, the time complexity of the function is O(n^3 * log(n))
"""

"""
USe dynamic programming to describe the solution for the following problem.
For a given set of coin denominations, determine the smallest number of coins that must be used to return a sum of money
Describe the mathematical formula used to build the solution.
Build the required auxiliary data structure and use it to determine the solution for sum = 13 and coin denominations of value 1,2,5,10
In this case the solution is 3 coins (1 each of denominations 10, 2, and 1)

Use the previously built table to describe how the principle of optimality works in the case of this problem

Solution:
The dynamic programming solution for this problem is to build a table dp where dp[i] holds the minimum number of coins needed to return the sum i.
The mathematical formula used to build the solution is:
dp[i] = min(dp[i], dp[i - coin] + 1) for each coin in the set of coin denominations
The principle of optimality works in this case because the solution for the sum i depends on the solutions for the sums i - coin for each coin in the set of coin denominations.
The solution for the sum i is the minimum number of coins needed to return the sum i, and it is built based on the solutions for the sums i - coin.
Therefore, the principle of optimality states that the optimal solution for the sum i is built based on the optimal solutions for the subproblems i - coin.

----------------------------------------------------------------------------------------------------------------------------

We will use auxiliary data, a list dp[] to store the minimum number of coins that must be used to obtain a certain value. 
We will initialize the dp[1], dp[2], dp[5] and dp[10] with 1 because for these sums of money, we have a coin of that value which can be used. 
For the rest of the values, we will imagine our data structure as a table with one row where we store the data. 
We know that a sum of money can be returned by using a coin of value 1, 2, 5 or 10, so when we calculate the minimum number of coins that must be used to return a certain sum, 
we will look in our table with 1, 2, 5 or 10 steps behind and choose the minimum value between these 4 and add 1 to it.

dp[i] = min(dp[i-1], dp[i-2], dp[i-5], dp[i-10]) + 1

for coin in (1, 2, 5, 10):
	dp[coin] = 1		#to initialize the base cases
	
for coin in (1, 2, 5, 10):
	dp[i] = min(dp[i], dp[i - coin] + 1)	#to calculate the minimum number of coins needed to return the sum i
	
The principle of optimality works in this case because the optimal solution for the sum i depends on the optimal solutions for the sums i - coin for each coin in the set of coin denominations.
"""

