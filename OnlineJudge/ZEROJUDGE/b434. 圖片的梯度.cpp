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
	static const int MAXN = 256;
	Pixel data[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}
	Pixel pabs(Pixel x) {
		return Pixel(fabs(x.r), fabs(x.g), fabs(x.b));
	}
	void border() {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				Pixel dx(0, 0, 0), dy(0, 0, 0);
				if (i+1 < H)
					dx = data[i+1][j] - data[i][j];
				if (j+1 < W)
					dy = data[i][j+1] - data[i][j];
				dx = pabs(dx), dy = pabs(dy);
				data[i][j] = (dx + dy)/2.0;
			}
		}
	}
	void print() {
		printf("%d %d\n", W, H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].print(), printf("%c", j == W-1 ? '\n' : ' ');
	}
} test;
int main() {
	test.read();
	test.border();
	test.print();
	return 0;
}

