#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stack>
using namespace std;
struct data {
    vector<vector<int> > KIND1;
    vector<vector<string> > KIND2;
};
char input[] = "1 1 2\n1 1 3\n2 4 4 9 5 11\n3 3 4 10 11\n4 1 6\n\
5 1 6\n6 2 15 7\n7 1 12\n7 2 8 12\n8 1 16\n8 2 17 16\n9 1 13\n\
9 2 17 13\n10 1 14\n10 2 17 14\n11 2 18 6\n11 1 19\n12 1 man\n\
12 1 dog\n12 1 fish\n12 1 computer\n12 1 waves\n13 1 struck 13 1 saw\n\
13 1 bit\n13 1 took\n14 1 slept\n14 1 jumped\n14 1 walked\n\
14 1 swam\n15 1 the\n15 1 a\n16 1 green\n16 1 small\n16 1 rabid\n\
16 1 quick\n17 1 nearly\n17 1 suddenly\n17 1 restlessly\n\
18 1 on\n18 1 over\n18 1 through\n";
char start[20][20] = {
    "", "sentence", "trans-sentence", "intrans-sentence",
    "subject", "object", "noun-phrase", "modified-noun",
    "modifier", "verb-phrase", "intrans-verb-phrase",
    "prep-phrase", "noun", "trans-verb", "intrans-verb",
    "article", "adjective", "adverb", "preposition", "empty"
};
/*
<sentence> 1>(2 | 3)
<trans-sentence> 2>(4 9 5 11)
<intrans-sentence> 3>(4 10 11)
<subject> 4>(6)
<object> 5>(6)
<noun-phrase> 6>(15 7)
<modified-noun> 7>(12 | 8 12)
<modifier> 8>(16 | 17 16)
<verb-phrase> 9>(13 | 17 13)
<intrans-verb-phrase> 10>(14 | 17 14)
<prep-phrase> 11>(18 6 | 19)
<noun> 12> man | dog | fish | computer | waves
<trans-verb> 13> struck | saw | bit | took
<intrans-verb> 14> slept | jumped | walked | swam
<article> 15> the | a
<adjective> 16>green | small | rabid | quick
<adverb> 17>nearly | suddenly | restlessly
<preposition> 18>on | over | through
<empty> 19>""
*/
int main() {
    data CH[20];
    int n, m, num;
    stringstream sin(input);
    while(sin >> n) {
        sin >> m;
        vector<int> buf1;
        vector<string> buf2;
        string token;
        while(m--) {
            sin >> token;
            if(token[0] >= '0' && token[0] <= '9') {
                stringstream nin(token);
                nin >> num;
                buf1.push_back(num);
            } else {
                buf2.push_back(token);
            }
        }
        if(buf1.size())
            CH[n].KIND1.push_back(buf1);
        if(buf2.size())
            CH[n].KIND2.push_back(buf2);
    }
    vector<string> buf2;
    buf2.push_back("");
    CH[19].KIND2.push_back(buf2);
    int k = 0, i, j;
    char s[50];
    while(scanf("%s", s) == 1) {
        int st = 0, x, y;
        for(i = 1; i <= 19; i++) {
            if(!strcmp(start[i], s))
                st = i, i = 20;
        }
        stack<int> stk;
        stk.push(st);
        int spaceflag = 0;
        while(!stk.empty()) {
            x = stk.top(), stk.pop();
            if(CH[x].KIND1.size()+CH[x].KIND2.size() > 1)
                    k++;
            if(CH[x].KIND1.size() == 0) {
                y = k%CH[x].KIND2.size();
                if(spaceflag && CH[x].KIND2[y][0].length())   putchar(' ');
                if(CH[x].KIND2[y][0].length())
                    spaceflag = 1;
                printf("%s", CH[x].KIND2[y][0].c_str());
            } else {
                y = k%CH[x].KIND1.size();
                //printf("ch %d\n", y);
                for(j = CH[x].KIND1[y].size()-1; j >= 0; j--)
                    stk.push(CH[x].KIND1[y][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
