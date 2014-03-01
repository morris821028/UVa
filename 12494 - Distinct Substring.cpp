#include <stdio.h>
#include <string.h>
struct Node {
    Node *next[26];
    int end;
    void init() {
        memset(next, 0, sizeof(next));
        end = 0;
    }
};
Node buf[1000000];
int MinExp(const char *s, const int slen) {
	int i = 0, j = 1, k = 0, x, y, tmp;
	while(i < slen && j < slen && k < slen) {
		x = i + k;
		y = j + k;
		if(x >= slen)	x -= slen;
		if(y >= slen)	y -= slen;
		if(s[x] == s[y]) {
			k++;
		} else if(s[x] > s[y]) {
			i = j+1 > i+k+1 ? j+1 : i+k+1;
			k = 0;
			tmp = i, i = j, j = tmp;
		} else {
			j = i+1 > j+k+1 ? i+1 : j+k+1;
			k = 0;
		}
	}
	return i;
}
int main() {
    int t;
    char s[1005];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        int i, j, k;
        for(i = len, j = 0; j < len; i++, j++)
            s[i] = s[j];
        int bufsize = 0;
        buf[0].init();
        Node *root = &buf[0], *p;
        int idx;
        int ret = 0;
        for(i = 0; i < len; i++) {
            for(j = 0; i+j < len; j++) {
                //s[i...i+j]
                int pos = MinExp(s+i, j+1)+i;
                //puts("");
                p = root;
                for(k = 0; k <= j; k++) {
                    idx = s[pos] - 'a';
                    pos++;
                    if(pos == i+j+1)    pos = i;
                    if(p->next[idx] == NULL) {
                        bufsize++;
                        buf[bufsize].init();
                        p->next[idx] = &buf[bufsize];
                    }
                    p = p->next[idx];
                }
                if(p->end == 0)
                    ret++;
                p->end = 1;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
