// Gale-Shapley algorithm, stable marriage problem
#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 256;
class GaleShapley { // produce the best possible choice for the mans
public:
    int mOrder[MAXN][MAXN], fOrder[MAXN][MAXN];
    int fPref[MAXN][MAXN];
    int man[MAXN], woman[MAXN];
    int N;
    void init(int n) {
        N = n;
    }
    void stable() {
        int mIdx[MAXN];
        for (int i = 0; i < N; i++)
            man[i] = woman[i] = -1, mIdx[i] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                fPref[i][fOrder[i][j]] = j;
        }
        for (int i = 0; i < N; i++) {
            int m = i, w;
            while (m >= 0) {
                w = mOrder[m][mIdx[m]++];
                while (m >= 0 && (woman[w] == -1 || fPref[w][woman[w]] > fPref[w][m])) {
                    man[m] = w;
                    swap(m, woman[w]);
                }
            }
        }
    }
} g;

char s[MAXN];
int tA[MAXN][MAXN], tB[MAXN][MAXN], rtA[MAXN][MAXN], rtB[MAXN][MAXN];
int main() {
    int N, M, x, n;
    int cases = 0;
    while (scanf("%d", &N) == 1 && N) {
    	map<string, int> Rn, Rm;
        for (int i = 0; i < N; i++)
        	scanf("%s", s), Rn[s] = i;
        scanf("%d", &M);
        for (int i = 0; i < M; i++)
        	scanf("%s", s), Rm[s] = i;
    	
    	for (int i = 0; i < N; i++)
    		for (int j = 0; j < M; j++)
    			scanf("%d", &tA[i][j]), tA[i][j]--, rtA[i][tA[i][j]] = j;
    	for (int i = 0; i < M; i++)
    		for (int j = 0; j < N; j++)
    			scanf("%d", &tB[i][j]), tB[i][j]--, rtB[i][tB[i][j]] = j;
    	++cases;
    	int tcases = 0;
    	while (scanf("%d", &n) == 1 && n) {
    		vector<string> A, B;
    		for (int i = 0; i < n; i++) {
    			scanf("%s", s);
    			string a(2, 'a'), b(2, 'a');
    			a[0] = s[0], a[1] = s[1];
    			b[0] = s[2], b[1] = s[3];
    			A.push_back(a), B.push_back(b);
    		}
    		g.init(n);
    		
    		for (int i = 0; i < n; i++) {
    			vector< pair<int, int> > p;
    			int u = Rn[A[i]], v;
    			for (int j = 0; j < n; j++) {
    				v = Rm[B[j]];
    				p.push_back(pair<int, int>(tA[u][v], j));
    			}
    			sort(p.begin(), p.end(), greater< pair<int, int> >());
    			for (int j = 0; j < n; j++) {
    				g.mOrder[i][j] = p[j].second;
//    				printf("%d ", p[j].second);
    			}
//    			puts(" -m");
    		}
    		
    		for (int i = 0; i < n; i++) {
    			vector< pair<int, int> > p;
    			int u = Rm[B[i]], v;
    			for (int j = 0; j < n; j++) {
    				v = Rn[A[j]];
    				p.push_back(pair<int, int>(tB[u][v], j));
    			}
    			sort(p.begin(), p.end(), greater< pair<int, int> >());
    			for (int j = 0; j < n; j++) {
    				g.fOrder[i][j] = p[j].second;
//    				printf("%d ", p[j].second);
    			}
//    			puts(" -f");
    		}
    		
    		g.stable();
    		
    		printf("Scenario %d, Mixture %d:\n", cases, ++tcases);
    		for (int i = 0; i < n; i++) {
    			int m = g.man[i];
    			if (i)	printf(" ");
    			printf("%s%s", A[i].c_str(), B[m].c_str());
    		}
    		puts("\n");
    	}
    }
    return 0;
}
/*

 */
