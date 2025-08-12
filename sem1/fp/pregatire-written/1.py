"""
Implement and test the function having the following specification
Compute the sum of even elements in the given list
input:
    l - the list of numbers
output:
    The sum of the even elements in the list

Raises TypeError if parameter l is not a Python list
Raises ValueError if the list does not contain even numbers
"""

def sum_even1(l):
    if type(l) is not list:
        raise TypeError
    if not any(i % 2 == 0 for i in l):
        raise ValueError
    return sum(i for i in l if i % 2 == 0)

#sau

def sum_even2(l):
    if type(l) is not list:
        raise TypeError
    ok = False
    sum = 0
    for i in l:
        if i % 2 == 0:
            ok = True
            sum += i
    if not ok:
        raise ValueError
    return sum

def test_sum_even():
    assert sum_even2([1, 2, 3, 4, 5, 6]) == 12
    assert sum_even2([2, 4, 6]) == 12
    try:
        sum_even2(5)
        assert False
    except TypeError:
        assert True
    try:
        sum_even2([1, 3, 5])
        assert False
    except ValueError:
        assert True

test_sum_even()