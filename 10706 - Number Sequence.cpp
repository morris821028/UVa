#include <stdio.h>
#include <math.h>

long long NLoc[33001];
char Sequ[1000000];
void Build() {
	int i, length, totlen = 0;
	char *s = Sequ;
	NLoc[0] = 0;
	for(i = 1; i <= 33000; i++) {
		sprintf(s, "%d", i);
		length = (int)log10(i)+1;
		s += length;
		totlen += length;
		NLoc[i] = totlen + NLoc[i-1];
	}
}
void FindNSeq(int v) {
	int l = 0, r = 33000, m;
	do {
		m = (l+r)>>1;
		if(NLoc[m] < v) {
			if(NLoc[m+1] >= v)
				break;
			else
				l = m+1;
		} else 
			r = m-1;
	} while(l <= r);
	printf("%c\n", Sequ[v-NLoc[m]-1]);
}
int main() {
	Build();
	int T, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &i);
		FindNSeq(i);
	}
    return 0;
}
