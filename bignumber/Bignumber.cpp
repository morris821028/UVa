#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define L 100
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
	return C;
}
BigNumber multi(BigNumber A, BigNumber B) {
	BigNumber C;
	int Aa[2*L], Bb[2*L], Cc[4*L+1] = {};
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
	C.pl = p, C.hl = h;
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
	int Aa[3*L] = {}, Bb[3*L] = {}, Cc[4*L+1] = {};
	int a, b, Al = L, Bl = 0, p, h, i, j;
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
    int cut = L - B.hl + A.hl;
	for(a = cut, b = 0; a < 4*L && b < L; a++, b++)
		C.pv[b] = Cc[a];
	for(a = cut-1, b = 0; a >= 0 && b < L; a--, b++)
		C.hv[b] = Cc[a];
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.neg = A.neg^B.neg;
	return C;
}
BigNumber msqrt(BigNumber A) {
	BigNumber C;
	int Aa[5*L] = {}, Cc[5*L+1] = {};
	int a, b, c, d, Al = L - A.hl - 1, Cl = 0, p, h;
	int cut;
	for(a = 0; a < L; a++)	C.pv[a] = C.hv[a] = 0;
	for(a = A.hl; a >= 0; a--)	Aa[Al++] = A.hv[a];
	for(a = 0; a <= A.pl; a++)	Aa[Al++] = A.pv[a];
    int B[5*L] = {}, top = Al, Bl = 1;
	for(a=(Al-1)/2*2 ; a >= 0; a -= 2, Bl++) {
        if(top > a+Bl-2)
    		for(b = 9;b >= 0;b--) {
            	int T[5*L]={0};
                B[0]=b;
        		for(d=0;d <= Bl;d++) {
                    T[a+d] += (b*B[d]);
                    T[a+d+1] += (T[a+d]/10);
                    T[a+d] %= 10;
                }
            	int find = 0;
                for(c = Bl+a+1; c >= 0; c--)
                	if(Aa[c] > T[c]) {find = 1;break;}
                    else if(T[c] > Aa[c]) break;
                if(find == 1 || c == -1) {
                	for(c = 0; c <= top;c++) {
                    	Aa[c] -= T[c];
                    	if(Aa[c]<0) {
                        	int temp=((-Aa[c])/10+((-Aa[c])%10!=0));
                        	Aa[c] += 10*temp;
                        	Aa[c+1] -= temp;
                    	}
                	}
            		break;
        		}
            }
        else b = 0;
        Cc[Cl++] = b;
        if(a == 100)	cut = Cl;
        if(top != -1) {
        	B[0] += b;
            for(b = 0; b <= Bl+1; b++)
        		if(B[b] >= 10) {
            		B[b+1] += (B[b]/10);
                    B[b] %= 10;
                }
                else break;
        	for(b = Bl+1;b >= 0; b--)	B[b+1] = B[b];
            	B[0]=0;          
            for(b = top;b >= 0; b--)
                if(Aa[b] != 0) {top = b;break;}
            if(b == -1) top = -1;
        }
    } 
	for(a = cut-1, b = 0; a >= 0 && b < L; a--, b++)
		C.pv[b] = Cc[a];
	for(a = cut, b = 0; a < 3*L  && b < L; a++, b++)
		C.hv[b] = Cc[a];
	p = L-1, h = L-1;
	while(C.pv[p] == 0 && p >= 0) p--;
	while(C.hv[h] == 0 && h >= 0) h--;
	C.pl = p, C.hl = h;
	C.neg = A.neg;
	return C;
}
void Print(BigNumber A) {
	int a;
	if(A.neg == 1)	printf("-");
	for(a = A.pl; a >= 0; a--)
		printf("%d", A.pv[a]);
	if(A.pl == -1) printf("0");
	if(A.hl != -1) printf(".");
	for(a = 0; a <= A.hl; a++)
		printf("%d", A.hv[a]);
	
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
	char s1[200], s2[200], k[2];
	printf("(1)A+B (2)A-B (3)A*B (4)A/B (5)sqrt(A)\n");
	while(scanf("%s", k) == 1) {
		BigNumber A, B, C;
		switch(k[0]) {
			case '1'...'4': {
				scanf("%s %s", s1, s2);
				A = Change(s1), B = Change(s2);
				Print(A);
				switch(k[0]) {
					case '1':C = addit(A, B);printf(" + ");
						break;
					case '2':C = minus(A, B);printf(" - ");
						break;
					case '3':C = multi(A, B);printf(" * ");
						break;
					case '4':C = divis(A, B);printf(" / ");
						break;
				}
				Print(B);
				printf("\n = ");
				Print(C);
				break;
			}
			case '5':
				scanf("%s", s1);
				A = Change(s1);
				C = msqrt(A);
				printf("sqrt( "), Print(A);
				printf(" )\n= ");
				Print(C);
				break;
		}
		puts("");
		system("pause");
		system("cls");
		printf("(1)A+B (2)A-B (3)A*B (4)A/B (5)sqrt(A)\n");
	}
	system("pause");
	return 0;
}
/*
1 -951.123548987 213548.2158
2 654.555 3158
3 0 10.665214
4 3.6 7
5 16.32458
*/
