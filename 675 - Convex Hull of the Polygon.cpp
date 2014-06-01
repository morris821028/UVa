#include <stdio.h>
#include <algorithm>
using namespace std;
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
        x(a), y(b) {}
    bool operator <(const Pt &a) const {
        if(x != a.x)       
            return x < a.x;
        return y < a.y;
    }   
    bool operator ==(const Pt &a) const {
        return x == a.x && y == a.y;
    }
};
int cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m - 1;
}
Pt D[100005], C[100005<<1], p;
Pt I[100005];
int main() {
	int cases = 0;
	char s[1024];
	while(gets(s)) {
		if(cases++ > 0)
			puts("");
		int n = 0, m, x, y;
		sscanf(s, "%d, %d", &x, &y);
		I[n] = D[n] = Pt(x, y);
		n++;
		while(gets(s) && s[0] != '\0') {
			sscanf(s, "%d, %d", &x, &y);
			I[n] = D[n] = Pt(x, y);
			n++;
		}
		m = monotone(n, D, C);
		int mark = -1;
		for(int i = 0; i < n && mark == -1; i++) {
			for(int j = 0; j < m; j++)
				if(C[j] == I[i]) {
					mark = j;
					break;
				}
		}
		for(int i = mark; i < m; i++)
			printf("%d, %d\n", C[i].x, C[i].y);	
		for(int i = 0; i <= mark; i++)
			printf("%d, %d\n", C[i].x, C[i].y);	
	}
	
    return 0;
}
