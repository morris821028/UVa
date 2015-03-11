class BIT: # binary indexed tree
    def __init__(self, n):
        n += 10
        self.size = n
        self.data = [0] * n
 
    def query(self, i):
        s = 0
        while i > 0:
            s += self.data[i]
            i -= i & -i
        return s
 
    def add(self, i, x):
        while i < self.size:
            self.data[i] += x
            i += i & -i 
            
def count_inversion(sequence):
    """
        Count inversions in a sequence of numbers
    """
    cnt = 0
    tree = BIT(512)
    for i, v in enumerate(sequence):
        cnt += i - tree.query(v + 256)
        tree.add(v + 256, 1)
   
    return cnt

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert count_inversion((1, 2, 5, 3, 4, 7, 6)) == 3, "Example"
    assert count_inversion((0, 1, 2, 3)) == 0, "Sorted"
    assert count_inversion((99, -99)) == 1, "Two numbers"
    assert count_inversion((5, 3, 2, 1, 0)) == 10, "Reversed"
