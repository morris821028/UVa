#include <iostream>
#include <sstream> // stringstream
#include <fstream> // fstream
#include <vector>
#include <algorithm> // sort
using namespace std;
struct seg { // segment
    int l, r, v, used;
    bool operator<(const seg &A) const {
        if(l != A.l)
            return l < A.l;
        return r < A.r;
    }
    seg(int a, int b, int c): l(a), r(b), v(c), used(0) {}
};
int main() {
    // if using read file
    //ifstream fin("input.txt");
    //ofstream fout("output.txt");
    // else replace all fin/fout to cin/cout
    string line;//read line
    stringstream sin;//parse string
    vector<int> UP, DOWN;//array
    int number;

    //<read file end>
    getline(cin, line);
    sin << line;
    while(sin >> number)
        UP.push_back(number);
    sin.clear();
    getline(cin, line);
    sin << line;
    while(sin >> number)
        DOWN.push_back(number);
    //</read file end>
    /* //<debug>
    for(int i = 0; i < UP.size(); i++)
        cout << UP[i] << " " << DOWN[i] << endl;
    */
    vector<seg> SEG;
    for(int i = 0; i < UP.size(); i++) {
        if(UP[i] != 0) {
            for(int j = 0; j < DOWN.size(); j++) {
                if(DOWN[j] == UP[i]) {
                    if(i > j)
                        SEG.push_back(seg(j, i, UP[i]));
                    else
                        SEG.push_back(seg(i, j, UP[i]));
                    break;
                }
            }
            for(int j = i+1; j < UP.size(); j++) {
                if(UP[j] == UP[i]) {
                    SEG.push_back(seg(i, j, UP[i]));
                    break;
                }
            }
        }
    }
    for(int i = 0; i < DOWN.size(); i++) {
        if(DOWN[i] != 0) {
            for(int j = i+1; j < UP.size(); j++) {
                if(DOWN[j] == DOWN[i]) {
                    SEG.push_back(seg(i, j, DOWN[i]));
                    break;
                }
            }
        }
    }
    sort(SEG.begin(), SEG.end());
    /* //<debug>
    for(int i = 0; i < SEG.size(); i++)
        cout << SEG[i].l+1 << " " << SEG[i].r+1 << " " << SEG[i].v << endl;
    */
    int trackID = 0;
    do {
        int lmin = -0xfffffff;// -oo
        int start = -1;
        for(int i = 0; i < SEG.size(); i++) {
            if(SEG[i].used == 0) {
                start = i;
                break;
            }
        }
        if(start == -1)
            break;
        cout << "Track " << ++trackID << ": I" << SEG[start].v;
        SEG[start].used = 1;
        for(int i = start+1; i < SEG.size(); i++) {
            if(SEG[i].l > SEG[start].r && SEG[i].used == 0) {
                cout << ", I" << SEG[i].v;
                SEG[i].used = 1;
                start = i;
            }
        }
        cout << endl;
    } while(true);
    system("pause");
    return 0;
}
