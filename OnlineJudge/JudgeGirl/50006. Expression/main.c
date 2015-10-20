#include <stdio.h>
#include <string.h>
#include "eval.h"

int main() {
	int exp[1024];
	memset(exp, -1, sizeof(exp));
	scanf("%d", &exp[0]);
	for (int i = 1; i <= exp[0]; i++)
		scanf("%d", &exp[i]);
	int ret = eval(exp);
	printf("%d\n", ret);
	return 0;
}
/* 
Sample Input 0: // 1 + 7 - 3 for 10pt in 0.in/0.out testdata.
5
1 1 7 2 3
Sample Output 0:
5

Sample Input 1: // 1 + 2 * -3 + 4 / 5 * 6
11
1 1 2 3 -3 1 4 4 5 3 6
Sample Output 2:
-5

Sample Input 2: // 1 + 4 * 3 / 2
7
1 1 4 3 3 4 2
Sample Output 2:
7

Sample Input 3: // 1 ? 3
3
1 0 3
Sample Output 3: 
-2147483646

Sample Input 4: // 1 / 0
3
1 4 0
Sample Output 4: 
-2147483647
*/
