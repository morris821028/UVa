#include <cstdio>
#include <iostream>
#include <sstream>
#include <ctype.h>
using namespace std;
int main() {
    string D[10000], country[10000];
    int $_dol[10000];
    int Idx = 0;
    while(cin >> D[Idx]) {
        if(D[Idx] == "000000")
            break;
        country[Idx] = "";
        char c;
        while(c = getchar()) {
            if(!isspace(c))
                break;
        }
        country[Idx] += c;
        while(c = getchar()) {
            if(c == '\n')
                break;
            country[Idx] += c;
        }
        int pos = country[Idx].find('$', 0);
        stringstream sin;
        sin << country[Idx].substr(pos+1);
        sin >> $_dol[Idx];
        country[Idx] = country[Idx].substr(0, pos);
        Idx++;
    }
    string call;
    int minute;
    while(cin >> call) {
        if(call == "#")
            break;
        cin >> minute;
        int error = 1;
        if(call[0] != '0') {
            error = 0;
            printf("%-16s%-15s%20s%5d  0.00   0.00\n", call.c_str(), "Local",
                           call.c_str(), minute);
        }
        for(int i = 0; i < Idx; i++) {
            //cout << call.substr(0, D[i].length()) << "|" << endl;
            if(call.substr(0, D[i].length()) == D[i]) {
                int len = call.substr(D[i].length()).length();
                //cout << call.substr(D[i].length()) << "|" << len<<  endl;
                if(call[1] == '0' && (len < 4 || len > 10)) {
                    //puts("error");
                    break;
                } else if(call[1] != '0' && (len < 4 || len > 7)) {
                    //puts("error2");
                    break;
                } else {
                    error = 0;
                    printf("%-16s%-25s%10s%5d%6.2lf%7.2lf\n", call.c_str(), country[i].c_str(),
                           call.substr(D[i].length()).c_str(), minute, $_dol[i]/100.0, $_dol[i]/100.0*minute);
                    break;
                }
            }
        }
        if(error) {
            printf("%-16s%-25s%21d%7.2lf\n", call.c_str(), "Unknown", minute, -1.00);
        }
    }
    return 0;
}
/**
031526          Arrowtown                      1526   22  0.38   8.36
031526          Arrowtown                      1526   22  0.38   8.36
*/
