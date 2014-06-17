#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>
using namespace std;

typedef struct {
	char s[100], ch[100];
}Word;
Word Data[1005];
int cmp(const void *i, const void *j) {
	Word *a, *b;
	a = (Word *)i, b = (Word *)j;
	return strcmp(a->s, b->s);
}
int main() {
	int i, n = 0;
	map<string, int> record;
	while(scanf("%s", &Data[n].s) == 1) {
		if(!strcmp(Data[n].s, "#"))
			break;
		for(i = 0; Data[n].s[i]; i++) {
			Data[n].ch[i] = Data[n].s[i];
			if(Data[n].ch[i] >= 'A' && Data[n].ch[i] <= 'Z')
				Data[n].ch[i] = Data[n].ch[i]-'A'+'a';
		}
		Data[n].ch[i] = '\0';
		sort(Data[n].ch, Data[n].ch+i);
		record[Data[n].ch]++;
		n++;
	}
	qsort(Data, n, sizeof(Word), cmp);
	for(i = 0; i < n; i++) {
		if(record[Data[i].ch] == 1)
			printf("%s\n", Data[i].s);
	}
    return 0;
}
