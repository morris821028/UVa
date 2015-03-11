class Building:
    def __init__(self, south, west, width_WE, width_NS, height=10):
        self.lx = south
        self.ly = west
        self.rx = south + width_NS
        self.ry = west + width_WE
        self.h = height

    def corners(self):
        ret = {
            "north-west": [self.rx, self.ly],
            "north-east": [self.rx, self.ry],
            "south-west": [self.lx, self.ly], 
            "south-east": [self.lx, self.ry]
        };
        return ret

    def area(self):
        return (self.rx - self.lx) * (self.ry - self.ly)

    def volume(self):
        return self.area() * self.h

    def __repr__(self):
        val = str(self.lx) + ', ' + str(self.ly) + ', '
        val += str(self.ry - self.ly) + ', ' + str(self.rx - self.lx) + ', '
        val += str(self.h)
        ret = "Building(" + val + ")"
        return ret


if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    def json_dict(d):
        return dict((k, list(v)) for k, v in d.items())

    b = Building(1, 2, 2, 3)
    b2 = Building(1, 2, 2, 3, 5)
    assert json_dict(b.corners()) == {'north-east': [4, 4], 'south-east': [1, 4],
                                      'south-west': [1, 2], 'north-west': [4, 2]}, "Corners"
    assert b.area() == 6, "Area"
    assert b.volume() == 60, "Volume"
    assert b2.volume() == 30, "Volume2"
    assert str(b) == "Building(1, 2, 2, 3, 10)", "String"
