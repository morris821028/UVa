#include <stdio.h>
#include <assert.h>
struct T0 {
	int i;
};
struct T1 {
	char c[4];
};
typedef struct Inst {
	int type;
	union {
		struct T0 t0;
		struct T1 t1;
	} para;
} Inst;
int main() {
	char s[16];
	assert(scanf("%s", s) == 1);
	FILE *fin = fopen(s, "rb");
	assert(fin != NULL);
	
	for (Inst cmd;;) {
		int stat = fread(&cmd, sizeof(Inst), 1, fin);
		if (stat != 1)
			break;
		switch (cmd.type) {
			case 0: 
				printf("%d", cmd.para.t0.i);
				break;
			case 1:
				putchar(cmd.para.t1.c[0]);
				putchar(cmd.para.t1.c[1]);
				putchar(cmd.para.t1.c[2]);
				putchar(cmd.para.t1.c[3]);
				break;
			case 2:
				{
					char c;
					while (fread(&c, sizeof(char), 1, fin) && c) {
						putchar(c);
					}
				}
				break;
			case 3:
				fseek(fin, cmd.para.t0.i-sizeof(Inst), SEEK_CUR);
				break;
			case 4:
				fseek(fin, cmd.para.t0.i, SEEK_SET);
				break;
			case 5:
				fseek(fin, cmd.para.t0.i, SEEK_END);
				break;
			default:
				printf("Seek end");
				return 0;
		}
	}
	printf("Seek end");
	return 0;
}


