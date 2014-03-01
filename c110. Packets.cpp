#include<stdio.h>
#include<stdlib.h>
main() {
	int t1, t2, t3, t4, t5, t6;
	while(scanf("%d %d %d %d %d %d", &t1, &t2, &t3, &t4, &t5, &t6) == 6) {
		if(t1+t2+t3+t4+t5+t6 == 0) break;
		int Ans = t6, tmp, tmp2;
		Ans += t5;
		t1 -= t5*11;	if(t1 < 0) t1 = 0;
		Ans += t4;
		tmp = t4*20;
		if(t2 >= t4*5)	tmp = 0, t2 -= t4*5;
		else {
			tmp -= t2*4, t2 = 0;
			if(t1 >= tmp)	t1 -= tmp, tmp = 0;
			else	tmp -= t1, t1 = 0;
		}
		Ans += (t3/4), t3 %= 4;
		if(t3) {
			Ans++;
			tmp = 36-t3*9, tmp2 = (3-t3)*2+1;
			if(t2 >= tmp2)	t2 -= tmp2, tmp -= tmp2*4;
			else	tmp -= t2*4, t2 = 0;
			if(t1 >= tmp)	t1 -= tmp, tmp -= t1;
			else	tmp -= t1, t1 = 0;
		}
		Ans += (t2/9), t2 %= 9;
		if(t2) {
			Ans++;
			tmp = 36-t2*4;
			if(t1 >= tmp)	t1 -= tmp, tmp -= t1;
			else	tmp -= t1, t1 = 0;
		}
		Ans += t1/36 + (t1%36!=0);
		printf("%d\n", Ans);
	}
	return 0;
}
