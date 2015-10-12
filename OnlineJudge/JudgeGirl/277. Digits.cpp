#include <stdio.h>
char seg7[10][5][5] = {
	{" - ", "| |", "   ", "| |", " - "},
	{"   ", "  |", "   ", "  |", "   "},
	{" - ", "  |", " - ", "|  ", " - "},
	{" - ", "  |", " - ", "  |", " - "},
	{"   ", "| |", " - ", "  |", "   "},
	{" - ", "|  ", " - ", "  |", " - "},
	{" - ", "|  ", " - ", "| |", " - "},
	{" - ", "| |", "   ", "  |", "   "},
	{" - ", "| |", " - ", "| |", " - "},
	{" - ", "| |", " - ", "  |", "   "},
};
void print_h(int lv, int hsz, char str[]) {
	int pos = 0, has = 0;
	for (int i = 0; str[i]; i++) {
		int d = str[i] - '0';
		if (seg7[d][lv][1] == '-') {
			while (has < i)
				putchar(' '), has++;
			for (; pos < i * (hsz+2); pos++)
				putchar(' ');
			putchar(' '), pos++;
			for (int j = 0; j < hsz; j++, pos++)
				putchar(d + '0');
		}
	}
	puts("");
}
void print_v(int lv, int vsz, int hsz, char str[]) {
	for (int i = 0; i < vsz; i++) {
		int pos = 0, has = 0;
		for (int j = 0; str[j]; j++) {
			int d = str[j] - '0';
			if (seg7[d][lv][0] == '|' || seg7[d][lv][2] == '|')
				while (has < j)
					putchar(' '), has++;
			if (seg7[d][lv][0] == '|') {
				for (; pos < j * (hsz+2); pos++)
					putchar(' ');
				putchar(d+'0'), pos++;
			}
			if (seg7[d][lv][2] == '|') {
				for (; pos < (j+1) * (hsz+2)-1; pos++)
					putchar(' ');
				putchar(d+'0'), pos++;
			}
		}
		puts("");
	}
}
void print(int vsz, int hsz, char str[]) {
	print_h(0, hsz, str);
	print_v(1, vsz, hsz, str);
	print_h(2, hsz, str);
	print_v(3, vsz, hsz, str);
	print_h(4, hsz, str);
}
int main() {
	char str[128];
	int wsz, hsz;
	while (scanf("%s %d %d", str, &wsz, &hsz) == 3) {
		print((hsz-3)/2, wsz-3, str);
	}	 
	return 0;
}

