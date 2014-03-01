#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int main() {
    map<string, string> r;
    string line, a, b;
    while(getline(cin, line)) {
        if(line == "")
            break;
        istringstream sin(line);
        sin >> a >> b;
        r[b] = a;
    }
    while(cin >> a) {
        map<string, string>::iterator it;
        it = r.find(a);
        if(it != r.end())
            cout << it->second << endl;
        else
            cout << "eh" << endl;
    }
    return 0;
}
