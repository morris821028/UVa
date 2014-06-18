#include <iostream>
#include <queue>
using namespace std;
queue <int> qu;
int main(){
    int ntc,n,hh,mm,ss;
    cin >> ntc;
    while(ntc--){
        cin >> n >> hh >> mm >> ss;
        for(int i=1;i<=n;i++)
           qu.push(i);
        int take = hh;
        mm = mm*mm*mm;
        ss = ss*ss*ss;
        while(qu.size()!=1){
            for(int i=1;i<take;i++){
               qu.push(qu.front());
               qu.pop();
            }
           // cout << qu.front() <<" ";
            take = qu.front();
            qu.pop();
            
            if(take%2) take = (mm)%qu.size()+1;
            else take = (ss)%qu.size()+1;
            
        }
        cout << qu.front() << endl;
        qu.pop();
    }
    
    
}
