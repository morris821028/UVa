#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct CMD {
    string cmd;
    int size, price;
    CMD(string kind, int x = 0, int y = 0):
    cmd(kind), size(x), price(y) {}
};
map<int, set<int> > BUY, SELL;
map<int, int> BUY_VAL, SELL_VAL;
vector<CMD> D;
void trade(int kind) {
    while (!BUY.empty() && !SELL.empty()) {
        if (BUY.rbegin()->first >= SELL.begin()->first) {
            set<int> &v1 = BUY.rbegin()->second;
            set<int> &v2 = SELL.begin()->second;
            int aid = *v1.begin(), bid = *v2.begin();
            int z = min(D[aid].size, D[bid].size);
            printf("TRADE %d %d\n", z, kind ? D[aid].price : D[bid].price);
            D[aid].size -= z, D[bid].size -= z;
            BUY_VAL[D[aid].price] -= z, SELL_VAL[D[bid].price] -= z;
            if (D[aid].size == 0)
                v1.erase(aid);
            if (D[bid].size == 0)
                v2.erase(bid);
            if (v1.size() == 0)
                BUY.erase(D[aid].price);
            if (v2.size() == 0)
                SELL.erase(D[bid].price);
        } else {
            return;
        }
    }
}
void print() {
    while (BUY_VAL.size() && BUY_VAL.rbegin()->second == 0) {
        BUY_VAL.erase(BUY_VAL.rbegin()->first);
    }
    while (SELL_VAL.size() && SELL_VAL.begin()->second == 0) {
        SELL_VAL.erase(SELL_VAL.begin()->first);
    }
    printf("QUOTE ");
    if (BUY_VAL.size()) {
        printf("%d %d", BUY_VAL.rbegin()->second, BUY_VAL.rbegin()->first);
    } else {
        printf("0 0");
    }
    printf(" - ");
    if (SELL_VAL.size()) {
        printf("%d %d", SELL_VAL.begin()->second, SELL_VAL.begin()->first);
    } else {
        printf("0 99999");
    }
    puts("");
}
int main() {
    int Q, cases = 0;
    char cmd[16];
    while (scanf("%d", &Q) == 1) {
        if (cases++)    puts("");
        BUY.clear(), SELL.clear();
        BUY_VAL.clear(), SELL_VAL.clear();
        D.clear();
        int size, price, id;
        for (int i = 0; i < Q; i++) {
            scanf("%s", cmd);
            if (!strcmp(cmd, "BUY")) {
                scanf("%d %d", &size, &price);
                BUY[price].insert(i);
                BUY_VAL[price] += size;
                D.push_back(CMD("BUY", size, price));
                trade(0);
            } else if (!strcmp(cmd, "SELL")) {
                scanf("%d %d", &size, &price);
                SELL[price].insert(i);
                SELL_VAL[price] += size;
                D.push_back(CMD("SELL", size, price));
                trade(1);
            } else if (!strcmp(cmd, "CANCEL")) {
                scanf("%d", &id), id--;
                D.push_back(CMD("CANCEL", id));
                if (D[id].cmd == "BUY") {
                    BUY[D[id].price].erase(id);
                    if (BUY[D[id].price].size() == 0)
                        BUY.erase(D[id].price);
                    BUY_VAL[D[id].price] -= D[id].size;
                    D[id].size = 0;
                }
                if (D[id].cmd == "SELL") {
                    SELL[D[id].price].erase(id);
                    if (SELL[D[id].price].size() == 0)
                        SELL.erase(D[id].price);
                    SELL_VAL[D[id].price] -= D[id].size;
                    D[id].size = 0;
                }
            }
            print();
        }
    }
    return 0;
}
/*
 11
 BUY 100 35
 CANCEL 1
 BUY 100 34
 SELL 150 36
 SELL 300 37
 SELL 100 36
 BUY 100 38
 CANCEL 4
 CANCEL 7
 BUY 200 32
 SELL 500 30
 */