def checkio(number):
    number = str(number)
    ret = 1
    for x in number:
        ret *= int(x, 10) if x != '0' else 1
    return ret

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio(123405) == 120
    assert checkio(999) == 729
    assert checkio(1000) == 1
    assert checkio(1111) == 1