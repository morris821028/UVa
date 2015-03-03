#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> getArgs(char line[]) {
    stringstream sin(line);
    vector<string> ret;
    string token;
    while (sin >> token)
        ret.push_back(token);
    return ret;
}
map<string, int> name2id;
map<int, string> id2name;
map<int, vector<int> > dependInstall, invDependInstall;
map<int, int> installStatus;
vector<int> installList;
int getId(string s) {
    int &ret = name2id[s];
    if (ret == 0) {
        ret = (int) name2id.size();
        id2name[ret] = s;
    }
    return ret;
}
string getName(int id) {
    return id2name[id];
}
int isDepended(int id) {
    vector<int> &v = invDependInstall[id];
    for (int i = 0; i < v.size(); i++) {
        if (installStatus[v[i]])    return 1;
    }
    return 0;
}
void installSoft(int id, int top) {
    if (installStatus[id] == 0) {
        vector<int> &v = dependInstall[id];
        for (int i = 0; i < v.size(); i++)
            installSoft(v[i], 0);
        printf("   Installing %s\n", getName(id).c_str());
        installStatus[id] = top ? 1 : 2;
        installList.push_back(id);
    }
}
void removeSoft(int id, int top) {
    if ((top == 1 || installStatus[id] == 2) && !isDepended(id)) {
        installStatus[id] = 0;
        printf("   Removing %s\n", getName(id).c_str());
        vector<int> &v = dependInstall[id];
        for (int i = 0; i < v.size(); i++)
            removeSoft(v[i], 0);
        installList.erase(find(installList.begin(), installList.end(), id));
    }
}
int main() {
    char line[2048];
    while (gets(line)) {
        vector<string> args = getArgs(line);
        puts(line);
        if (args[0] == "DEPEND") {
            vector<int> softId;
            for (int i = 1; i < args.size(); i++) {
                softId.push_back(getId(args[i]));
            }
            vector<int> &v = dependInstall[softId[0]];
            for (int i = 1; i < softId.size(); i++) {
                v.push_back(softId[i]);
                invDependInstall[softId[i]].push_back(softId[0]);
            }
        } else if (args[0] == "INSTALL") {
            if (installStatus[getId(args[1])]) {
                printf("   %s is already installed.\n", args[1].c_str());
            } else {
                installSoft(getId(args[1]), 1);
            }
        } else if (args[0] == "REMOVE") {
            if (installStatus[getId(args[1])] == 0) {
                printf("   %s is not installed.\n", args[1].c_str());
            } else if (isDepended(getId(args[1]))) {
                printf("   %s is still needed.\n", args[1].c_str());
            } else {
                removeSoft(getId(args[1]), 1);
            }
        } else if (args[0] == "LIST") {
            for (int i = 0; i < installList.size(); i++) {
                printf("   %s\n", getName(installList[i]).c_str());
            }
        } else if (args[0] == "END") {
            break;
        }
    }
    return 0;
}
/*
 DEPEND   TELNET TCPIP NETCARD
 DEPEND TCPIP NETCARD
 DEPEND DNS TCPIP NETCARD
 DEPEND  BROWSER   TCPIP  HTML
 INSTALL NETCARD
 INSTALL TELNET
 INSTALL foo
 REMOVE NETCARD
 INSTALL BROWSER
 INSTALL DNS
 LIST
 REMOVE TELNET
 REMOVE NETCARD
 REMOVE DNS
 REMOVE NETCARD
 INSTALL NETCARD
 REMOVE TCPIP
 REMOVE BROWSER
 REMOVE TCPIP
 END
 */