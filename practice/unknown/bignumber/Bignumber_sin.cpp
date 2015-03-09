/**********************************************************************************/
/*  Problem: a204 "Exact sinx" from                                               */
/*  Language: C                                                                   */
/*  Result: AC (956ms, 424KB) on ZeroJudge                                        */
/*  Author: morris1028 at 2011-08-03 23:04:45                                     */
/**********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define L 1000
typedef struct {
	char neg;
	int pv[L], pl;
	int hv[L], hl;
}BigNumber;
/*
123.456
pv[] = '321'
hv[] = '456'
*/
BigNumber minus(BigNumber , BigNumber );
int compare(BigNumber A, BigNumber B) {/*兩個都是正數*/
	int a, h;
	if(A.pl > B.pl) return 1;
	if(A.pl < B.pl) return 0;
	for(a = A.pl; a >=0; a--)
		if(A.pv[a] > B.pv[a])
			return 1;
		else if(A.pv[a] < B.pv[a])
			return 0;
	for(a = 0; a <= A.hl && a <= B.hl; a++)
		if(A.hv[a] > B.hv[a])
			return 1;
		else if(A.hv[a] < B.hv[a])
			return 0;
	if(A.hl > B.hl) return 1;
	else if(A.hl < B.hl) return 0;
	return 1;
}
BigNumber addit(BigNumber A, BigNumber B) {
	if(A.neg == 0 && B.neg == 1) {
		B.neg = 0;return minus(A, B);
	}
	else if(A.neg == 1 && B.neg == 0) {
		A.neg = 0;return minus(B, A);
	}
	int a, p, h;
	BigNumber C;
	C.neg = A.neg;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = 0; a <= A.pl; a++)	C.pv[a] += A.pv[a];
	for(a = 0; a <= B.pl; a++)	C.pv[a] += B.pv[a];
	for(a = 0; a <= A.hl; a++)	C.hv[a] += A.hv[a];
	for(a = 0; a <= B.hl; a++)  C.hv[a] += B.hv[a];
	h = (A.hl < B.hl) ? A.hl : B.hl;/*min*/
	for(a = h; a >= 1; a--)
		C.hv[a-1] += C.hv[a]/10, C.hv[a] %= 10;
	C.pv[0] += C.hv[0]/10, C.hv[0] %= 10;
	p = (A.hl > B.hl) ? A.hl : B.hl;/*max*/
	for(a = 0; a <= p; a++)
		C.pv[a+1] += C.pv[a]/10, C.pv[a] %= 10;
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	return C;
}
BigNumber minus(BigNumber A, BigNumber B) {
	if(A.neg == 1 && B.neg == 1) {
		B.neg = 0, A.neg = 0;return minus(B, A);
	}
	else if(A.neg == 1 && B.neg == 0) {
		A.neg = 0;
		BigNumber C = addit(A, B);
		C.neg = 1;
		return C;
	}
	else if(A.neg == 0 && B.neg == 1) {
		B.neg = 0;return addit(A, B);
	}
	if(compare(A, B) == 0) {
		A.neg = 0;
		BigNumber C = minus(B, A);
		C.neg = 1;
		return C;
	}
	int a, p, h;
	BigNumber C;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = 0; a <= A.pl; a++) C.pv[a] = A.pv[a];
	for(a = 0; a <= A.hl; a++) C.hv[a] = A.hv[a];
	for(a = 0; a <= B.pl; a++) C.pv[a] -= B.pv[a];
	for(a = 0; a <= B.hl; a++) C.hv[a] -= B.hv[a];
	for(a = L-1; a >= 1; a--)
		while(C.hv[a] < 0)
			C.hv[a-1]--, C.hv[a] += 10;
	while(C.hv[0] < 0)
		C.pv[0]--, C.hv[0] += 10;
	for(a = 0; a < L; a++)
		while(C.pv[a] < 0)
			C.pv[a+1]--, C.pv[a] += 10;
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.hl = (C.hl > 100) ? 100 : C.hl;
	return C;
}
BigNumber multi(BigNumber A, BigNumber B) {
	BigNumber C;
	int Aa[4*L], Bb[4*L], Cc[4*L+1] = {};
	int a, b, Al = 0, Bl = 0, p, h;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = A.hl; a >= 0; a--)	Aa[Al++] = A.hv[a];
	for(a = 0; a <= A.pl; a++)	Aa[Al++] = A.pv[a];
	for(a = B.hl; a >= 0; a--)	Bb[Bl++] = B.hv[a];
	for(a = 0; a <= B.pl; a++)	Bb[Bl++] = B.pv[a];
	for(a = 0; a < Al; a++) {
		for(b = 0; b < Bl; b++)
			Cc[a+b] += Aa[a]*Bb[b];
	}
	for(a = 0; a < 2*L; a++)
		Cc[a+1] += Cc[a]/10, Cc[a] %= 10;
	int cut = (A.hl+1)+(B.hl+1);
	for(a = cut, b = 0; a < 4*L && b < L; a++, b++)
		C.pv[b] = Cc[a];
	for(a = cut-1, b = 0; a >= 0 && b < 100; a--, b++)
		C.hv[b] = Cc[a];
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.hl = (C.hl > 80) ? 80 : C.hl;
	C.neg = A.neg^B.neg;
	return C;
}
int Check(int a[], int b[], int lb, int lc) {
    int i;
    for(i = lb-1; i >= 0; i--) {
    	if(a[i+lc] < b[i]) return 0;
    	if(a[i+lc] > b[i]) return 1;
	}
	return 1;
}
BigNumber divis(BigNumber A, BigNumber B) {
	BigNumber C;
	int Aa[4*L] = {}, Bb[4*L] = {}, Cc[4*L+1] = {};
	int a, b, Al = 300, Bl = 0, p, h, i, j;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = A.hl; a >= 0; a--)	Aa[Al++] = A.hv[a];
	for(a = 0; a <= A.pl; a++)	Aa[Al++] = A.pv[a];
	for(a = B.hl; a >= 0; a--)	Bb[Bl++] = B.hv[a];
	for(a = 0; a <= B.pl; a++)	Bb[Bl++] = B.pv[a];
	Al++, Bl++;
 	for(i = Al-Bl; i >= 0; i--) {
		while(Check(Aa, Bb, Bl, i)){
        	Cc[i]++;
            for(j = 0; j < Bl; j++) {
            	Aa[i+j] -= Bb[j];
				if(Aa[i+j] < 0) {
                	Aa[i+j] += 10;
                	Aa[i+j+1]--;
              	}
        	}
    	}
    }
    int cut = 300 - B.hl + A.hl;
	for(a = cut, b = 0; a < 4*L && b < L; a++, b++)
		C.pv[b] = Cc[a];
	for(a = cut-1, b = 0; a >= 0 && b < L; a--, b++)
		C.hv[b] = Cc[a];
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.hl = (C.hl > 80) ? 80 : C.hl;
	C.neg = A.neg^B.neg;
	return C;
}
void Print(BigNumber A) {
	int a;
	if(A.neg == 1)	printf("-");
	for(a = A.pl; a >= 0; a--)
		printf("%d", A.pv[a]);
	if(A.pl == -1) printf("0");
	/*if(A.hl != -1)*/ printf(".");
	for(a = 0; a <= A.hl && a < 50; a++)
		printf("%d", A.hv[a]);
	for(; a < 50; a++)	printf("0");
	
}
BigNumber Change(char s[]) {
	int a, l = strlen(s), cut = l, b, p, h, neg = 0;
	BigNumber C;
	if(s[0] == '-')	neg = 1;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = neg; a < l; a++)
		if(s[a] == '.') cut = a;
	for(a = cut-1, b = 0; a >= neg; a--, b++)
		C.pv[b] = s[a] - '0';
	for(a = cut+1, b = 0; a < l; a++, b++)
		C.hv[b] = s[a] - '0';
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.neg = neg;
	return C;
}
main() {
	char x[200], y[20];
	/*freopen("in1.txt", "rt", stdin);   
	freopen("out1.txt", "w+t", stdout);*/
	while(scanf("%s", x) == 1) {
		BigNumber s1, s2, Ans, A;
		sprintf(y, "%d", 1);
		s1 = Change(x), s2 = Change(y);
		A = s1;
		sprintf(y, "%d", 0);
		Ans = Change(y);
		int a, t = 0;
		for(a = 1; a < 300; a += 2, t = 1-t) {
			if(t == 0)
				Ans = addit(Ans, divis(s1, s2));
			else
				Ans = minus(Ans, divis(s1, s2));
			/*Print(s1);
			puts("");			
			Print(s2);
			puts("");*/
			s1 = multi(A, multi(s1, A));
			sprintf(y, "%d", (a+1)*(a+2));
			s2 = multi(s2, Change(y));

		}
		Print(Ans);
		puts("");
	}
	return 0;
}/*
-0.523593766666666666666666666666666666666666666666666666
*/
