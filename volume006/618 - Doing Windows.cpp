#include <bits/stdc++.h>
using namespace std;

struct Rect {
	int w, h;
	Rect() {}
	Rect(int w, int h): w(w), h(h) {}
	void reduce() {
		int g = __gcd(w, h);
		w /= g, h /= g;
	}
	void rotate() {
		swap(w, h);
	}
};

int lcm(int x, int y) {
	return x / __gcd(x, y) * y;
}

int place(Rect win, Rect dia[], int n);
/*
|A|B|C|D|
*/
int case_1(Rect win, Rect dia[], int n) {
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (win.h%dia[i].h)
			return 0;
		s += win.h / dia[i].h * dia[i].w;
		if (s > win.w)
			return 0;
	}
	return s == win.w;
}

/*
|  A  |
|B|C|D|
*/
int case_2(Rect win, Rect dia[], int n) {
	if (win.w%dia[0].w || n < 1)
		return 0;
	int s = win.w / dia[0].w * dia[0].h;
	if (s > win.h)
		return 0;
	int h = win.h - s;
	return place(Rect(win.w, h), dia+1, n-1);
}

/*
| A | B | 
| C | D |
*/
int case_3(Rect win, Rect dia[], int n) {
	int ab_h = lcm(dia[0].h, dia[1].h);
	if (ab_h > win.h)
		return 0;
	int ab_w = ab_h / dia[0].h * dia[0].w + ab_h / dia[1].h * dia[1].w;
	if (win.w%ab_w)
		return 0;
	int s = win.w / ab_w * ab_h;
	if (s > win.h)
		return 0;
	int h = win.h - s;
	return place(Rect(win.w, h), dia+2, n-2);
}
int _place(Rect win, Rect dia[], int n) {
	if (case_1(win, dia, n))
		return 1;
	if (n > 1) {
		Rect d[6];
		for (int i = 0; i < n; i++) {
			memcpy(d, dia, sizeof(dia[0])*n);
			swap(d[0], d[i]);
			if (case_2(win, d, n))
				return 1;
		}
	}
	if (n > 2) {
		Rect d[6];
		for (int i = 0; i < (1<<n); i++) {
			if (__builtin_popcount(i) != 2)
				continue;
			Rect *st = d, *ed = d+n-1;
			for (int k = 0; k < n; k++) {
				if ((i>>k)&1) {
					*st = dia[k], st++;
				} else {
					*ed = dia[k], ed--;
				}
			}
			if (case_3(win, d, n))
				return 1;
		}
	}
	return 0;
}

int place(Rect win, Rect dia[], int n) {
	if (n == 0 || _place(win, dia, n))
		return 1;
	win.rotate();
	for (int i = 0; i < n; i++)
		dia[i].rotate();
	return _place(win, dia, n);
}
int main() {
	int w, h;
	int cases = 0;
	while (scanf("%d %d", &w, &h) == 2 && w) {
		Rect win(w, h);
		Rect dia[4];
		for (int i = 0; i < 4; i++) {
			scanf("%d %d", &w, &h);
			dia[i] = Rect(w, h);
			dia[i].reduce();
		}

		int ret = place(win, dia, 4);
		printf("Set %d: %s\n", ++cases, ret ? "Yes" : "No");
	}
	return 0;
}
/*
400 400 10 10 35 35 15 15 100 100
200 300 10 10 20 20 30 45 40 60
200 250 10 10 20 20 30 45 40 60

260 100 2 1 6 4 3 2 3 1
260 100 6 4 2 1 3 2 3 1
260 100 6 4 3 2 2 1 3 1

240 360 3 4 3 10 3 2 15 16
240 360 15 16 3 4 3 10 3 2

0 0
*/
