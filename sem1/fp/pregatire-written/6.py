"""
Create an iterable data structure and a Product class with attributes name, type and price.
Write a generic sort function having n*log(n) time complexity.
Create an instance of the iterable data structure and add 10 products to it. Use your sort function implementation to sort the list:
o Alphabetically by product name
o Decreasing by price
"""

def MergeSort(data, comp, start, end):
    if start == end:
        return

    mid = start + (end - start) // 2

    MergeSort(data, comp, start, mid)
    MergeSort(data, comp, mid + 1, end)

    left = data[start:mid + 1]
    right = data[mid + 1:end + 1]

    left_index = 0
    right_index = 0
    data_index = start

    while left_index < len(left) and right_index < len(right):
        if comp == 1:
            if left[left_index].name < right[right_index].name:
                data[data_index] = left[left_index]
                left_index += 1
            else:
                data[data_index] = right[right_index]
                right_index += 1

        elif comp == -1:
            if left[left_index].price > right[right_index].price:
                data[data_index] = left[left_index]
                left_index += 1
            else:
                data[data_index] = right[right_index]
                right_index += 1

        data_index += 1

    while left_index < len(left):
        data[data_index] = left[left_index]
        left_index += 1
        data_index += 1

    while right_index < len(right):
        data[data_index] = right[right_index]
        right_index += 1
        data_index += 1

class Iterator:
    def __init__(self, data):
        self.__data = data
        self.__index = -1

    def __next__(self):
        self.__index += 1
        if self.__index >= len(self.__data):
            raise StopIteration()

        return self.__data[self.__index]

class Product:
    def __init__(self, name, type, price):
        self.name = name
        self.type = type
        self.price = price

    def __str__(self):
        return f"{self.name} {self.type} {self.price}"

class ProductList:
    def __init__(self):
        self.products = []

    def add(self, product):
        self.products.append(product)

    def sort(self, comp, key):
        if key == "sort_by_name":
            MergeSort(self.products, comp, 0, len(self.products) - 1)
            return self.products
        elif key == "sort_by_price":
            MergeSort(self.products, comp, 0, len(self.products) - 1)
            return self.products

    def __iter__(self):
        return Iterator(self.products)

def sort_by_name(product):
    return product.name

def sort_by_price(product):
    return product.price

pl = ProductList()
pl.add(Product("ice cream", "sweet", 9))
pl.add(Product("apple", "fruit", 2))
pl.add(Product("carrot", "vegetable", 3))
pl.add(Product("banana", "fruit", 1))
pl.add(Product("date", "fruit", 4))
pl.add(Product("fig", "fruit", 6))
pl.add(Product("grape", "fruit", 7))
pl.add(Product("eggplant", "vegetable", 5))
pl.add(Product("honey", "sweet", 8))
pl.add(Product("jelly", "sweet", 10))

print("sort by name")
data = pl.sort(1, "sort_by_name")
for p in data:
    print(p)

print()
print("sort by price")
data = pl.sort(-1, "sort_by_price")
for p in pl:
    print(p)
