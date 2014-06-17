#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;
struct E {
    string A, B, C; // A (C) B
};
map<string, E> R;
string dfs(string val) {
    E &v = R[val];
    string ret = "", right, left;
    if(v.A[0] >= '0' && v.A[0] <= '9')
        left = v.A;
    else
        left = dfs(v.A);
    if(v.B[0] >= '0' && v.B[0] <= '9')
        right = v.B;
    else
        right = dfs(v.B);
    if(v.C == "+") {
        ret = left + "+";
        if(v.B[0] >= '0' && v.B[0] <= '9')
            ret = ret + right;
        else
            ret = ret + "(" + right + ")";
    } else { // v.C == "*"
        int i, flag = 0, l = 0, flag2 = 0;
        for(i = 0; i < left.length() && !flag; i++) {
            if(left[i] == '(')  l++;
            if(left[i] == ')')  l--;
            if(l == 0 && left[i] == '+')
                flag = 1;
        }
        if(flag)
            ret = "(" + left + ")*";
        else
            ret = left + "*";
        i, l = 0;
        for(i = 0; i < right.length() && !flag; i++) {
            if(right[i] == '(')  l++;
            if(right[i] == ')')  l--;
            if(l == 0 && right[i] == '+')
                flag2 = 1;
        }
        if(flag == 0 && flag2 == 0)
            ret = ret + "(" + right + ")";
        else
            ret = ret + right;
    }
    return ret;
}
int main() {
    int testcase, cases = 0;
    int n, i;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        R.clear();
        char s1[50], s2[50], s3[50], s4[50];
        E tmp;
        for(i = 0; i < n; i++) {
            scanf("%s = %s %s %s", s1, s2, s3, s4);
            tmp.A = s2, tmp.B = s4;
            tmp.C = s3;
            R[s1] = tmp;
        }
        printf("Expression #%d: ", ++cases);
        cout << dfs(s1);
        puts("");
    }
    return 0;
}
