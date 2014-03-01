#include<stdio.h>
#include<windows.h>
HANDLE hConsole;
main() {
	int k;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for(k = 1; k < 255; k++) {
		SetConsoleTextAttribute(hConsole, k);   //?¸m¤å¦r¤Î­I´º¦â
		printf("%d s ", k);
	}
	puts("");
	system("pause");
}
