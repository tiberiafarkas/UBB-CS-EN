def is_prime(nr):
    """
    function that tests whether the number is prime or not
    intput: nr - integer number
    output: True or False
    """
    if nr == 0 or nr == 1:
        return False
    if nr == 2:
        return True
    if nr % 2 == 0:
        return False
    if nr < 0:
        return False

    for i in range(3, int(nr ** 0.5 + 1), 2):
        if nr % i == 0:
            return False

    return True

def test_is_prime():
    assert(is_prime(-23) == False)
    assert(is_prime(0) == False)
    assert(is_prime(1) == False)
    assert(is_prime(2) == True)
    assert(is_prime(8) == False)
    assert(is_prime(17))
    assert(is_prime(9) == False)

test_is_prime()