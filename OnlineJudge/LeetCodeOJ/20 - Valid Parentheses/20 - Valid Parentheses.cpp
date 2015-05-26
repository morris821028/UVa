class Solution {
public:
    char inv(char c) {
        switch(c) {
            case ')': return '(';
            case ']': return '[';
            case '}': return '{';
            case '(': return ')';
            case '[': return ']';
            case '{': return '}';
        }
        return '?';
    }
    bool isValid(string s) {
        stack<char> stk;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stk.push(s[i]);
            } else {
                if (!stk.empty() && stk.top() == inv(s[i]))
                    stk.pop();
                else
                    return false;
            }
        }
        return stk.empty();
    }
};
