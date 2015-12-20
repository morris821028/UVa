#include <stdio.h>
#include <string.h>
#include "memory.h"

int main() {
	static Memory mem[2];
	char c; int i;
	memset(mem,0xB3,sizeof(mem));
	while (scanf(" %c%d", &c, &i) == 2) {
		if (c == 'I') {
			int n;
			scanf("%d",&n);
			initMemory(mem+i,n);
		} else if (c == 'P') {
			printMemory(mem+i);
		} else {
			int b, n;
			scanf("%d%d", &b, &n);
			if (c == 'A')
				allocateMemory(mem+i,b,n);
			else 
				freeMemory(mem+i,b,n);
		}
	}
	return 0;
}
