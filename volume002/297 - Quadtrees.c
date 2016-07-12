#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int len = 32;
int mat[len][len];
int cnt;
char quad;

void build(char q,int c,int r, int w)
{
	cin >> q;
	if (q == 'p')
	{
		build(q, c+w/2, r,     w/2);
		build(q, c,     r,     w/2);
		build(q, c,     r+w/2, w/2);
		build(q, c+w/2, r+w/2, w/2);
	}
	else if (q == 'f')
		for (int i = r; i < (r + w);++i)
			for (int j = c; j < (c + w); ++j)
				if (mat[i][j] == 0)
				{
					mat[i][j] = 1;
					cnt++;
				}
}

int main()
{
	int cas;
	scanf("%d",&cas);
	while (cas--)
	{
		cnt = 0;
		memset(mat, 0, sizeof(mat));
		build(quad, 0, 0, 32);
		build(quad, 0, 0, 32);
		cout << "There are " << cnt << " black pixels." << '\n';
	}
	return 0;
}
