#include <iostream>
#include <map>
using namespace std;

int main() {
    string str, substr;
    int n;
    while(cin >> n >> str) {
        map<string, int> record;
        int len = str.length();
        for(int i = 0; i < len-n+1; i++) {
            substr.assign(str, i, n);
            record[substr]++;
        }
        int max = 0;
        for(map<string, int>::iterator i = record.begin(); i != record.end(); i++) {
            if(i->second > max) {
                max = i->second;
                str = i->first;
            }
        }
        cout << str << endl;
    }
    return 0;
}
