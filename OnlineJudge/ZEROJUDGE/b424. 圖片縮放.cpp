#include <bits/stdc++.h> 
using namespace std;

const double eps = 1e-18;
class IMAGE {
public:
	struct Pixel {
		long double r, g, b, a;
		Pixel(long double x = 0, long double y = 0, long double z = 0, long double w = 0):
			r(x), g(y), b(z), a(w) {}
		void read() {
			int p1, p2, p3, p4;
			scanf("%d %d %d %d", &p1, &p2, &p3, &p4);
			r = p1, g = p2, b = p3, a = p4;
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
    		printf("%.0lf %.0lf %.0lf %.0lf", p1 + eps, p2 + eps, p3 + eps, p4 + eps);
    	}
	};
	int W, H;
	static const int MAXN = 512;
	Pixel data[MAXN][MAXN], tmp[MAXN][MAXN];
	void read() {
		scanf("%d %d", &W, &H);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				data[i][j].read();
	}
	int isValid(int x, int y) {
		return x >= 0 && y >= 0 && x < H && y < W;
	}
	void resize(long double SX, long double SY, int trans = 0) {
		if (trans != 0 && trans != 1)
			return ;			
		int rW = (int) round(SX * W);
		int rH = (int) round(SY * H);
		if (rW > 256 || rH > 256 || rW <= 0 || rH <= 0)
			return ;
		for (int i = 0; i < rH; i++) {
			for (int j = 0; j < rW; j++) {
				long double x = i / SY;
				long double y = j / SX;
				int lx, rx, ly, ry;
				lx = floor(x), rx = ceil(x);
				ly = floor(y), ry = ceil(y);
				
				Pixel v[] = {data[lx][ly], data[lx][ry], data[rx][ly], data[rx][ry]};
				int px[] = {lx, lx, rx, rx};
				int py[] = {ly, ry, ly, ry};
				if (trans == 0) {
					Pixel t1, t2;
					if (isValid(px[0], py[0]) && isValid(px[1], py[1]) && isValid(px[2], py[2]) && isValid(px[3], py[3])) {
						long double a = x - lx, b = y - ly;
						tmp[i][j] = v[0] * (1 - a) * (1 - b) + v[2] * a * (1 - b)
									+ v[1] * (1 - a) * b + v[3] * a * b;
					} else if (isValid(px[0], py[0]) && isValid(px[2], py[2])) {
						if (rx != lx)
							tmp[i][j] = v[0] + (v[2] - v[0]) * ((x - lx) / (rx - lx));
						else
							tmp[i][j] = v[0];
					} else if (isValid(px[0], py[0]) && isValid(px[1], py[1])) {
						if (ry != ly)
							tmp[i][j] = v[0] + (v[1] - v[0]) * ((y - ly) / (ry - ly));
						else
							tmp[i][j] = v[0];
					} else if (isValid(px[0], py[0])) {
						tmp[i][j] = v[0];
					} else {
						puts("WTF");
					}
				} else {
					int c = -1;
					double mndist;
					for (int k = 0; k < 4; k++) {
						if (!isValid(px[k], py[k]))
							continue;
						double d = (x-px[k])*(x-px[k])+(y-py[k])*(y-py[k]);
						if (c == -1 || mndist > d)
							c = k, mndist = d;
					}
					tmp[i][j] = data[px[c]][py[c]];
				}
			}
		}
		W = rW, H = rH;
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
	double X, Y;
	int TYPE;
	scanf("%lf %lf %d", &X, &Y, &TYPE);
	test.read();
	test.resize(X, Y, TYPE);
	test.print();
	return 0;
}
/*
2 2 0
2 1 
1 2 3 255 4 5 6 255 
*/ 
