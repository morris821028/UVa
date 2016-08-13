#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

class hashTab{
public:
	int v, next = 0, num = 0;
} hashNode[16000001];

int menu[33554433], d;

void creatHash(int x){
	int idx = (int)(abs(x)) % 33554432;
	int cur, pre = 0;
	cur = menu[idx];
	while (cur != 0){
		if (hashNode[cur].v == x){
			hashNode[cur].num++;
			return;
		}
		else {
			pre = cur;
			cur = hashNode[cur].next;
		}
	}
	++d;
	if (!pre)
		menu[idx] = d;
	else
		hashNode[pre].next = d;

	hashNode[d].v = x;
	hashNode[d].num = 1;
	hashNode[d].next = 0;
}

int getCnt(int x){
	int idx = (int)(abs(x)) % 33554432;
	int cur, pre = 0;
	cur = menu[idx];
	while (cur != 0){
		if (hashNode[cur].v == x)
			return hashNode[cur].num;
		else{
			pre = cur;
			cur = hashNode[cur].next;
		}
	}
	return 0;
}

int main(){
	int cas,n,ans;
	int A[4000], B[4000], C[4000], D[4000];
	scanf("%d", &cas);
	while (cas--){
		ans = d = 0;
		memset(menu, 0, sizeof(menu));
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			creatHash(A[i] + B[j]);
		
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			ans += getCnt(- C[i] - D[j]);
		printf("%d\n", ans);

		if (cas) putchar('\n');
	}
	return 0;
}
