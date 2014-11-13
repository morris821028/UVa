#include <stdio.h> 

int main() {
	while (true) {
		int a[10], b[10], y = 1;
		for (int i = 0; i < 5; i++)
			if (scanf("%d", &a[i]) != 1)
				return 0;
		for (int i = 0; i < 5; i++)
			if (scanf("%d", &b[i]) != 1)
				return 0;
		for (int i = 0; i < 5; i++)
			y &= a[i] != b[i];
		puts(y ? "Y" : "N");
	}
	return 0;
}
/*
1 1 0 1 0
0 0 1 0 1
1 0 0 1 0
1 0 1 1 0
*/
