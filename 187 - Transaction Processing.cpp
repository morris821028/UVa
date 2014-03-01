#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
struct D {
        int cost;
        int it;
};
int main() {
    string line, name;
    string item[1000];
    int num;
    while(getline(cin, line)) {
        name = line.substr(3);
        num = (line[2]-'0')+(line[1]-'0')*10+(line[0]-'0')*100;
        if(!num)    break;
        item[num] = name;
    }

    vector<D> cust[1000];
    int cost, it;
    while(cin >> line >> cost) {
        num = (line[2]-'0')+(line[1]-'0')*10+(line[0]-'0')*100;
        it = (line[5]-'0')+(line[4]-'0')*10+(line[3]-'0')*100;
        if(num == 0)    break;
        D ele;
        ele.cost = cost;
        ele.it = it;
        cust[num].push_back(ele);
    }
    int i, j;
    for(i = 0; i < 1000; i++) {
        int r[1000] = {}, sum = 0;
        for(vector<D>::iterator it = cust[i].begin();
            it != cust[i].end(); it++) {
            r[it->it] += it->cost;
            sum += it->cost;
        }
        if(sum) {
            printf("*** Transaction %03d is out of balance ***\n",i);
            for(j = 0; j < 1000; j++) {
                if(r[j]) {
                    printf("%03d %-30s %10.2lf\n", j, item[j].c_str(), r[j]/100.0);
                }
            }
            printf("999 Out of Balance                 %10.2lf\n", -sum/100.0);
            puts("");
        }
    }
    return 0;
}
