#include <bits/stdc++.h> 
using namespace std;

class IMAGE {
public:
	struct Pixel {
		double r, g, b, a;
		Pixel(double x = 0, double y = 0, double z = 0, double w = 0):
			r(x), g(y), b(z), a(w) {}
		void read() {
			scanf("%lf %lf %lf %lf", &r, &g, &b, &a);
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
    		printf("%d %d %d %d", (int)round(r), (int)round(g), (int)round(b), (int)round(a));
    	}
	};
	int W, H;
	static const int MAXN = 300;
	Pixel data[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}
	void alloc() {
		int TYPE;
		Pixel st, ed;
		scanf("%d %d %d", &W, &H, &TYPE);
		st.read(), ed.read();
		gradient(st, ed, TYPE);
	}
	void gradient(Pixel st, Pixel ed, int TYPE) {
		if (TYPE != 0 && TYPE != 1)
			return;
		if (TYPE == 0) {
			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++) 
					data[i][j] = W-1 ? st + (ed - st) * j / (W-1) : st;
		} else {
			double cx = (H-1)/2.0, cy = (W-1)/2.0;
			double cr = hypot(cx, cy);
			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
					data[i][j] = cr ? st + (ed - st) * hypot(i-cx, j-cy) / cr : st;
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
	test.alloc();
	test.print();
	return 0;
}

