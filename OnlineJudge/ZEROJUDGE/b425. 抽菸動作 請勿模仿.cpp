#include <bits/stdc++.h> 
using namespace std;

class IMAGE {
public:
	struct Pixel {
		double r, g, b, a;
		Pixel(double x = 0, double y = 0, double z = 0, double w = 0):
			r(x), g(y), b(z), a(w) {}
		void read() {
			scanf("%lf %lf %lf", &r, &g, &b);
		}
		Pixel operator-(const Pixel &x) const {
        	return Pixel(r-x.r, g-x.g, b-x.b, a-x.a);
    	}
    	Pixel operator+(const Pixel &x) const {
        	return Pixel(r+x.r, g+x.g, b+x.b, a+x.a);
    	}
    	Pixel operator*(const double x) const {
        	return Pixel(r*x, g*x, b*x, a*x);
    	}
		Pixel operator/(const double x) const {
        	return Pixel(r/x, g/x, b/x, a/x);
    	}
    	void print() {
    		printf("%d %d %d", (int)round(r), (int)round(g), (int)round(b));
    	}
	};
	int W, H;
	static const int MAXN = 300;
	Pixel data[MAXN][MAXN], tmp[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}
	void blur(long long X, long long Y, long long R) {
		if (R < 0)	return ;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if ((i-X)*(i-X) + (j-Y)*(j-Y) <= R*R) {
					Pixel B(0, 0, 0);
					int cnt = 0;
					for (int a = -5; a <= 5; a++) {
						for (int b = -5; b <= 5; b++) {
							if (i+a < H && j+b < W && i+a >= 0 && j+b >= 0) {
								B = B + data[i+a][j+b];
								cnt++;
							}
						}
					}
					tmp[i][j] = B / cnt;
				} else {
					tmp[i][j] = data[i][j];
				}
			}
		}
		
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j] = tmp[i][j];
	}
	void print() {
		printf("%d %d\n", W, H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].print(), printf("%c", j == W-1 ? '\n' : ' ');
	}
} test;
int main() {
	long long X, Y, R;
	scanf("%lld %lld %lld", &X, &Y, &R);
	test.read();
	test.blur(Y, X, R);
	test.print();
	return 0;
}

