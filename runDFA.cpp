#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm> //std::find
using namespace std;

int main() {
    fstream fin("DFA1.txt");
    string buf;
    vector<char> sigma;
    map<string, int> str2num;
    //<sigma>
    getline(fin, buf);
    for(int i = 1; i < buf.length(); i += 2)
        sigma.push_back(buf[i]);
    //</sigma>
    //<read table>
    int table[1000][sigma.size()], tsize = 0;
    int acceptTable[1000] = {};
    memset(table, 0, sizeof(table));
    while(getline(fin, buf)) {
        string left, right;
        int pos = buf.find(")"), prev;
        left = buf.substr(0, pos+1);
        prev = pos;
        int &x = str2num[left];
        if(x == 0)  x = ++tsize;
        if(left[1] == '*')  acceptTable[x] = 1;
        for(int i = 0; i < sigma.size(); i++) {
            pos = buf.find(")", prev+1);
            right = buf.substr(prev+1, pos-prev);
            prev = pos;
            int &y = str2num[right];
            if(y == 0)  y = ++tsize;
            table[x][i] = y;
            if(right[1] == '*')  acceptTable[y] = 1;
        }
    }
    //</read table>
    fin.close();
    cout << "¿é¤J¤§token:";
    cin >> buf;
    int error = 0, nowState = 1, nextState;
    for(int i = 0; i < buf.length(); i++) {
        int sigmaIdx = find(sigma.begin(), sigma.end(), buf[i])-sigma.begin();
        if(sigmaIdx >= sigma.size()) {//not found char
            error = 1;
            break;
        }
        nextState = table[nowState][sigmaIdx];
        if(nextState == 0) {//no state translate
            error = 1;
            break;
        }
        nowState = nextState;
    }
    cout << "¿é¥X:";
    if(error) {
        puts("error");
    } else {
        error = !acceptTable[nowState];
        if(error)
            puts("error");
        else
            puts("vaild");
    }
    return 0;
}
