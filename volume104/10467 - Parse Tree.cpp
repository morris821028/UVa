#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

char g[512][512];
int max_col = 0;
int mfind(string str, char c) {
	int l = 0;
	int ret = string::npos;
	for (int i = 0; i < str.length(); i++) {
		if (l == 0 && str[i] == c)
			ret = i;
		if (str[i] == '(')	l++;
		if (str[i] == ')') 	l--;
	}
	return ret;
}
int dfs(string nonterminal, string str, int row) {
//	cout << nonterminal << " -> " << str << endl;
	int p1, p2, np, ret = max_col;
	if (nonterminal == "E") {
		p1 = mfind(str, '+');
		p2 = mfind(str, '-');
		if(p1 > p2) {
			np = dfs("E", str.substr(0, p1), row+2);
			max_col += 2; 
			for (int i = np; i <= max_col; i++)
				g[row+1][i] = '=';
			g[row+1][++max_col] = '|', g[row][max_col] = 'E', g[row+2][max_col] = '+';
			ret = max_col;
			max_col += 3;
			np = dfs("T", str.substr(p1+1), row+2);
			for (int i = ret + 1; i <= np; i++)
				g[row+1][i] = '=';
		} else if (p1 < p2) {
			np = dfs("E", str.substr(0, p2), row+2);
			max_col += 2; 
			for (int i = np; i <= max_col; i++)
				g[row+1][i] = '=';
			g[row+1][++max_col] = '|', g[row][max_col] = 'E', g[row+2][max_col] = '-';
			ret = max_col;
			max_col += 3;
			np = dfs("T", str.substr(p2+1), row+2);
			for (int i = ret + 1; i <= np; i++)
				g[row+1][i] = '=';
		} else {
			np = dfs("T", str, row+2);
			g[row+1][np] = '|', g[row][np] = 'E';
			ret = np;
		}
	} else if (nonterminal == "T") {
		p1 = mfind(str, '*');
		p2 = mfind(str, '/');
		if(p1 > p2) {
			np = dfs("T", str.substr(0, p1), row+2);
			max_col += 2; 
			for (int i = np; i <= max_col; i++)
				g[row+1][i] = '=';
			g[row+1][++max_col] = '|', g[row][max_col] = 'T', g[row+2][max_col] = '*';
			ret = max_col;
			max_col += 3;
			np = dfs("F", str.substr(p1+1), row+2);
			for (int i = ret + 1; i <= np; i++)
				g[row+1][i] = '=';
		} else if (p1 < p2) {
			np = dfs("T", str.substr(0, p2), row+2);
			max_col += 2; 
			for (int i = np; i <= max_col; i++)
				g[row+1][i] = '=';
			g[row+1][++max_col] = '|', g[row][max_col] = 'T', g[row+2][max_col] = '/';
			ret = max_col;
			max_col += 3;
			np = dfs("F", str.substr(p2+1), row+2);
			for (int i = ret + 1; i <= np; i++)
				g[row+1][i] = '=';
		} else {
			np = dfs("F", str, row+2);
			g[row+1][np] = '|', g[row][np] = 'T';
			ret = np;
		}
	} else if (nonterminal == "F") {
		if (str[0] == 'i') {
			g[row+1][max_col] = '|', g[row][max_col] = 'F';
			ret = max_col;
			dfs(str, str, row+2);
		} else {
			int t = max_col;
			g[row+2][max_col] = '(';
			max_col += 3;
			np = dfs("E", str.substr(1, str.length()-2), row+2);
			for (int i = t; i < np; i++)
				g[row+1][i] = '=';
			g[row+1][np] = '|', g[row][np] = 'F';
			max_col += 3;
			for (int i = np + 1; i <= max_col; i++)
				g[row+1][i] = '=';
			g[row+2][max_col] = ')';
			ret = np;
		}
	} else {
		g[row][max_col] = str[0];
		ret = max_col;
	}
	return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	char line[1048];
	int cases = 0;
	while(scanf("%s", line) == 1) {
		if(cases++)	puts("");
		int node_pos;
		memset(g, ' ', sizeof(g));
		max_col = 0;
		dfs("E", line, 0);
		for (int i = 0; i < 512; i++) {
			for (int j = 512 - 1; j >= 0 && g[i][j] == ' '; j--)
				g[i][j] = 0;
			if(g[i][0])
				puts(g[i]);
		}
	}
	return 0;
}
/*
i+i*i
i+i*(i+i)
i/i-i
i-i/(i+i)
((i+i-i*i-i+i)+(i/i+(i+i-i)))
*/
