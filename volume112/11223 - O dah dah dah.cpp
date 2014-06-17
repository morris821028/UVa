#include <iostream>
#include <map>
#include <ctype.h>
using namespace std;

int main() {
    map<string, char> r;
    r[".-"] = 'A', r["-..."] = 'B', r["-.-."] = 'C';
    r["-.."] = 'D', r["."] = 'E', r["..-."] = 'F';
    r["--."] = 'G', r["...."] = 'H', r[".."] = 'I';
    r[".---"] = 'J', r["-.-"] = 'K', r[".-.."] = 'L';
    r["--"] = 'M', r["-."] = 'N', r["---"] = 'O';
    r[".--."] = 'P', r["--.-"] = 'Q', r[".-."] = 'R';
    r["..."] = 'S', r["-"] = 'T', r["..-"] = 'U';
    r["...-"] = 'V', r[".--"] = 'W', r["-..-"] = 'X';
    r["-.--"] = 'Y', r["--.."] = 'Z', r["-----"] = '0';
    r[".----"] = '1', r["..---"] = '2', r["...--"] = '3';
    r["....-"] = '4', r["....."] = '5', r["-...."] = '6';
    r["--..."] = '7', r["---.."] = '8', r["----."] = '9';
    r[".-.-.-"] = '.', r["--..--"] = ',', r["..--.."] = '?';
    r[".----."] = '\'', r["-.-.--"] = '!', r["-..-."] = '/';
    r["-.--."] = '(', r["-.--.-"] = ')', r[".-..."] = '&';
    r["---..."] = ':', r["-.-.-."] = ';', r["-...-"] = '=';
    r[".-.-."] = '+', r["-....-"] = '-', r["..--.-"] = '_';
    r[".-..-."] = '\"', r[".--.-."] = '@';
    int t, cases = 0;
    string in;
    cin >> t;
    cin.ignore(100, '\n');
    while(t--) {
        cases++;
        cout << "Message #" << cases << endl;
        getline(cin, in);
        int len = in.length(), cnt = 0;
        for(int i = 0; i < len; i++) {
            if(isspace(in[i])) {
                if(cnt == 1) {
                    cout << ' ';
                    cnt = 0;
                } else
                    cnt++;
                continue;
            }
            int j = i;
            string s = "";
            while(!isspace(in[j]) && j < len) {
                s += in[j];
                j++;
            }
            cout << r[s];
            cnt = 0;
            i = j-1;
        }
        cout << endl;
        if(t)
            cout << endl;

    }
    return 0;
}
