#include<stdio.h>
#include<stdlib.h>
main() {
	int i, j;
	for(i = 0; i < 5; i++) {
		for(j = 0; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}
	system("pause"); //stdib.h
}
