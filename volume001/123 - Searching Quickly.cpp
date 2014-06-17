#include<iostream>
#include<string>
#include<map>
#include<set>
#include<cstdio>
#include<cctype>
using namespace std;
const int kMaxn(207);
const string kSign("::");

int main()
{
    /*
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    //*/

    set<string> ignore;
    string t;
    while(getline(cin,t) && t!=kSign)
        ignore.insert(t);
    multimap<string,string> r;
    while(getline(cin,t))
    {
        for(int i=0;i<t.size();i++)
            t[i]=tolower(t[i]);
        for(int i=0;i<t.size();i++)
        {
            if(!isalpha(t[i]))
                continue;
            int j(i);
            string t2;
            while(j<t.size() && isalpha(t[j]))
            {
                t2+=t[j];
                j++;
            }
            if(!ignore.count(t2))
            {
                for(int k=0;k<t2.size();k++)
                    t2[k]=toupper(t2[k]);
                string t3(t);
                t3.replace(i,t2.size(),t2);
                r.insert(make_pair(t2,t3));
            }
            i=j;
        }
    }

    for(map<string,string>::iterator i=r.begin();i!=r.end();i++)
        cout<<i->second<<endl;

    return 0;
}
