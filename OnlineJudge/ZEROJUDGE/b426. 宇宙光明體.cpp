#include <bits/stdc++.h> 
using namespace std;

const double eps = 0;
class IMAGE {
public:
	struct Pixel {
		long double r, g, b, a;
		Pixel(long double x = 0, long double y = 0, long double z = 0, long double w = 0):
			r(x), g(y), b(z), a(w) {}
		void read() {
			int p1, p2, p3;
			scanf("%d %d %d", &p1, &p2, &p3);
			r = p1, g = p2, b = p3;
		}
		Pixel operator-(const Pixel &x) const {
        	return Pixel(r-x.r, g-x.g, b-x.b, a-x.a);
    	}
    	Pixel operator+(const Pixel &x) const {
        	return Pixel(r+x.r, g+x.g, b+x.b, a+x.a);
    	}
    	Pixel operator*(const long double x) const {
        	return Pixel(r*x, g*x, b*x, a*x);
    	}
		Pixel operator/(const long double x) const {
        	return Pixel(r/x, g/x, b/x, a/x);
    	}
    	void print() {
    		double p1 = r, p2 = g, p3 = b, p4 = a;
    		printf("%.0lf %.0lf %.0lf", p1 + eps, p2 + eps, p3 + eps);
    	}
	};
	int W, H;
	static const int MAXN = 256;
	Pixel data[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}	
	void add(IMAGE &other, int X, int Y, double OPACITY) {
		for (int i = 0; i < other.H && i+X < H; i++) {
			for (int j = 0; j < other.W && j+Y < W; j++) {
				if (i+X >= 0 && j+Y >= 0)
					data[i+X][j+Y] = other.data[i][j] * OPACITY + data[i+X][j+Y] * (1 - OPACITY);
			}
		}
	}
	void print() {
		printf("%d %d\n", W, H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].print(), printf("%c", j == W-1 ? '\n' : ' ');
	}
} back, fore;
int main() {
	double OPACITY;
	int X, Y;
	scanf("%d %d %lf", &X, &Y, &OPACITY);
	fore.read();
	back.read();
	back.add(fore, Y, X, OPACITY);
	back.print();
	return 0;
}
/*
0 0 0.5
1 1
255 255 255
1 1
0 0 0
*/
