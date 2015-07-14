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
	Pixel data[MAXN][MAXN], tmp[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}
	Pixel pabs(Pixel x) {
		return Pixel(fabs(x.r), fabs(x.g), fabs(x.b));
	}
	Pixel getPixel(int x, int y) {
		if (x >= 0 && y >= 0 && x < H && y < W)
			return data[x][y];
		if (y < 0)	return data[min(max(x, 0), H-1)][0];
		if (y >= W)	return data[min(max(x, 0), H-1)][W-1];
		if (x < 0)	return data[0][min(max(y, 0), W-1)];
		if (x >= H)	return data[H-1][min(max(y, 0), W-1)];
		return Pixel(0, 0, 0);
	}
	void border() {
		const int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
		const int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
		const int xw[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
		const int yw[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				Pixel Dx(0, 0, 0), Dy(0, 0, 0);
				for (int k = 0; k < 9; k++) {
					Dx = Dx + getPixel(i+dx[k], j+dy[k]) * xw[k];
					Dy = Dy + getPixel(i+dx[k], j+dy[k]) * yw[k];
				}
				Dx = pabs(Dx), Dy = pabs(Dy);
				tmp[i][j] = (Dx + Dy)/8.0;
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
	test.read();
	test.border();
	test.print();
	return 0;
}

