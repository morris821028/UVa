class Solution:
    # @param {string} s
    # @param {string} t
    # @return {boolean}
    def isIsomorphic(self, s, t):
        (R1, R2) = (dict(), dict())
        for index, c in enumerate(s):
            R1[c] = t[index]
        for index, c in enumerate(t):
            R2[c] = s[index]
        
        for index in range(len(s)):
            if R1[s[index]] != t[index] or R2[t[index]] != s[index]:
                return False
        
        return True