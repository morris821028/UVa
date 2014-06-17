#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;
map<string, int> R2N;
map<int, string> N2R;
string NtoR(int num) {
    const string ch[] = {"M", "CM", "D", "CD", "C", "XC", "L",
                "XL", "X", "IX", "V", "IV", "I"};
    const int val[] = {1000, 900, 500, 400, 100, 90, 50,
                40, 10, 9, 5, 4, 1};
    string ans = "";
    for(int i = 0; i < 13; i++) {
        while(num >= val[i]) {
            num -= val[i];
            ans += ch[i];
        }
    }
    return ans;
}
int main() {
    int i;
    string tmp;
    for(i = 1; i <= 100; i++) {
        tmp = NtoR(i);
        N2R[i] = tmp;
        R2N[tmp] = i;
    }
    while(cin >> tmp) {
        if(tmp == "#")  break;
        int pos1 = tmp.find('+'), pos2 = tmp.find('=');
        string a = tmp.substr(0, pos1);
        string b = tmp.substr(pos1+1, pos2-pos1-1);
        string c = tmp.substr(pos2+1);
        if(N2R[R2N[a]+R2N[b]] == c)
            cout << "Correct ambiguous" << endl;
        cout << a <<" "<< b <<" "<< c << endl;
    }
    return 0;
}
