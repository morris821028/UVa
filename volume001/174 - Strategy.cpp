#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
#include <map>
#include <assert.h>
#include <string.h>
#include <ctype.h>
using namespace std;
enum ACTION {TRADE, CHEAT, EMPTY};
enum RECORD {LAST1, LAST2};
class Memory {
public:
    map<RECORD, ACTION> R;
    Memory() {
        R[LAST1] = EMPTY;
        R[LAST2] = EMPTY;
    }
    static ACTION getAction(string s) {
        if(s == "TRADE")    return TRADE;
        if(s == "CHEAT")    return CHEAT;
        if(s == "EMPTY")    return EMPTY;
        assert(false);
    }
    ACTION getMemory(string addr) {
        if (addr == "LAST1")
            return R[LAST1];
        if (addr == "LAST2")
            return R[LAST2];
        assert(false);
    }
    void record(ACTION a) {
        ACTION last1 = R[LAST1], last2 = R[LAST2];
        R[LAST1] = a;
        R[LAST2] = last1;
    }
};
class Strategy {
public:
    char prog[1024];
    Strategy(string s) {
        for (int i = 0; i < s.length(); i++) {
            prog[i] = s[i];
        }
        prog[s.length()] = '\0';
    }
    char* match(char *str, const char *p) {
        if (str == NULL)
            return  NULL;
        if (memcmp(str, p, strlen(p)) == 0)
            return str + strlen(p);
        return NULL;
    }
/*
 <condition> ::= <cond> | <cond> <op> <condition>
 <op> ::= AND | OR
 <cond> ::= <memory> {= | #} {<command> | NULL}
 <memory> ::= {MY | YOUR} LAST {1 | 2}
 <command> ::= TRADE | CHEAT
 */
    bool cond(char* &p, Memory MY, Memory YOUR) {
        // printf("condition %s\n", p);
        char        *q;
        Memory      *addr = NULL;
        string      read, equal, kind;
        /* <memory> */
        q = match(p, "MY");
        if(q != NULL)   p = q, addr = &MY;
        q = match(p, "YOUR");
        if(q != NULL)   p = q, addr = &YOUR;
        q = match(p, "LAST1");
        if(q != NULL)   p = q, read = "LAST1";
        q = match(p, "LAST2");
        if(q != NULL)   p = q, read = "LAST2";
        /* {= | #} */
        q = match(p, "=");
        if(q != NULL)   p = q, equal = "=";
        q = match(p, "#");
        if(q != NULL)   p = q, equal = "#";
        /* {<command> | NULL} */
        q = match(p, "TRADE");
        if(q != NULL)  p = q, kind = "TRADE";
        q = match(p, "CHEAT");
        if(q != NULL)  p = q, kind = "CHEAT";
        q = match(p, "NULL");
        if(q != NULL)  p = q, kind = "EMPTY";
        bool ret = equal == "=" ? addr->getMemory(read) == Memory::getAction(kind) :
									addr->getMemory(read) != Memory::getAction(kind);
        // cout << "ADDR: " << addr->getMemory(read) << ", ACTION: " << Memory::getAction(kind) << endl;
        // cout << read << ", " << kind << endl; 
        /* <op> <condition> */
        q = match(p, "AND");
        if(q != NULL)  p = q, ret = ret&cond(p, MY, YOUR);
        q = match(p, "OR");
        if(q != NULL)  p = q, ret = ret|cond(p, MY, YOUR);
        // cout << "return " << ret << endl;
        return ret;
    }
    ACTION ifstat(char* &p, Memory a, Memory b) {
        char *q;
        q = match(p, "IF");
        if (q != NULL) {
            p = q;
            bool f = cond(p, a, b);
            ACTION a1, a2;
            q = match(p, "THEN");
            p = q;
            a1 = statement(p, a, b);
            q = match(p, "ELSE");
        	p = q;
        	a2 = statement(p, a, b);
        	return f ? a1 : a2;
        }
        assert(false);
    }
    ACTION statement(char* &p, Memory a, Memory b) {
        // printf("%s\n", p);
        char *q;
        q = match(p, "TRADE");
        if (q != NULL)  {
            p = q;
            return TRADE;
        }
        q = match(p, "CHEAT");
        if (q != NULL) {
            p = q;
            return CHEAT;
        }
        return ifstat(p, a, b);
    }
    ACTION eval(char* &p, Memory a, Memory b) { // read only
        // printf("eval %s\n", p);
        return statement(p, a, b);
    }
};
int main() {
    char c, s[1024];
    vector<Strategy> machine;
    while (true) {
        int n = 0;
        while ((c = getchar()) != EOF) {
            if(c == '.' || (c == '#' && n == 0) )
                break;
            if(isspace(c))
                continue;
            s[n++] = c;
        }
        if (n == 0)
            break;
        s[n++] = '\0';
        machine.push_back(Strategy(s));
    }
#define MAXN 20
    int SCORE[MAXN] = {};
    for (int i = 0; i < machine.size(); i++) {
        for (int j = i + 1; j < machine.size(); j++) {
            Memory      ma, mb;
            Strategy    &A = machine[i];
            Strategy    &B = machine[j];
            char        *p;
            
            for (int k = 0; k < 10; k++) {
                ACTION ia = A.eval(p = A.prog, ma, mb);
                ACTION ib = B.eval(p = B.prog, mb, ma);
                if(ia == TRADE && ib == TRADE)
                	SCORE[i]++, SCORE[j]++;
                else if(ia == TRADE && ib == CHEAT)
                	SCORE[i] -= 2, SCORE[j] += 2;
                else if(ia == CHEAT && ib == TRADE)
                	SCORE[i] += 2, SCORE[j] -= 2;
                else
                	SCORE[i]--, SCORE[j]--;
                ma.record(ia), mb.record(ib);
            }
        }
    }
    for(int i = 0; i < machine.size(); i++)
    	printf("%3d\n", SCORE[i]);
    return 0;
}
/*
 <program> ::= <statement>.
 <statement> ::= <command> | <ifstat>
 <ifstat> ::= IF <condition> THEN <statement> ELSE <statement>
 <condition> ::= <cond> | <cond> <op> <condition>
 <op> ::= AND | OR
 <cond> ::= <memory> {= | #} {<command> | NULL}
 <memory> ::= {MY | YOUR} LAST {1 | 2}
 <command> ::= TRADE | CHEAT 
 
 Sample input
 
CHEAT.
IF MY LAST1 = CHEAT THEN TRADE ELSE CHEAT.
IFYOURLAST2=NULLTHENTRADEELSEIFYOURLAST1=TRADETHENTRADE
ELSECHEAT.
#
 
CHEAT.
TRADE.
IF MY LAST1 = CHEAT OR MY LAST2 = CHEAT AND YOUR LAST2 = CHEAT THEN TRADE ELSE CHEAT.
IF MY LAST1 = CHEAT AND MY LAST2 = CHEAT THEN IF MY LAST1 = CHEAT AND MY LAST2 = CHEAT THEN TRADE ELSE CHEAT ELSE CHEAT.
IFYOURLAST2=NULLTHENTRADEELSEIFYOURLAST1=TRADETHENTRADEELSECHEAT.
IF YOUR LAST2=CHEATORYOURLAST1=CHEATTHENCHEATELSETRADE.
IF YOUR LAST1#NULLTHENIF YOUR LAST1#NULLANDMYLAST1=TRADETHENTRADEELSETRADEELSEIF YOUR LAST1#NULLTHENTRADEELSETRADE.
IF MY LAST1 = CHEAT OR MY LAST2 = CHEAT AND YOUR LAST2 = CHEAT THEN TRADE ELSE CHEAT.
IF MY LAST1 = CHEAT AND MY LAST2 = CHEAT THEN IF MY LAST1 = CHEAT AND MY LAST2 = CHEAT THEN TRADE ELSE CHEAT ELSE CHEAT.
IFYOURLAST2=NULLTHENTRADEELSEIFYOURLAST1=TRADETHENTRADEELSECHEAT.
# 

 Sample output
 
 1
 -12
 -13
 */
