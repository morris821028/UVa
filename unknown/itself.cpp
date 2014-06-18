#include<stdio.h>
#include<stdlib.h>
int main() {
	FILE *fptr;
	fptr = fopen("itself.cpp", "rb");
	char s[100];
	while(fgets(s, 100, fptr))
		printf("%s", s);
	getchar();
    return 0;
}
