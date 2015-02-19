#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
#define MAXN 1024
int isOperator(char c) {
    switch (c) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
    }
    return 0;
}
int oneItemPlus(string exp) { // x+x-x/x*x*x
    int p = 0;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            p++;
        } else if (exp[i] == ')') {
            p--;
        } else if (isOperator(exp[i]) && p == 0) {
            if (exp[i] == '-' || exp[i] == '+')
                return 1;
        }
    }
    return 0;
}
string flipOperator(string exp, int flip) {
    int p = 0;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            p++;
        } else if (exp[i] == ')') {
            p--;
        } else if (isOperator(exp[i]) && p == 0) {
            if (flip == 1) {
                if (exp[i] == '+')
                    exp[i] = '-';
                else if (exp[i] == '-')
                    exp[i] = '+';
            } else if (flip == 2) {
                if (exp[i] == '*')
                    exp[i] = '/';
                else if (exp[i] == '/')
                    exp[i] = '*';
            }
        }
    }
    return exp;
}
string parsing(string exp) {
    if (exp.length() <= 1)
        return exp;
    string ret, left, right;
    int p = 0;
    int pos = -1, wp = 0x3f3f3f3f;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            p++;
        } else if (exp[i] == ')') {
            p--;
        } else if (isOperator(exp[i])) {
            if (p == 0) {
                if (isOperator(exp[i]) <= wp) {
                    wp = isOperator(exp[i]);
                    pos = i;
                }
            }
        }
    }
    if (pos == -1)
        return parsing(exp.substr(1, exp.length() - 2));
    left = exp.substr(0, pos);
    right = exp.substr(pos+1);
    
    left = parsing(left);
    right = parsing(right);
    if (exp[pos] == '+') {
        ret = left + exp[pos] + right;
    } else if (exp[pos] == '-') {
        right = flipOperator(right, 1);
        ret = left + exp[pos] + right;
    } else if (exp[pos] == '*') {
        if (oneItemPlus(left)) {
            left = '(' + left + ')';
        }
        if (oneItemPlus(right)) {
            right = '(' + right + ')';
        }
        ret = left + exp[pos] + right;
    } else if (exp[pos] == '/') {
        if (oneItemPlus(left)) {
            left = '(' + left + ')';
        }
        if (oneItemPlus(right)) {
            right = '(' + right + ')';
        } else {
            right = flipOperator(right, 2);
        }
        ret = left + exp[pos] + right;
    }
//    cout << exp << endl;
//    cout << "left: " << left << endl;
//    cout << "right: " << right << endl;
//    cout << "return : " << ret << endl;
    return ret;
}
int main() {
    string exp;
    while (cin >> exp) {
        string ret = parsing(exp);
        cout << ret << endl;
    }
    return 0;
}
/*
 (z*z*g/f)/(p*(t))
 (z*z*g/f)/(p+(t))
 (z*z*g/f)-(p+(t))
 (a+b)/t
 c-(a+b-c)
 a+b-c+(a+b-c)
 m*n/(e-h-f*c/n)
 (r+f*(j))/((z)/g*h*s+x*i)
 ((a-b)-(c-d)-(z*z*g/f)/(p*(t))*((y-u)))
 */
