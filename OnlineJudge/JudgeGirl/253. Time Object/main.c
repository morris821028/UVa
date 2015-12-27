#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main() {
	int ch;
	int n, i, h, m, s;
	scanf("%d", &n);
	Time *t = (Time*) malloc(sizeof(Time)*n);
	while ((ch = getchar()) != EOF) {
		switch(ch) {
			case 'i':
				scanf("%d", &i);
				initTime(&t[i]);
				break;
			case 's':
				scanf("%d%d%d%d", &i, &h, &m, &s);
				setTime(&t[i], h, m, s);
				break;
			case 'a':
				scanf("%d%d%d%d", &i, &h, &m, &s);
				addTime(&t[i], h, m, s);
				break;
			case 'p':
				scanf("%d", &i);
				printTime(&t[i]);
				printTime24(&t[i]);
				break;
			default:
				break;
		}
	}
	free(t);
	return 0;
}
