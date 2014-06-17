#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int t, n, X, Y;
    cin >> t;
    while(t--) {
        cin >> n;
        cin.ignore(100, '\n');
        string p[100][100], in;
        int pw[100] = {};
        for(int i = 0; i < n; i++) {
            getline(cin, in);
            stringstream sin;
            sin << in;
            while(sin >> p[i][pw[i]])
                pw[i]++;
        }
        cin >> Y >> X;
        int font, i, j;
        for(font = 28; font >= 8; font--) {
            if(font*n > X)  continue;
            int x = 0, y = 0;
            int first;
            for(i = 0; i < n; i++) {
                x += font, y = 0;
                first = 0;
                for(j = 0; j < pw[i]; j++) {
                    if(y+font*(p[i][j].length()+first) > Y) {
                        x += font, y = font*p[i][j].length();
                    } else {
                        y += font*(p[i][j].length()+first);
                    }
                    if(y > Y || x > X) {
                        x = X+1;
                        break;
                    }
                    first = 1; // space
                }
            }
            if(x <= X) {
                cout << font << endl;
                break;
            }
        }
        if(font == 7)
            cout << "No solution" << endl;
    }
    return 0;
}

