#include <stdio.h>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
string num2str(int x) {
    string s;
    stringstream sin(s);
    sin << x;
    return sin.str();
}
int dfs(vector<int> A, int M, string &solution) {
//    printf("[");
//    for (int i = 0; i < A.size(); i++)
//        printf("%d ", A[i]);
//    puts("]");
    int same = 1;
    for (int i = 1; i < A.size(); i++)
        same &= A[i] == A[0];
    if (same == 1) {
        solution = "[" + num2str(A[0]) + "]";
        return 1;
    }
    if (M <= 0)  return 0;
    int g = A[0];
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == 0) {
            g = 0;
            break;
        }
        g = __gcd(g, A[i]);
    }
    for (int i = 1; i < A.size(); i++) {
        if (A[i-1] != 0 && A[i]%A[i-1] != 0)
            g = 0;
        if (A[i-1] == 0 && A[i] != 0)
            g = 0;
    }
    if (g < 0)  g = -g;
    if (g > 0) {
        for (int m = 1; m <= g; m++) {
            if (g%m == 0) {
                vector<int> nA;
                nA.push_back(A[0] / m);
                for (int j = 1; j < A.size(); j++) {
                    if (A[j-1] == 0)
                        nA.push_back(0);
                    else
                        nA.push_back(A[j] / A[j-1]);
                }
                if (dfs(nA, M-1, solution)) {
                    solution = "[" + num2str(m) + "*" + solution + "]";
                    return 1;
                }
                nA.clear();
                nA.push_back(A[0] / (-m));
                for (int j = 1; j < A.size(); j++) {
                    if (A[j-1] == 0)
                        nA.push_back(0);
                    else
                        nA.push_back(A[j] / A[j-1]);
                }
                if (dfs(nA, M-1, solution)) {
                    solution = "[" + num2str(-m) + "*" + solution + "]";
                    return 1;
                }
            }
        }
    }
    vector<int> nA;
    for (int i = 1; i < A.size(); i++)
        nA.push_back(A[i] - A[i-1]);
    if (dfs(nA, M-1, solution)) {
        solution = "[" + num2str(A[0]) + "+" + solution + "]";
        return 1;
    }
    return 0;
}
int main() {
    int M, x;
    string line;
    while (getline(cin, line)) {
        stringstream sin(line);
        sin >> M;
        vector<int> A;
        while (sin >> x)
            A.push_back(x);
        string solution;
        int f = dfs(A, M, solution);
        if (f == 0)
            puts("[0]");
        else
            puts(solution.c_str());
    }
    return 0;
}

/*
 3 10 30 30 -30 90 -450 3150
 2 2 6 36 360 5400 113400
*/