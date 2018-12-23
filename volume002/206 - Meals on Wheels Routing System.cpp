#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
struct Loc {
	int x, y;
	string name;
	Loc(int x, int y, char *s): x(x), y(y) {
		name = s;
	}
	double angle() const {
		double a = atan2(y, x);
		if (a < 0)
			a += 2*pi;
		return a;
	}
	double len() const {
		return (double)x*x + (double)y*y;
	}
	bool operator<(const Loc &l) const {
		double a = angle();
		double b = l.angle();
		if (a != b)
			return a < b;
		return len() < l.len();
	}
};
int main() {
	char data_set_id[1024];
	int cases = 0;
	int n, m;
	char c;
	while (fgets(data_set_id, 1024, stdin)) {
		if (cases++)
			puts("***********************************");
		data_set_id[strlen(data_set_id)-1] = '\0';
		scanf("%d %d", &n, &m);
		while (getchar() != '\n');
		vector<Loc> A;
		for (int i = 0; i < m; i++) {
			int x, y;
			char name[64];
			fgets(name, 64, stdin);
			name[strlen(name)-1] = '\0';
			scanf("%d %d", &x, &y);
			while (getchar() > '\n');
			A.push_back(Loc(x, y, name));
		}
		
		printf("%s\n", data_set_id);
		printf("Number of Customers: %-10d Number of Routes: %d\n\n", m, n);

		sort(A.begin(), A.end());

		int tot = 0;
		for (int i = 0, pos = 0; i < n; i++) {
			printf("Route ==> %d\n", i+1);
			int v = m/n + (i < m%n), cost = 0;
			int tx = 0, ty = 0;
			for (int j = 0; j < v; j++) {
				printf("Customer: %s\n", A[pos].name.c_str());
				cost += abs(tx - A[pos].x) + abs(ty - A[pos].y);
				tx = A[pos].x, ty = A[pos].y;
				pos++;
			}
			cost += abs(tx) + abs(ty);
			printf("Route Length ==> %d\n\n", cost);
			tot += cost;
		}
		printf("Total Route Length ==> %d\n", tot);
	}
	return 0;
}
/*
Sample Route List 1
4 10
able
1 2
baker
-3 6
charlie
-4 -5
donald
4 -7
eloise
3 4
frank
2 2
gertrude
5 9
horace
-2 -5
inez
5 -3
james
0 1
Sample Route List 2
1 1
charlie
1 1
*/
