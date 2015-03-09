#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct event {
	int time;
	string site, kind;
	bool operator<(const event &e) const {
		return time < e.time;
	}
};
struct outItem {
	int salary, i;
	string site;
	bool operator<(const outItem &e) const {
		if (salary != e.salary)
			return salary < e.salary;
		return i < e.i;
	}
};
int main() {
	int syy, smm, eyy, emm;
	int yyyy, yy, mm, M, n, m;
	int X, Y;
	int salary[128];
	char site[128][128], s1[128], s2[128], line[128];
	event D[1024];
	while (scanf("%d/%d %d", &syy, &smm, &M) == 3) {
		n = m = 0;
		while (scanf("%s", site[n]) == 1) {
			if (!strcmp(site[n], "----"))
				break;
			scanf("%d", &salary[n]);
			n++;
		}
		scanf("%d %d", &X, &Y);
		while (scanf("%s", line) == 1) {
			if (!strcmp(line, "----"))
				break;
			sscanf(line, "%d/%d", &yy, &mm);
			scanf("%s %s", s1, s2);
			D[m].time = yy * 100 + mm;
			D[m].site = s1, D[m].kind = s2;
			m++;
		}
		sort(D, D+m);
		scanf("%d/%d", &eyy, &emm);
		printf("%d/%02d ", eyy, emm);
		
		int idx = 0;
		do {
			smm++;
			if (smm == 13)	smm = 1, syy++;
			for (int i = 0; i < n; i++)
				M += salary[i];
			for (; idx < m; idx++) {
				if (D[idx].time == syy * 100 + smm) {
					int u = 0;
					for (int i = 0; i < n; i++) {
						if (!strcmp(site[i], D[idx].site.c_str()))
							u = i;
					}
					if (D[idx].kind == "BUILT") {
						salary[u] += X;
					} else if (D[idx].kind == "BOOST") {
						salary[u] += X * X;
					} else if (D[idx].kind == "DAMAGE") {
						salary[u] = max(0, salary[u] - Y);
					} else if (D[idx].kind == "RUIN") {
						salary[u] = 0;
					}
				} else {
					break;
				}
			}			
		} while (syy != eyy || smm != emm);
		printf("%d\n", M);
		outItem out[1024];
		for (int i = 0; i < n; i++) {
			out[i].salary = salary[i];
			out[i].i = i;
			out[i].site = site[i];
		}
		sort(out, out + n);
		for (int i = 0; i < n; i++)
			printf("%s %d\n", out[i].site.c_str(), out[i].salary);
	}
	return 0;
}
