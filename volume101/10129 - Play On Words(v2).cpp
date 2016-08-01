#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100010;
const int let = 300;
string words[maxn];
bool possible;
int mat[let][let];
int i,cnt,n;

bool dfs(int u)
{
	if (cnt == n)
		return true;
	for (int v = 0; v < 26; v++)
	{
		if (mat[u][v] > 0)
		{
			cnt++;
			mat[u][v]--;
			if(dfs(v))
				return true;
			mat[u][v]++;
			cnt--;
		}
	}
	return false;
}

int main()
{
	int cas;
	cin >> cas;
	while (cas--)
	{
		possible = false;
		memset(mat, 0, sizeof(mat));
		i = 0;

		scanf("%d", &n);
		getchar();
		int temp = n;
		while (temp--)
		{
			getline(cin, words[i]);
			mat[words[i][0]-'a'][words[i][words[i].length() - 1]-'a']++;
			i++;
		}

		for (int j = 0; j < i; j++)
		{
			cnt = 0;
			possible = dfs(words[j][0]-'a');
			if (possible)	break;
		}

		if (possible)	cout << "Ordering is possible." << '\n';
		else    cout << "The door cannot be opened." << '\n';
	}
	
	return 0;
}
