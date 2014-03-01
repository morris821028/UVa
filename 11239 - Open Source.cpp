#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
struct D {
    string s;
    int n;
};
bool cmp(D i, D j) {
    if(i.n != j.n)
        return i.n > j.n;
    return i.s.compare(j.s) < 0;
}
int main() {
    while(1) {
        string proj, name;
        map<string, string> stu;
        map<string, set<string> > pro;
        getline(cin, proj);
        stu[""] = "-1";
        while(1) {
            if(proj[0] == '0')
                return 0;
            if(proj[0] == '1')
                break;
            pro[proj].insert("");
            while(getline(cin, name)) {
                if(name[0] >= 'A' && name[0] <= 'Z' || name[0] == '1') {
                    proj = name;
                    break;
                }
                if(stu[name] == "" || stu[name] == proj) {
                    stu[name] = proj;
                    pro[proj].insert(name);
                } else {
                    stu[name] = "-1";
                }
            }
        }
        int idx = 0;
        D ans[100];
        for(map<string, set<string> >::iterator i = pro.begin(); i != pro.end(); i++) {
            //cout << i->first << endl;
            int cnt = 0;
            for(set<string>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                //cout << *j << endl;
                if(stu[*j] != "-1")
                    cnt++;
            }
            ans[idx].s = i->first;
            ans[idx].n = cnt;
            idx++;
        }
        sort(ans, ans+idx, cmp);
        for(int i = 0; i < idx; i++)
            cout << ans[i].s << " " << ans[i].n << endl;
    }
    return 0;
}
