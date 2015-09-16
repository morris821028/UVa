#include <stdio.h>
#include <math.h>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;
map<string, int> R;
int toIndex(string s) {
    if (R.count(s))
        return R[s];
    int v = (int) R.size();
    return R[s] = v;
}
int main() {
    string s1, s2;
    map<pair<int, int>, int> hehe;
    while (cin >> s1) {
        getline(cin, s2);
        string name1, name2;
        int pos = (int) s1.find("->");
        name1 = s1.substr(0, pos);
        name2 = s1.substr(pos+2, s1.length()-pos-3);
        int x = toIndex(name1), y = toIndex(name2);
        if (x > y)  swap(x, y);
        for (int i = 0; i < s2.length(); i++)
            s2[i] = tolower(s2[i]);
        int has = 0;
        stringstream sin(s2);
        while (sin >> s2) {
            if (s2.length()%2 || s2.length() < 4)
                continue;
            int ok = 1;
            for (int i = 0; i < s2.length(); i += 2) {
                ok &= s2[i] == 'h' && s2[i+1] == 'e';
            }
            has |= ok;
        }
        hehe[make_pair(x, y)] = has;
    }
    int a = 0, b = 0;
    for (auto &x : hehe) {
        a += x.second, b ++;
    }
    printf("%d%%\n", (int) round((double) a * 100 / b));
    return 0;
}