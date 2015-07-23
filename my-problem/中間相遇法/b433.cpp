#include <bits/stdc++.h> 
using namespace std;

typedef unsigned short int UINT16;
class SimpleIdea {
public:
	UINT16 key;
	SimpleIdea(UINT16 k = 0):
		key(k) {}
	UINT16 encrypt(UINT16 m) {
		return (rotate_left(m, key&15) + key)^key;
	}
	UINT16 decrypt(UINT16 m) {
		return rotate_left((m^key)+(~key)+1, 16 - (key&15));
	}
private:
	UINT16 rotate_left(UINT16 x, UINT16 n) {
    	return  (x << n) | (x >> (16-n));
	}
} test;
int main() {
	int C, M;
	while (scanf("%d %d", &C, &M) == 2) {
		unordered_map<int, int> H1, H2;
		for (int i = 0; i < (1<<16); i++) {
			int key1 = i, key2 = i;
			test.key = key1;
			H1[test.encrypt(M)]++;
			test.key = key2;
			H2[test.decrypt(C)]++;
		}
		
		int ret = 0;
		for (auto &x : H1) {
			if (H2.count(x.first))
				ret += H2[x.first] * x.second;
		}
		printf("%d\n", ret);
	}
	return 0;
}
