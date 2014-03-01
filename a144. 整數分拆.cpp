#include<stdio.h>
#define Max 101
int ans[100] = {Max}, n;
void div(int n, int index) {
	int a, next = index+1;
	if(n == 0) {
		for(a = 1; a < index; a++) printf("%d ", ans[a]);
		puts("");
		return ;
	}
	for(a = (n > ans[index-1]) ? ans[index-1] : n; a >= 1; a--)
		ans[index] = a, div(n-a, next);
}
main() {
	while(scanf("%d", &n) == 1)
		div(n, 1);
	return 0;
}
