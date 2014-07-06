#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
struct Line {
	int x, ly, ry, val;
	Line(int a = 0, int b = 0, int c = 0, int d = 0):
		x(a) , ly(b), ry(c), val(d) {
	}
	bool operator<(const Line &a)  const {
		return x < a.x;
	}
};
struct Node {
	int val[12], label, seg;
};

Node tree[(65536<<1) + 10];
vector<Line> lines;
vector<int> yDVal;
map<int, int> yMAP;
int N, K;
void buildST(int k, int l, int r) {
	memset(&tree[k], 0, sizeof(Node));
	tree[k].seg = yDVal[r+1] - yDVal[l];
	tree[k].val[0] = tree[k].seg;
	if(l >= r)		return;
	int m = (l + r)/2;
	buildST(k<<1, l, m);
	buildST(k<<1|1, m+1, r); 
} 
void modify(int k, int l, int r, int x, int y, int val) {
	if(x <= l && r <= y) {
		tree[k].label += val;
	} else {
		int m = (l + r)/2;
		if(x <= m)
			modify(k<<1, l, m, x, y, val);
		if(y > m)
			modify(k<<1|1, m+1, r, x, y, val);
	}
	if(tree[k].label >= K) {
		for(int i = 0; i <= K; i++)
			tree[k].val[i] = 0;
		tree[k].val[K] = tree[k].seg;
	} else if(l == r) {
		for(int i = 0; i <= K; i++)
			tree[k].val[i] = 0;
		tree[k].val[tree[k].label] = tree[k].seg;
	} else {
		int shift = tree[k].label;

		tree[k].val[K] = 0;
		for(int i = 0; i < shift; i++)
			tree[k].val[i] = 0;
		for(int i = shift; i < K; i++)
			tree[k].val[i] = tree[k<<1].val[i-shift] + tree[k<<1|1].val[i-shift];
		for(int i = K - shift; i <= K; i++)
			tree[k].val[K] += tree[k<<1].val[i] + tree[k<<1|1].val[i];
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &K);
		int lx, ly, rx, ry;
		yDVal.clear(), lines.clear(), yMAP.clear();
		for(int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			rx++, ry++;
			lines.push_back(Line(lx, ly, ry, 1));
			lines.push_back(Line(rx, ly, ry, -1));
			yDVal.push_back(ly);
			yDVal.push_back(ry);
		}
		sort(lines.begin(), lines.end());
		sort(yDVal.begin(), yDVal.end());
		yDVal.erase(unique(yDVal.begin(), yDVal.end()), yDVal.end());
		for(int i = 0; i < yDVal.size(); i++)
			yMAP[yDVal[i]] = i;
		buildST(1, 0, yDVal.size()-2);
		
		long long ret = 0;
		for(int i = 0; i < lines.size() - 1; i++) {
			modify(1, 0, yDVal.size()-2, yMAP[lines[i].ly], yMAP[lines[i].ry]-1, lines[i].val);
//			printf("qq %d %d\n", yMAP[lines[i].ly], yMAP[lines[i].ry]-1);
			ret += (long long)(tree[1].val[K]) * (long long)(lines[i+1].x - lines[i].x);
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
5
10 5
39 59 130 147
7 7 85 10
66 97 153 170
46 52 78 119
42 60 58 160
23 97 35 112
59 11 95 109
84 35 129 51
47 94 59 140
51 75 74 137

10 5
75 35 85 78
50 30 106 87
63 37 154 137
36 42 134 129
95 88 165 187
74 64 105 160
26 71 81 86
91 41 110 125
59 89 64 115
85 49 162 58

10 5
63 81 127 180
61 79 112 153
92 33 100 94
71 51 152 72
49 18 113 116
11 98 53 112
71 67 127 132
14 77 42 163
78 29 98 34
34 66 48 147

10 5
86 10 112 54
46 46 87 78
50 51 149 91
72 77 172 129
33 24 64 101
81 46 152 86
40 8 61 73
76 72 173 147
45 38 125 89
11 2 37 62

10 5
24 74 57 99
45 12 83 37
92 42 170 128
38 63 73 116
74 65 126 97
79 97 154 138
34 55 80 81
63 75 143 173
92 6 180 50
46 37 72 118

*/
