#include <stdio.h> 
#include <string.h>
//#define DEBUG
int gray(int n, int k) { // find k-th gray code
    if(n == 0)  return 0;
    if(k >= (1<<(n-1)))
        return (1<<(n-1)) | gray(n-1, (1<<(n))-k-1);
    else
        return gray(n-1, k);
}
int path[128];
void grayNext(int idx, int n, char w[], int& k, int &f) {
	if(f == 2)	return;
	if(idx == n) {
		if(f == 0) {
			f = 1;
		} else {
			k--;
			if(k == 0) {
				for(int i = 0; i < n; i++)
					printf("%d", path[i]);
				puts("");
				f = 2;
			}
		}
#ifdef DEBUG
		for(int i = 0; i < n; i++)
			printf("%d", path[i]);
		puts("");
#endif
		return ;
	}
	if(f == 0) {
		if(w[idx] == path[idx] + '0') {
			grayNext(idx+1, n, w, k, f);
			path[idx] = !path[idx];
			grayNext(idx+1, n, w, k, f);
		} else {
			for(int i = idx; i < n; i++)
				path[i] = 0;
			path[idx] = w[idx] - '0';path[idx+1] = 1;
			grayNext(idx+1, n, w, k, f);
		}
	} else {
		grayNext(idx+1, n, w, k, f);
		path[idx] = !path[idx];
		grayNext(idx+1, n, w, k, f);
	}
	
}
int main() {
	int n, m, f;
	char w[1024];
	while(scanf("%d %s", &n, w) == 2 && n) {
		f = 0;
		memset(path, 0, sizeof(path));
		m = strlen(w);
//		printf("find next %d\n", n);
		grayNext(0, m, w, n, f);
		while(n) {
			memset(path, 0, sizeof(path));
			grayNext(0, m, w, n, f);
		}
	}
	return 0;
}
