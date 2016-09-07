class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int mm[128] = {};
        for (int i = 0; i < magazine.length(); i++)
            mm[magazine[i]]++;
        for (int i = 0; i < ransomNote.length(); i++) {
            mm[ransomNote[i]]--;
            if (mm[ransomNote[i]] == -1)
                return false;
        }
        return true;
    }
};
