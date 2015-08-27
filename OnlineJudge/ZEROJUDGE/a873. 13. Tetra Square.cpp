#include <bits/stdc++.h>
using namespace std;

template<typename ELE, int COL, int MAXV> class DLX {
public:
    struct Node {
        int left, right, up, down, ch;
        ELE data;
    } DL[MAXV + COL];
    int s[COL], o[COL], head, size;
    int found;
    vector<ELE> fstep;
    void remove(int c) {
        DL[DL[c].right].left = DL[c].left;
        DL[DL[c].left].right = DL[c].right;
        for (int i = DL[c].down; i != c; i = DL[i].down) {
            for (int j = DL[i].right; j != i; j = DL[j].right) {
                DL[DL[j].down].up = DL[j].up;
                DL[DL[j].up].down = DL[j].down;
                s[DL[j].ch]--;
            }
        }
    }
    void resume(int c) {
        for (int i = DL[c].down; i != c; i = DL[i].down) {
            for (int j = DL[i].left; j != i; j = DL[j].left) {
                DL[DL[j].down].up = j;
                DL[DL[j].up].down = j;
                s[DL[j].ch]++;
            }
        }
        DL[DL[c].right].left = c;
        DL[DL[c].left].right = c;
    }
    void dfs(int dep) {
        if (found) return ;
        if (DL[head].right == head) {
        	for (int i = 0; i < dep; i++)
        		fstep.push_back(DL[o[i]].data);
            found++;
            return ;
        }
        int tmp = 0x3f3f3f3f, c;
        for (int i = DL[head].right; i != head; i = DL[i].right) {
            if(s[i] < tmp)
                tmp = s[i], c = i;
        }
        remove(c);
        for (int i = DL[c].down; i != c; i = DL[i].down) {
            o[dep] = i;
            for (int j = DL[i].right; j != i; j = DL[j].right)
                remove(DL[j].ch);
            dfs(dep+1);
            for (int j = DL[i].left; j != i; j = DL[j].left)
                resume(DL[j].ch);
        }
        resume(c);
    }
    int newNode(int u, int d, int l, int r) {
        DL[size].up = u, DL[size].down = d;
        DL[size].left = l, DL[size].right = r;
        DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
        assert(size < MAXV + COL);
        return size++;
    }
    void addRow(int r[], int n, ELE data) {
    	sort(r, r+n);
        for (int i = 0, j, h; i < n; i++) {
            DL[size].ch = r[i], s[r[i]]++;
            DL[size].data = data;
            if (i)
                j = newNode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
            else
                h = newNode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
        }
    }
    void init(int c) { // total column
        size = 0, found = 0, fstep.clear();
        head = newNode(0, 0, 0, 0);
        for (int i = 1; i <= c; i++) {
            newNode(i, i, DL[head].left, head);
            DL[i].ch = i, s[i] = 0;
        }
    }
};

char tile_name[][10] = {"J1", "J2", "J3", "J4", "T1", "T2", "T3", "T4", 
					"L1", "L2", "L3", "L4", "Z1", "Z2", "S1", "S2", "I1", "I2"};
char tile[][4][4] = {{"01", "01", "11", ""}, 	// J1
					 {"100", "111", "", ""},			// J2
					 {"11", "10", "10", ""},		// J3
					 {"111", "001", "", ""},			// J4
					 {"111", "010", "", ""},			// T1
					 {"01", "11", "01", ""},		// T2
					 {"010", "111", "", ""},			// T3
					 {"10", "11", "10", ""},		// T4
					 {"10", "10", "11", ""},		// L1
					 {"111", "100", "", ""},			// L2
					 {"11", "01", "01", ""},		// L3
					 {"001", "111", "", ""},			// L4
					 {"110", "011", "", ""},			// Z1
					 {"01", "11", "10", ""},		// Z2
					 {"011", "110", "", ""},			// S1
					 {"10", "11", "01", ""},		// S2
					 {"1", "1", "", ""},				// I1
					 {"11", "", "", ""}};					// I2
struct ELE {
	int id, px, py, pp;
	ELE(int a = 0, int b = 0, int c = 0, int d = 0):
		id(a), px(b), py(c), pp(d) {}
};
DLX<ELE, 64, 32767> dlx;
int allin(int tid, int x, int y, int r[], int &rn) {
	rn = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; tile[tid][i][j]; j++) {
			if (tile[tid][i][j] == '1') {
				int tx, ty;
				tx = x + i, ty = y + j;
				if (tx < 0 || ty < 0 || tx >= 4 || ty >= 4)
					return 0;
				r[rn++] = tx*4+ty+1;
			}
		}
	}
	return 1;
}
int main() {
	int n;
	char s[1024];
    while (scanf("%d", &n) == 1 && n) {
        dlx.init(4*4 + n);
        for (int i = 0; i < n; i++) {
        	scanf("%s", s);
        	int tid = -1; 
        	for (int j = 0; j < 18; j++)
        		if (!strcmp(tile_name[j], s))
        			tid = j;
        	for (int x = 0; x < 4; x++) {
        		for (int y = 0; y < 4; y++) {
        			int r[64], rn = 0;
        			if (allin(tid, x, y, r, rn)) {
        				r[rn++] = 16 + (i+1);
        				ELE e(tid, x, y, i);
        				dlx.addRow(r, rn, e);
					}
				}
			}
		}
		dlx.dfs(0);
		assert(dlx.found != 0);
		char g[16][16] = {};
		
		for (int i = 0; i < dlx.fstep.size(); i++) {
			int tid = dlx.fstep[i].id;
			int x = dlx.fstep[i].px;
			int y = dlx.fstep[i].py;
			int c = dlx.fstep[i].pp + 'A';
			for (int j = 0; j < 4; j++) {
				for (int k = 0; tile[tid][j][k]; k++)
					if (tile[tid][j][k] == '1')
						g[x+j][y+k] = c;
			}
		}
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				putchar(g[i][j]);
			}
			puts("");
		}
    }
    return 0;
}
