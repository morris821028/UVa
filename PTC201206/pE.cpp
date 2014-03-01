#include <stdio.h>
#include <stdlib.h>
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
int MaxExp(const char *s, const int slen) {
	int i = 0, j = 1, k = 0, x, y, tmp;
	while(i < slen && j < slen && k < slen) {
		x = i + k;
		y = j + k;
		if(x >= slen)	x -= slen;
		if(y >= slen)	y -= slen;
		if(s[x] == s[y]) {
			k++;
		} else if(s[x] < s[y]) {
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
char str[300005];
int main() {
    int t, n, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %s", &n, str);
        int a = MinExp(str, n);
        int b = MaxExp(str, n);
        for(i = 0; i < n; i++) {
            printf("%d", (str[a]-'0')^(str[b]-'0'));
            a++, b++;
            if(a >= n)  a-=n;
            if(b >= n)  b-=n;
        }
        puts("");
    }
    return 0;
}
