#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <ctype.h>
using namespace std;

int main() {
    string s;
    while(getline(cin, s)) {
        if(s.substr(0, 20) == "****END_OF_INPUT****")
            return 0;
        map<string, int> r;
        int lambda = 0;
        do {
            if(s == "****END_OF_TEXT****")
                break;
            int i, len = s.length();
            for(i = 0; i < len; i++) {
                if(!isalpha(s[i]))
                    continue;
                string word = "";
                int j(i);
                while(j < len) {
                    bool flag = false;
                    switch(s[j]) {
                        case ',':break;
                        case '.':break;
                        case ':':break;
                        case ';':break;
                        case '!':break;
                        case '?':break;
                        case '\"':break;
                        case '\t':break;
                        case '(':break;
                        case ')':break;
                        case ' ':break;
                        case '\n':break;
                        case EOF:break;
                        case '\0':break;
                        default:
                            if(isupper(s[j]))
                                s[j] += 32;
                            word += s[j];
                            flag = true;
                    }
                    if(!flag)
                        break;
                    j++;
                }
                //cout << word << endl;
                i = j;
                lambda++;
                r[word]++;
            }
        } while(getline(cin, s));
        double Et = 0, Emax = log10(lambda);
        for(map<string, int>::iterator it = r.begin(); it != r.end(); it++) {
            Et += it->second*(log10(lambda)-log10(it->second));
        }
        Et /= lambda;
        if(lambda == 0)
            puts("0 0.0 0");
        else
            printf("%d %.1lf %.0lf\n", lambda, Et, Et*100/Emax);
    }
    return 0;
}
