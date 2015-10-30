#include <stdio.h>
#include <limits.h>
#define min(x, y) (x) < (y) ? (x) : (y)
char buf[1<<20], *dic[1024];
int n;
void read() {
	char *p = buf;
	while (1) {
		dic[n] = p;
		if (scanf("%s", p) != 1)
			break;
		while (*p)	p++;
		p++, n++;
	}
}
int mn_edit(char *s1, char *s2, int limit, int edit) {
	if (edit > limit)	return INT_MAX;
	if (*s1 == '\0' && *s2 == '\0')
		return edit;
	int ret = INT_MAX, t;
	if (*s1 == *s2) {
		t = mn_edit(s1+1, s2+1, limit, edit);
		ret = min(ret, t);
	}
	if (*s1) {
		t = mn_edit(s1+1, s2, limit, edit+1);
		ret = min(ret, t);
	}
	if (*s2) {
		t = mn_edit(s1, s2+1, limit, edit+1);
		ret = min(ret, t);
	}
	return ret;
}
int main() {
	read();
	
	int id1 = -1, id2 = 0, ret = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int r = mn_edit(dic[i], dic[j], ret, 0);
			if (r < ret || (r == ret && i*1000+j < id1*1000+id2))
				id1 = i, id2 = j, ret = r;
		}
	}
	printf("%d %d %d\n", ret, id1+1, id2+1);
	return 0;
}

