#include<iostream>    
using namespace std;

#define LL gate[i].in1
#define RR gate[i].in2

class gateClass {
public:
    int in1, in2, out;
} gate[200005];
int n, m, all0, all1;

int getOutput(int pos) {
    for (int i = 1; i <= m; i++) {
        int x = LL>0 ? gate[LL].out:-LL<=pos;
        int y = RR>0 ? gate[RR].out:-RR<=pos;
        gate[i].out = !(x && y);
    }
    return gate[m].out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cas , mid;
    cin >> cas;
    while (cas--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
            cin >> gate[i].in1 >> gate[i].in2;
        int all0 = getOutput(0);
        int all1 = getOutput(n);
        if (all0 == all1) {
            for (int i = 1; i <= n; i++) cout << '0';
        } else {
            int lef = 1, rit = n;
            while (lef < rit) {
                mid = lef + rit >> 1;
                if (getOutput(mid) == all1) rit = mid;
                else lef = mid + 1;
            }
            for (int i = 1; i < rit; i++) cout << '1';
            cout << 'x';
            for (int i = rit + 1; i <= n; i++) cout << '0';
        }
        cout << '\n';
    }
    return 0;
}
