#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 524288;
int N, pass[MAXN];
struct Node {
	long long arrive_time, v;
	int id;
	Node(long long a = 0, int b = 0, long long c = 0):
		arrive_time(a), id(b), v(c) {}
	bool operator<(const Node &a) const {
		if (arrive_time != a.arrive_time)
			return arrive_time < a.arrive_time;
		return v < a.v;
	}
};
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		
		set<Node> pQ;
		int id = 0;
		long long D, H, M;
		for (int i = 0; i < N; i++) {
			scanf("%lld %lld %lld", &D, &H, &M);
			for (int j = 0; j < H; j++) {
				long long arrive_time = (360 - D) * (M + j);
				pQ.insert(Node(arrive_time, id, M + j));
				pass[id] = 0, id++;
			}
		}
		
		int ret = id, encounter = id;
		
		for (; encounter <= 2 * id; ) {
			Node u = *pQ.begin(); 			// extract minimum
			
			ret = min(ret, encounter);
			
			if (pass[u.id])
				encounter++;
			else
				encounter--;
			pass[u.id] = 1;
			
			pQ.erase(pQ.begin());
			pQ.insert(Node(u.arrive_time + u.v * 360, u.id, u.v));
		}
		
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
