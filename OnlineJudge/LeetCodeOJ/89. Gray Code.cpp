class Solution {
public:
    unsigned int binaryToGray(unsigned int num)
    {
        return num ^ (num >> 1);
    }
    unsigned int grayToBinary(unsigned int num)
    {
        unsigned int mask;
        for (mask = num >> 1; mask != 0; mask = mask >> 1)
            num = num ^ mask;
        return num;
    }
    vector<int> grayCode(int n) {
        vector<int> ret;
        for (int i = 0; i < (1<<n); i++)
            ret.push_back(binaryToGray(i));
        return ret;
    }
};
