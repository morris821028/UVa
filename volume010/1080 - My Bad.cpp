#include <stdio.h> 
#include <vector>
#include <assert.h>
#include <string.h>
#include <algorithm>
using namespace std;
class Circuit {
public:
	enum LOGIC {AND, OR, XOR, NOT, FV, F0, F1};
	struct Gate {
		LOGIC type;
		int p1, p2;
	} gates[1024];
	int inVal[512], outVal[512];
	int visited[512], sick[512];
	LOGIC sickType[512];
	int div = 256;
	void addGate(int id, LOGIC t, int in1, int in2 = 0) {
		gates[id].type = t;
		gates[id].p1 = in1, gates[id].p2 = in2;
	}
	int getInId(int x) {
		return div + x;
	}
	int getId(char s[]) {
		int x;
		sscanf(s+1, "%d", &x);
		return (s[0] == 'i') ? getInId(x) : x;
	}
	int getOutput(int id) {
		if (id > div)		return inVal[id - div];
		if (visited[id])	return outVal[id];
		visited[id] = 1;
		int &val = outVal[id];
		val = 0;
		if (gates[id].type == AND)
			val = (getOutput(gates[id].p1) & getOutput(gates[id].p2));
		if (gates[id].type == OR)
			val = (getOutput(gates[id].p1) | getOutput(gates[id].p2));
		if (gates[id].type == XOR)
			val = (getOutput(gates[id].p1) ^ getOutput(gates[id].p2));
		if (gates[id].type == NOT)
			val = !(getOutput(gates[id].p1));
		if (!sick[id])
			return val;
		if (sickType[id] == FV)
			return val = !val;
		else if (sickType[id] == F0)
			return val = 0;
		else
			return val = 1;
	}
	void clearSick()  {
		memset(sick, 0, sizeof(sick));
	}
	void clear() {
		memset(visited, 0, sizeof(visited));
	}
} g;

int N, G, U, B;
int outGate[128], IN[1024][128], OUT[1024][128];
char s[128], s1[128], s2[128];

int singleTest() {
	int ok = 1;
	for (int i = 0; i < B && ok; i++) {
		g.clear();
		for (int j = 1; j <= N; j++)
			g.inVal[j] = IN[i][j];
		for (int j = 1; j <= U; j++) {
			int v = g.getOutput(outGate[j]);
			ok &= v == OUT[i][j];
		}
	} 
	return ok;
}
void test() {
	g.clearSick();

	if (singleTest()) {
		puts("No faults detected");
		return;
	} 
	
	vector< pair<int, int> > err;
	for (int i = 1; i <= G; i++) {
		g.clearSick();
		g.sick[i] = 1, g.sickType[i] = Circuit::FV;
		if (singleTest())
			err.push_back(pair<int, int>(i, 0));
		g.sick[i] = 1, g.sickType[i] = Circuit::F0;
		if (singleTest())
			err.push_back(pair<int, int>(i, 1));	
		g.sick[i] = 1, g.sickType[i] = Circuit::F1;
		if (singleTest())
			err.push_back(pair<int, int>(i, 2));
		if (err.size() > 1)
			break;
	}
	if (err.size() > 1)
		puts("Unable to totally classify the failure");
	else {
		if (err[0].second == 0)
			printf("Gate %d is failing; output inverted\n", err[0].first);
		else if (err[0].second == 1)
			printf("Gate %d is failing; output stuck at 0\n", err[0].first);
		else if (err[0].second == 2)
			printf("Gate %d is failing; output stuck at 1\n", err[0].first);
	}
}
int main() {
	int cases = 0;
	while (scanf("%d %d %d", &N, &G, &U) == 3 && N) {
		for (int i = 1; i <= G; i++) {
			scanf("%s", s);
			if (s[0] == 'a') {
				scanf("%s %s", s1, s2);
				g.addGate(i, Circuit::AND, g.getId(s1), g.getId(s2));
			} else if (s[0] == 'o') {
				scanf("%s %s", s1, s2);
				g.addGate(i, Circuit::OR, g.getId(s1), g.getId(s2));
			} else if (s[0] == 'x') {
				scanf("%s %s", s1, s2);
				g.addGate(i, Circuit::XOR, g.getId(s1), g.getId(s2));
			} else {
				scanf("%s", s1);
				g.addGate(i, Circuit::NOT, g.getId(s1));
			}
		}
		
		for (int i = 1; i <= U; i++)
			scanf("%d", &outGate[i]);
		scanf("%d", &B);
		assert(B < 1024);
		for (int i = 0; i < B; i++) {
			for (int j = 1; j <= N; j++)
				scanf("%d", &IN[i][j]);
			for (int j = 1; j <= U; j++)
				scanf("%d", &OUT[i][j]);
		}
		
		printf("Case %d: ", ++cases);
		test();
	}
	return 0;
}
/*
2 2 1 
o i1 i2 
n g1 
2 
2 
1 0 0 
0 0 1 

2 1 1 
a i1 i2 
1 
1 
1 0 1 

2 1 1 
a i1 i2 
1 
2 
1 0 1 
1 1 1 

1 1 1 
n i1 
1 
2 
1 1 
0 0 

3 4 4 
n g4 
a i1 i2 
o i2 i3 
x i3 i1 
2 3 4 1 
4 
0 1 0 0 1 0 1
0 1 1 0 1 1 0
1 1 1 0 1 0 1
0 0 0 0 0 0 1

0 0 0
*/
