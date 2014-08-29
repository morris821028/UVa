#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
#define maxL ((1024*1024)>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
using namespace std;
int mark[maxL];

void solve(int n, int h[], int record[]) {
    int i, height;
    stack< pair<int, int> > stk;// <height, position>
    pair<int, int> e;
    h[n] = 0;// visual height.
    for(i = 0; i <= n; i++) {
        height = h[i];
        e = make_pair(height, i);
        while(!stk.empty() && height <= stk.top().first)
            e = stk.top(), stk.pop();
        if (height == 0)
            continue;
        if(stk.empty() || height - stk.top().first > e.second - stk.top().second) {
            record[height + (i - e.second + 1)]++;
            stk.push(make_pair(height, e.second));
        } else {
            record[stk.top().first + (i - stk.top().second + 1)]++;
        }
    }
}
int n, m, h[1024];
int main() {
	int testcase;
    char line[1024];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
    	memset(mark, 0, sizeof(mark));
    	memset(h, 0, sizeof(h));
        for(int i = 0; i < n; i++) {
        	scanf("%s", line);
            for (int j = 0; j < m; j++) {
                if (line[j] == '.') {
                    SET(i * 1024 + j);
                }
            }
        }
        int record[2048] = {};
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
            	if(GET(j * 1024 + i))
            		h[j]++;
            	else
            		h[j] = 0;
            }
            solve(n, h, record);
        }
        for (int i = 1; i <= n+m; i++) {
            if (record[i]) {
                printf("%d x %d\n", record[i], i<<1);
            }
        }
    }
    return 0;
}

/*
 1
 6 5
 ..#.#
 .#...
 #..##
 ...#.
 #....
 #..#.
 */
