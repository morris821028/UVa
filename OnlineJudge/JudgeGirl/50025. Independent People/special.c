#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void cformat(const char const *buf, int n, int A[]) {
	// n variable separate by spaces
    int c = 0, toks = 0;
    char *ptr = strtok(buf, " \t\n\r");;
    while (ptr) {
        assert(sscanf(ptr, "%d", &A[toks]) == 1);
		toks++, ptr = strtok(NULL, " \t\n\r");
        assert(toks <= n);
    }
    assert(toks == n);
}
int main(int argc, char *argv[]) {
    assert(argc >= 4);
    FILE *fin0 = fopen(argv[1], "r"),  // testdata in
        *fin1 = fopen(argv[2], "r"),   // testdata out
        *fin2 = fopen(argv[3], "r");   // 
        
    int n, m, g[128][128];
    char buf[1024];
    while (fscanf(fin0, "%d %d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
        		fscanf(fin0, "%d", &g[i][j]);
			}	
		}
        	
        int solvable;
    	fscanf(fin1, "%d", &solvable);
    	if (solvable == 1) {
	    	int used[1024] = {}, A[1024];
    		fgets(buf, 1024, fin2);
    		cformat(buf, m, A);
	    	for (int i = 0; i < m; i++) {
	    		assert(A[i] >= 0 && A[i] < n);
	    		assert(used[A[i]] == 0);
	    		used[A[i]] = 1;
	    		for (int j = 0; j < i; j++)
	    			assert(g[A[i]][A[j]] == 0);
			}
		} else {
			fgets(buf, 1024, fin2);
			char s1[1024], s2[1024];
			assert(sscanf(buf, "%s %s", s1, s2) == 2);
			assert(strcmp(s1, "no") == 0);
			assert(strcmp(s2, "solution") == 0);
		}
	}
    return 0;
}
