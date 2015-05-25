class Solution:
    # @param {integer} n
    # @return {integer}
    def sieve(self, n):
        (mark, ret) = ([True] * (n + 2), 0)
        for i in xrange(2, n):
            if mark[i]:
                ret += 1
                
                k = n/i
                j = i*k;
                while k >= i:
                    mark[j] = False
                    k -= 1
                    j -= i
                
        return ret
        
    def countPrimes(self, n):
        return self.sieve(n)