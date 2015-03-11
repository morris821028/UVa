from collections import defaultdict
class Friends:
    def __init__(self, connections):
        self.graph = defaultdict(list)
        for w in connections:
            w = list(w)
            self.graph[w[0]].append(w[1])
            self.graph[w[1]].append(w[0])

    def add(self, connection):
        p = list(connection)
        if p[1] in self.graph[p[0]] or p[0] in self.graph[p[1]]:
            return False
        self.graph[p[0]].append(p[1])
        self.graph[p[1]].append(p[0])
        return True

    def remove(self, connection):
        p = list(connection)
        if p[0] not in self.graph[p[1]]:
            return False
        self.graph[p[0]].remove(p[1])
        self.graph[p[1]].remove(p[0])
        return True

    def names(self):
        txt = set()
        for key, value in self.graph.items():
            if len(value) > 0:
                txt.add(key)
        return txt

    def connected(self, name):
        return set(self.graph[name])



if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    letter_friends = Friends(({"a", "b"}, {"b", "c"}, {"c", "a"}, {"a", "c"}))
    digit_friends = Friends([{"1", "2"}, {"3", "1"}])
    assert letter_friends.add({"c", "d"}) is True, "Add"
    assert letter_friends.add({"c", "d"}) is False, "Add again"
    assert letter_friends.remove({"c", "d"}) is True, "Remove"
    assert digit_friends.remove({"c", "d"}) is False, "Remove non exists"
    assert letter_friends.names() == {"a", "b", "c"}, "Names"
    assert letter_friends.connected("d") == set(), "Non connected name"
    assert letter_friends.connected("a") == {"b", "c"}, "Connected name"
