#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

map<string, string> morse;
map<string, string> dict;
int dist(string s1, string s2) {
    if (s1 == s2)   return 0;
    if (s1.length() > s2.length())
        swap(s1, s2);
    if (s1 != s2.substr(0, s1.length()))    return 0x3f3f3f3f;
    return (int) (s2.length() - s1.length());
}
string encode(string s) {
    string ret = "";
    for (int i = 0; i < s.length(); i++)
        ret += morse[string(1, s[i])];
    return ret;
}
string decode(string s) {
    string ret = dict.begin()->first;
    int mn = 0x3f3f3f3f;
    for (map<string, string>::iterator it = dict.begin();
         it != dict.end(); it++) {
        int d = dist(it->second, s);
        if (d < mn) {
            mn = d, ret = it->first;
        } else if (d == mn && d == 0 && *ret.rbegin() != '!') {
            ret += "!";
        }
    }
    if (mn)
        ret += "?";
    return ret;
}
int main() {
    string s1, s2;
    while (cin >> s1 && s1 != "*") {
        cin >> s2;
        morse[s1] = s2;
    }
    while (cin >> s1 && s1 != "*")
        dict[s1] = encode(s1);
    while (cin >> s1 && s1 != "*")
        cout << decode(s1) << endl;
    return 0;
}
/*
 A       .-
 B       -...
 C       -.-.
 D       -..
 E       .
 F       ..-.
 G       --.
 H       ....
 I       ..
 J       .---
 K       -.-
 L       .-..
 M       --
 N       -.
 O       ---
 P       .--.
 Q       --.-
 R       .-.
 S       ...
 T       -
 U       ..-
 V       ...-
 W       .--
 X       -..-
 Y       -.--
 Z       --..
 0       ------
 1       .-----
 2       ..---
 3       ...--
 4       ....-
 5       .....
 6       -....
 7       --...
 8       ---..
 9       ----.
 *
 AN
 EARTHQUAKE
 EAT
 GOD
 HATH
 IM
 READY
 TO
 WHAT
 WROTH
 *
 .--.....--   .....--....
 --.----..   .--.-.----..
 .--.....--   .--.
 ..-.-.-....--.-..-.--.-.
 ..--   .-...--..-.--
 ----        ..--
 *
*/