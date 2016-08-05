#include <cstdio>
#include <cstring>
using namespace std;

int n,maxd;
int para[10];

int geth(int a[]){
	int num = 0;
	for (int i = 1; i < n;++i)
	if (a[i] + 1 != a[i + 1]) num++;
	return num;
}

void change_para(int i,int j,int k, int a[])
{
	int temp1[10], temp2[10];
	memcpy(temp1, a + i, sizeof(int)*j);
	memcpy(temp2, a + i + j, sizeof(int)*k);
	memcpy(a + i, temp2, sizeof(int)*k);
	memcpy(a + i + k, temp1, sizeof(int)*j);
}

bool isok(int a[]){
	for (int i = 1; i <= n;++i)
		if (i != a[i]) return false;
	return true;
}

bool dfs(int d,int paras[]){
	if (d == maxd )
		if (isok(paras)) return true;

	int h = geth(paras);
	if (3 * d + h <= 3 * maxd)
		for (int i = 1; i < n; ++i)
		for (int j = 1; j <= n - i; ++j)
		for (int k = 1; k <= n+1 - i - j; ++k){
			int new_para[10];
			memcpy(new_para, paras, sizeof(int)*10);
			change_para(i, j, k, new_para);
			if (dfs(d+1, new_para)) return true;
		}
	return false;
}

int main(){
	int cas = 0;
	while (scanf("%d", &n) == 1 && n){
		for (int i = 1; i <= n; ++i)
			scanf("%d", &para[i]);
		for (maxd = 0; maxd < n; ++maxd)
			if (dfs(0,para)) break;
		printf("Case %d: %d\n", ++cas,maxd);
	}
	return 0;
}
