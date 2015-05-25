class Solution {
public:
    bool isPalindrome(int x) {
        char buf[32];
        sprintf(buf, "%d", x);
        
        bool ret = true;
        for (int i = 0, j = strlen(buf)-1; i < j; i++, j--)
            ret &= buf[i] == buf[j];
            
        return ret;
    }
};
