#include <iostream>
#include <map>
using namespace std;

int main() {
    int m, n;
    while(cin >> m >> n) {
        map<string, int> r;
        string s;
        int d;
        while(m--) {
            cin >> s >> d;
            r[s] = d;
        }
        while(n--) {
            int sum = 0;
            while(cin >> s) {
                if(s == ".")
                    break;
                map<string, int>::iterator it;
                it = r.find(s);
                if(it != r.end())
                    sum += it->second;
            }
            cout << sum << endl;
        }
    }
    return 0;
}
