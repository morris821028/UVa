#include <iostream>
#include <ctype.h>
using namespace std;
int main() {
    string line, tmp = "";
    int next = 0;
    while(getline(cin, line)) {
        if(line == "#")
            break;
        int i, len = line.length();
        for(i = 0; i < len; i++) {
            if(isspace(line[i])) {
                cout << tmp;
                if(next)
                    cout << endl;
                cout << line[i];
                next = 0;
                tmp = "";
            } else if(isalpha(line[i])) {
                tmp += line[i];
            } else {
                if(line[i] == '-') {
                    if(tmp.length() > 0 && i == len-1) {
                        next = 1;
                    }
                } else {
                    cout << tmp;
                    tmp = "";
                    if(next)
                        cout << endl;
                    next = 0;
                }
            }
        }
        if(next == 0) {
            cout << tmp;
            if(next)
                cout << endl;
            tmp = "";
        }
        cout << endl;
    }
    return 0;
}
