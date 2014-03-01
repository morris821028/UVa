#include <iostream>
using namespace std;

int main() {
    string s;
    int cases = 0;
    while(cin >> s) {
        if(s == "*")    break;
        cout << "Case " << ++cases << ": ";
        if(s == "Hajj")
            cout << "Hajj-e-Akbar" << endl;
        else
            cout << "Hajj-e-Asghar" << endl;
    }
    return 0;
}
