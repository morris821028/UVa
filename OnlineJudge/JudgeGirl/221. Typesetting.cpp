#include <stdio.h>
#include <string.h>
char token[1024][512];
int tlen[1024];
int WIDTH, offset = 0, n = 0;
char buf[10<<20];
static int readtoken(char **ret) {
    static const int N = 10<<20;
    static char *end = buf, *token = NULL;
    if(token == NULL) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf)
            return EOF;
        token = strtok(buf, " \n");
    } else {
        token = strtok(NULL, " \n");
    }
    *ret = token;
    return 1;
}
void mflush() {
	if (n == 0)	return;
	if (n == 1) {
		printf("%s", token[0]);
		for (int i = offset; i < WIDTH; i++)
			putchar(' ');
	} else {
		int base = (WIDTH - offset) / (n-1), ss = (WIDTH - offset) % (n-1);
		for (int i = 0; i < n; i++) {
			printf("%s", token[i]);
			if (i != n-1)
			for (int j = 0; j < base; j++)
				putchar(' ');
			if (i < ss)	putchar(' ');
		}
	}
	puts("");
	n = 0, offset = 0;
}
int main() {
	char *s;
	readtoken(&s);
	sscanf(s, "%d", &WIDTH);
	while (readtoken(&s) != EOF && s) {
		int m = strlen(s);
		if (offset + n + m > WIDTH)
			mflush();
		strcpy(token[n], s);
		tlen[n] = m, offset += m;
		n++;
	}
	mflush();
	return 0;
}

