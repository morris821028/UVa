#include <bits/stdc++.h> 
using namespace std;

struct Ticket {
	int price;
	int K0, K1, K2;
	void read() {
		scanf("%d %d %d", &K0, &K1, &K2);
	}
	double sale(int H) {
		if (H >= 21 || H < 6 || (H >= 14 && H < 16))
			return price * K0 / 100.0;
		if ((6 <= H && H < 9) || (17 <= H && H < 19)) 
			return price * K2 / 100.0;
		return price * K1 / 100;
	}
} T[3];

int main() {
	T[0].price = 400;
	T[1].price = 600;
	T[2].price = 1000;
	int testcase, M, H, cases ;
	scanf("%d", &testcase);
	while (testcase--) {
		int H;
		double M;
		scanf("%lf %d", &M, &H);
		T[0].read();
		T[1].read();
		T[2].read();
		
		int ch = -1;
		for (int i = 2, f = 0; i >= 0; i--) {
			if (T[i].sale(H) < M || (f == 0 && T[i].sale(H) <= M)) {
				ch = i;
				M = T[i].sale(H), f = 1;
			}
		}
		switch(ch) {
			case -1: puts("Walk home"); break;
			case 0: puts("Bus"); break;
			case 1: puts("Train"); break;
			case 2: puts("HSR"); break;
		}
	}
	return 0;
}
