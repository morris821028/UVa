#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
class ApplesAndOrangesEasy {
public:
	int maximumApples(int N, int K, vector<int> info) {
		const int MAXN = 4096;
		int A[MAXN] = {}, apple = K/2;
		int ret = (int) info.size();
		memset(A, -1, sizeof(A));
		for (int i = 0; i < info.size(); i++)
			A[info[i]] = 1;
		for (int i = N+1; i <= N + K; i++)
			A[i] = 0;
		for (int i = N; i >= 1; i--) {
			int sum = 0;
			for (int j = i; j < i+K; j++)
				sum += A[j] >= 1;
			if (sum < apple && A[i] == -1)
				A[i] = 2, ret++, sum++;
			if (sum > apple) {
				for (int j = i; j < i+K; j++) {
					if (sum > apple && A[j] == 2) {
						A[j] = -1, ret--, sum--;
					}
				}
			}
		}
		return ret;
	}
};
int main() {
	ApplesAndOrangesEasy ap;
	int a[] = {1, 3};
	ap.maximumApples(3, 2, vector<int>(a, a + 2));
	return 0;
}
