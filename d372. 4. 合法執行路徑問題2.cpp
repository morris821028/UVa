#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;
int i;
int dfs(int a[], int n) {
    if(a[i] == 1 && a[i+1] == 2 && a[i+2] == 4 && a[i+3] == 5) {
        i += 4;
        if(dfs(a, n) == 0)  return 0;
        if(a[i] == 6) {
            i++;
            if(dfs(a, n) == 0)   return 0;
            if(a[i] == 7 && a[i+1] == 8) {
                i += 2;
                return 1;
            } else  return 0;
        } else  return 0;
    } else if(a[i] == 1 && a[i+1] == 2 && a[i+2] == 3 && a[i+3] == 7 && a[i+4] == 8) {
        i += 5;
        return 1;
    } else  return 0;
}
int check(int a[], int n) {
    if(a[0] == 9 && a[1] == 10 && a[2] == 11) {
        i = 3;
        if(dfs(a, n) == 0)  return 0;
        if(a[i] == 12)  return 1;
        else return 0;
    }
    return 0;
}
int main() {
    string line;
    while(getline(cin, line)) {
        stringstream sin;
        sin << line;
        int a[1000], n = 0;
        while(sin >> a[n])
            n++;
        a[n] = -1;
        if(a[0] == 0)   break;
        printf("%s\n", check(a, n) == 1 ? "valid" : "invalid");
    }
    return 0;
}
