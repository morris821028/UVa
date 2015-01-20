#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    string line;
    vector< vector<string> > ret;
    int mx[256] = {};
    while (getline(cin, line)) {
        stringstream sin(line);
        vector<string> v;
        string x;
        while (sin >> x) {
            v.push_back(x);
            mx[v.size()] = max(mx[v.size()], (int) x.length());
        }
        ret.push_back(v);
    }
    for (int i = 1; i < 256; i++)
        mx[i] += mx[i - 1] + 1;
    for (int i = 0; i < ret.size(); i++) {
        vector<string> &v = ret[i];
        int pos = 0;
        for (int j = 0; j < v.size(); j++) {
            while (pos < mx[j]) putchar(' '), pos++;
            printf("%s", v[j].c_str());
            pos += v[j].length();
        }
        puts("");
    }
    return 0;
}