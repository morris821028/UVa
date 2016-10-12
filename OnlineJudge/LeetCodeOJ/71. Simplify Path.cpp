class Solution {
public:
    string simplifyPath(string path) {
        int n = path.length();
        for (int i = 0; i < n; i++) {
            if (path[i] == '/')
                path[i] = ' ';
        }
        stringstream sin(path);
        string token;
        deque<string> dir;
        while (sin >> token) {
            if (token == ".")
                continue;
            if (token == "..") {
                if (!dir.empty())
                    dir.pop_back();
            } else {
                dir.push_back(token);
            }
        }
        string ret = "";
        while (!dir.empty()) {
            string dd = dir.front();
            dir.pop_front();
            ret += "/" + dd;
        }
        if (ret == "")  ret = "/";
        return ret;
    }
};
