#include <stdio.h>
#include <stdlib.h>
long long Ans[11] = {}; /*計算有 i 行有彈珠的可能總數*/ 
int tmp[11] = {}; /*計算第 i 行有幾顆彈珠*/ 
void DFS(int now) {
	if(now == 10)	{/*模擬完成進行計算*/ 
		int i, temp = 0;
		for(i = 0; i < 10; i++)
			if(tmp[i])
				temp++;
		Ans[temp] ++;
		return;
	}
	int i;
	for(i = 0; i < 10; i++) {
		tmp[i]++;
		DFS(now+1);
		tmp[i]--;
	}
}
int main() {
	DFS(0);
	int i;
	for(i = 1; i <= 10; i++) {
		printf("%2d line %11I64d / 1e+10\n", i, Ans[i]);
	}
	system("pause");
    return 0;
}
/*
模擬 10 顆彈珠分別選了第幾行,
例如第一顆彈珠選了第 i 行, 則換下一個選 
*/ 
