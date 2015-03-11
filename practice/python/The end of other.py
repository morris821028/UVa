def checkio(words_set):
    rev = []
    for word in words_set:
        rev.append(word[::-1])
    
    for w1 in rev:
        for w2 in rev:
            if w1 != w2 and w1.find(w2) == 0:
                return True
                
    return False

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio({"hello", "lo", "he"}) == True, "helLO"
    assert checkio({"hello", "la", "hellow", "cow"}) == False, "hellow la cow"
    assert checkio({"walk", "duckwalk"}) == True, "duck to walk"
    assert checkio({"one"}) == False, "Only One"
    assert checkio({"helicopter", "li", "he"}) == False, "Only end"
