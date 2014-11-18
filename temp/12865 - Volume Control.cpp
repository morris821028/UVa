#include <stdio.h> 
#include <set>
#include <math.h>
#include <vector>
using namespace std;

int main() {
	int ret[65536] = {1}, sum = 1;
	int nop[32767] = {}, cases = 0;
	for (int i = 1; i <= 30000; i++) {
		vector<int> f;
		int first_prime;
		for (int j = 2; j * j <= i; j++) {
			if (i%j == 0) {
				f.push_back(j);
			}
		}
		// i * j == p * q (p, q < i)
		// i = a * b, p = a * ?1, q = b * ?2
		// j = ?1 * ?2
		cases++;
		first_prime = f.size() ? f[0] : i;
		for (int j = 0, q1, q2 = 2; j < f.size(); j++) { // f[j] x (i / f[j])
			for (; q2 < f[j]; q2++) { // ?2 < a, ?1 < b
				for (q1 = i/ f[j] - 1; q1 >= 1; q1--)
					nop[q1 * q2] = cases;
			}
		}
		for (int j = i / first_prime; j <= i; j++)
			sum += nop[j] != cases;
		ret[i] = sum;
	}
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", ret[n]);
	}
	return 0;
}
