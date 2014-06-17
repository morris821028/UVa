#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
using namespace std;
struct Info {
    string d[8];
};
int main() {
    int t;
    string depart, info;
    map<string, Info> r;
    cin >> t;
    getchar();
    while(t--) {
        getline(cin, depart);
        while(getline(cin, info)) {
            if(info.length() == 0)
                break;
            int pos_1 = 0, pos_2 = info.find(",");
            int idx = 0;
            Info p;
            while(1) {
                string sub = info.substr(pos_1, pos_2-pos_1);
                p.d[idx++] = sub;
                pos_1 = pos_2 + 1;
                pos_2 = info.find(",", pos_2 + 1);
                if(pos_2 == string::npos) {
                    sub = info.substr(pos_1, pos_2-pos_1);
                    p.d[idx++] = sub;
                    break;
                }
            }
            p.d[7] = depart;
            r[p.d[2]] = p;
        }
    }
    for(map<string, Info>::iterator i = r.begin(); i != r.end(); i++) {
        cout << "----------------------------------------" << endl;
        Info p = i->second;
        cout << p.d[0] << " " << p.d[1] << " " << p.d[2] << endl;
        cout << p.d[3] << endl;
        cout << "Department: " << p.d[7] << endl;
        cout << "Home Phone: " << p.d[4] << endl;
        cout << "Work Phone: " << p.d[5] << endl;
        cout << "Campus Box: " << p.d[6] << endl;
    }
    return 0;
}
