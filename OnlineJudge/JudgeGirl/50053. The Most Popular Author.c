#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char buff[65536];
static char *dict[128];
static char *bptr = buff;
static int dcnt = 0, sell[128];
int name2int(char *s) {
	for (int i = 0; i < dcnt; i++) {
		if (!strcmp(dict[i], s))
			return i;
	}
	strcpy(bptr, s);
	sell[dcnt] = 0;
	dict[dcnt++] = bptr;
	while (*bptr != '\0')	
		bptr++;
	bptr++;
	return dcnt-1;
}
int main() {
	int n;
	scanf("%d", &n); 
	{
		bptr = buff, dcnt = 0;
		
		char book[128][64];
		int uid_book[128];
		for (int i = 0; i < n; i++) {
			char s[128];
			scanf("%s", s);
			uid_book[i] = name2int(s);
			scanf("%s", book[i]);
		}
		
		{
			char s[128];
			int cnt;
			while (scanf("%s", s) == 1) {
				scanf("%d", &cnt);
				for (int i = 0; i < n; i++) {
					if (!strcmp(s, book[i])) {
						sell[uid_book[i]] += cnt;
						break;
					}
				}
			}
		}
	}
	
	int mx = -1;
	char *ret = NULL;
	for (int i = 0; i < dcnt; i++) {
		if (sell[i] > mx)
			mx = sell[i], ret = dict[i];
		if (sell[i] == mx && (strcmp(dict[i], ret) < 0))
			ret = dict[i];
	}
	printf("%s %d\n", ret, mx);
	return 0;
}


