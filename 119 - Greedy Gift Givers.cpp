#include <iostream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int t, first = 0;
    while(cin >> t) {
        cin.ignore(100, '\n');
        string in;
        stringstream sin;
        getline(cin, in);
        sin << in;
        map<string, int> r;
        vector<string> v;
        while(sin >> in) {
            r[in] = 0;
            v.push_back(in);
        }
        int m, n;
        string give;
        while(t--) {
            cin >> in >> m >> n;
            if(n == 0)  continue;
            r[in] += m%n - m;
            for(int i = 0; i < n; i++) {
                cin >> give;
                r[give] = r[give] + m/n;

            }
        }
        if(first)
            cout << endl;
        first = 1;
        for(vector<string>::iterator it = v.begin(); it != v.end(); it++) {
            cout << *it << " " << r[*it] << endl;
        }
    }
    return 0;
}
