#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <ctype.h>
using namespace std;
map<string, int> DSIZE;
map<string, map<int, int> > DR;
int testBug;
void declara(char exp[]) {
    string name = "";
    int size = 0, i;
    for (i = 0; exp[i] != '['; i++)
        name += exp[i];
    for (i++; exp[i] != ']'; i++)
        size = size * 10 + exp[i] - '0';
//    cout <<"DECL "<< name << " " << size << endl;
    DSIZE[name] = size;
    DR[name].clear();
}
int getValue(char exp[]) {
    if (isdigit(exp[0])) {
        int value = 0;
        for (int i = 0; isdigit(exp[i]); i++)
            value = value * 10 + exp[i] - '0';
        return value;
    }
    string name = "";
    int i;
    for (i = 0; exp[i] != '['; i++)
        name += exp[i];
    int index = getValue(exp + i + 1);
    if (DSIZE.count(name) == 0 || index >= DSIZE[name] || DR[name].count(index) == 0) {
        testBug = 1;
        return 0;
    }
    return DR[name][index];
}
void assign(char exp[]) {
    string name = "";
    int i;
    for (i = 0; exp[i] != '['; i++)
        name += exp[i];
    int index = getValue(exp + i + 1);
    for (i = 0; exp[i] != '='; i++);
    int value = getValue(exp + i + 1);
    if (testBug)    return;
    if (DSIZE.count(name) == 0 || index >= DSIZE[name]) {
        testBug = 1;
        return;
    }
//    cout << "ASSIGN " << name << " " << index << " " << value << endl;
    DR[name][index] = value;
}
int main() {
    char c;
    while ((c = getchar()) != '.') {
        ungetc(c, stdin);
        DSIZE.clear();
        DR.clear();
        char exp[32767];
        int bugLine = 0, lines = 0;
        testBug = 0;
        while (gets(exp) && exp[0] != '.') {
            lines++;
            int f = 0;
            for (int i = 0; exp[i]; i++)
                f |= exp[i] == '=';
            if (!f)
                declara(exp);
            else
                assign(exp);
            if (testBug && bugLine == 0)
                bugLine = lines;
        }
        printf("%d\n", bugLine);
    }
    return 0;
}
/*
 a[3]
 a[0]=a[1]
 .
 x[1]
 x[0]=x[0]
 .
 a[0]
 a[0]=1
 .
 b[2]
 b[0]=2
 b[1]=b[b[0]]
 b[0]=b[1]
 .
 g[2]
 G[10]
 g[0]=0
 g[1]=G[0]
 .
 a[2147483647]
 a[0]=1
 B[2]
 B[a[0]]=2
 a[B[a[0]]]=3
 a[2147483646]=a[2]
 . 
 .
*/