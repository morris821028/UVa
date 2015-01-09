#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
char pattern[32][4][32][32]; // [id][rotate][x][y]
char prob_out[4][32][32], out[32][32];
int n, m;
int mx[30];
void out_update() {
	int mxrt = -1;
	for (int rt = 1; rt < 4; rt++) {
		for (int p = 0; p < n; p++) {
			for (int q = 0; q < n; q++) {
				prob_out[rt][p][q] = prob_out[rt-1][q][n - 1 - p];
			}
		}
	}
	for (int rt = 0; rt < 4; rt++) {
		int sum[30] = {};
		for (int p = 0; p < n; p++) {
			for (int q = 0; q < n; q++)
				sum[q] += prob_out[rt][p][n - q - 1] - '0';
		}
		for (int p = 0; p < 29; p++)
			sum[p+1] += sum[p]/10, sum[p] %= 10;
		int flag = 0;
		for (int p = 29; p >= 0; p--) {
			if (sum[p] != mx[p]) {
				flag = sum[p] > mx[p] ? 1 : -1;
				break;
			}
		}
		if (flag == 1) {
			for (int p = 29; p >= 0; p--)
				mx[p] = sum[p];
			mxrt = rt;
		}
	}
	if (mxrt >= 0) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) 
				out[i][j] = prob_out[mxrt][i][j];
	}
}
class DLX {
	public:
	struct DancingLinks {
		int left, right, up, down, ch;
		int id, rotate, px, py; // extra data
	} DL[131072 + 256];
	int s[512], o[512], head, size;		
	void remove(int c) {
	    DL[DL[c].right].left = DL[c].left;
	    DL[DL[c].left].right = DL[c].right;
	    int i, j;
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        for(j = DL[i].right; j != i; j = DL[j].right) {
	            DL[DL[j].down].up = DL[j].up;
	            DL[DL[j].up].down = DL[j].down;
	            s[DL[j].ch]--;
	        }
	    }
	}
	void resume(int c) {
	    int i, j;
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        for(j = DL[i].left; j != i; j = DL[j].left) {
	            DL[DL[j].down].up = j;
	            DL[DL[j].up].down = j;
	            s[DL[j].ch]++;
	        }
	    }
	    DL[DL[c].right].left = c;
	    DL[DL[c].left].right = c;
	}
	int found;
	void print(int dep) {
		for (int i = 0; i < dep; i++) {
			int id = DL[o[i]].id, rt = DL[o[i]].rotate;
			int px = DL[o[i]].px, py = DL[o[i]].py;
			for (int p = 0; p < n; p++) {
				for (int q = 0; q < n; q++) {
					if (pattern[id][rt][p][q] != ' ')
						prob_out[0][px + p][py + q] = pattern[id][rt][p][q];
				}
			}
		}
		out_update();
	}
	void dfs(int dep) {
		if (found) return;
	    if (DL[head].right == head) {
	    	print(dep);
	        found++;
	        return;
	    }
	    int tmp = 0x3f3f3f3f, c, i, j;
	    for(i = DL[head].right; i != head; i = DL[i].right)
	        if(s[i] < tmp)
	            tmp = s[i], c = i;
	    remove(c);
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        o[dep] = i;
	        for(j = DL[i].right; j != i; j = DL[j].right)
	            remove(DL[j].ch);
	        dfs(dep+1);
	        for(j = DL[i].left; j != i; j = DL[j].left)
	            resume(DL[j].ch);
	    }
	    resume(c);
	}
	int getnode(int u, int d, int l, int r) {
	    DL[size].up = u, DL[size].down = d;
	    DL[size].left = l, DL[size].right = r;
	    DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
	    assert(size < 131072);
	    return size++;
	}
	void newrow(int r[], int rn, int id, int rotate, int px, int py) {
	    int i, j, h;
	    for(i = 0; i < rn; i++) {
	        DL[size].ch = r[i], s[r[i]]++;
	        DL[size].id = id; // extra data
	        DL[size].rotate = rotate; // extra data
	        DL[size].px = px; // extra data
	        DL[size].py = py; // extra data
	        if(i) {
	            j = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
	        } else {
	            h = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
	        }
	    }
	}
	void init(int c) {// total column
	    size = 0;
	    head = getnode(0,0,0,0);
	    int i;
	    for(i = 1; i <= c; i++) {
	        getnode(i, i, DL[head].left, head);
	        DL[i].ch = i, s[i] = 0;
	    }
	}
} DLX;
int validPos(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n; 
}
char in[32767][128];
int main() {
	while (scanf("%d %d", &n, &m) == 2 && n) {
		while (getchar() != '\n');
		DLX.init(n * n + m);
		
		int t = 0;
		while (gets(in[t]) && in[t][0] != '#') {
			t++;
		}
		memset(pattern, ' ', sizeof(pattern));
		
		int test = 0;
		for (int i = 0, idx = 0; i < m; i++) {
			int r = 0, c = 0;
			char label = -1;
			for (int j = 0; in[idx][j]; j++)
				if (in[idx][j] >= '0' && in[idx][j] <= '9')
					label = in[idx][j];
					
			for (r = 0; ; r++) {
				int ok = 0;
				for (int j = 0; in[idx][j]; j++)
					if (in[idx][j] == label)
						ok = 1;
				if (ok == 0)	break;
				for (int j = 0; in[idx][j]; j++) {
					if (in[idx][j] == label) {
						pattern[i][0][r][j] = in[idx][j];
						c = max(c, j + 1);
						test++;
					}
				}
				idx++;
			}
			r = c = max(r, c);
			assert(r <= n && c <= n && r > 0);
			for (int rt = 1; rt < 4; rt++) {
				for (int p = 0; p < r; p++) {
					for (int q = 0; q < c; q++) {
						pattern[i][rt][p][q] = pattern[i][rt-1][q][r - 1 - p];
					}
				}
			}
			for (int rt = 0; rt < 1; rt++) {
				for (int p = -20; p <= n; p++) { 
					for (int q = -20; q <= n; q++) { // top-left corner
						int ok = 1, row[512], rn = 0;
						for (int p1 = 0; p1 < r && ok; p1++) {
							for (int q1 = 0; q1 < c && ok; q1++) {
								if (pattern[i][rt][p1][q1] != ' ') {
									ok &= validPos(p1 + p, q1 + q);
									row[rn++] = (p1 + p) * n + (q1 + q) + 1;
								}
							}
						}
						if (ok) {
							row[rn++] = n * n + i + 1;
							DLX.newrow(row, rn, i, rt, p, q);
						}
					}
				}	
			}
//			for (int kind = 0; kind < 4; kind++) {
//				for (int p = 0; p < r; p++, puts("")) {
//					for (int q = 0; q < c; q++)
//						printf("%c", pattern[i][kind][p][q]);
//				}
//				puts("---");
//			}
		}
		memset(mx, 0, sizeof(mx));
		DLX.found = 0;
		DLX.dfs(0);
		assert(DLX.found && test == n*n);
		if (DLX.found) {
			for (int i = 0; i < n; i++, puts("")) {
				for (int j = 0; j < n; j++) {
					putchar(out[i][j]);
					assert(out[i][j] != ' ');
				}
			}
		}
		puts("");
	}
	return 0;
}
