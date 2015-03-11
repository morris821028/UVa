def checkio(str_number, radix):
    x = 0
    for w in str_number:
        v = 0
        if w.isalpha():
            v = ord(w) - ord('A') + 10
        elif w.isdigit():
            v = ord(w) - ord('0')
        else:
            return -1
        if v >= radix:
            return -1
        x = x * radix + v
    return x

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio("AF", 16) == 175, "Hex"
    assert checkio("101", 2) == 5, "Bin"
    assert checkio("101", 5) == 26, "5 base"
    assert checkio("Z", 36) == 35, "Z base"
    assert checkio("AB", 10) == -1, "B > A > 10"
