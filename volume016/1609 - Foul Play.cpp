#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1025;
char team[maxn][maxn];
int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("input.txt" , "r", stdin );
    //freopen("output.txt", "w", stdout);
    while(cin >> n){
        for(int i = 1; i <= n; ++i) {
            cin >> team[i]+1;
        }
        vector<int> win, lose;
        for(int i = 2; i <= n; ++i) {
            if(team[1][i] == '1')
                win.push_back(i);
            else lose.push_back(i);
        }
        int leftTeam = n;
        while (leftTeam > 1) {
            vector<int> winSub, loseSub, round3;
            for(int i = 0; i < lose.size(); ++i) {
                bool matched = false;
                for(int j = 0; j < win.size(); ++j){
                    if(win[j] && team[win[j]][lose[i]] == '1'){
                        cout << win[j] << ' ' <<lose[i] << '\n';
                        matched = true;
                        winSub.push_back(win[j]);
                        win[j] = 0;
                        break;
                    }
                }
                if(!matched) round3.push_back(lose[i]);
            }

            bool isOK = false;
            for(int i = 0; i < win.size(); ++i) {
                if(win[i]) {
                    if(!isOK){
                        cout << "1 " << win[i] << '\n';
                        isOK = true;
                    } else {
                        round3.push_back(win[i]);
                    }
                }
            }

            for(int i = 0; i < round3.size(); i += 2) {
                cout << round3[i] << ' ' << round3[i+1] << '\n';
                int tmp = round3[i+1];
                if(team[round3[i]][tmp] == '1')
                    tmp = round3[i];
                if(team[1][tmp] == '1') winSub.push_back(tmp);
                else loseSub.push_back(tmp);
            }

            win = winSub;
            lose = loseSub;
            leftTeam >>= 1;
        }            
    }
    return 0;
}
        
