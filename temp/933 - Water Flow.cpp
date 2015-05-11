#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

map<string, int> R;
vector<int> RN;
void parse_equ(string exp) {
    char s[10];
    int val;
    sscanf(exp.c_str(), "%[a-zA-Z]=%d", s, &val);
    RN.push_back(val);
    R[s] = val;
}
void parse_exp(string exp) {
    size_t pos = exp.find(";");
    if (pos == string::npos) {
        parse_equ(exp);
        return ;
    }
    parse_exp(exp.substr(0, pos));
    parse_exp(exp.substr(pos+1));
}
int readLine() {
    string line;
    if (!getline(cin, line))
        return 0;
    parse_exp(line);
    return 1;
}
int main() {
    {
        readLine();
        readLine();
        readLine();
        int N = RN[0], A[26], V[26];
        int sumA = 0;
        for (int i = 0; i < N; i++)
            A[i] = RN[i+1], sumA += A[i];
        for (int i = 0; i < N-1; i++)
            V[i] = RN[i+N+1];
        
        printf("%3c", 't');
        for (int i = 0; i < N; i++)
            printf("%4c", i + 'A');
        puts("");
        printf("---");
        for (int i = 0; i < N; i++)
            printf("----");
        puts("");
        
        int time = 0;
        do {
            printf("%3d", time);
            for (int i = 0; i < N; i++)
                printf("%4d", A[i]);
            puts("");
            if (A[N-1] == sumA)
                break;
            for (int i = N-1; i >= 1; i--) {
                int f = min(A[i-1], V[i-1]);
                A[i] += f, A[i-1] -= f;
            }
            time++;
        } while (true);
        
        R.clear();
        RN.clear();
    }
    return 0;
}

/*
N=3
A=11;B=0;C=0
a=5;b=4
 
N=3
A=11;B=0;C=0
a=5;c=4
*/