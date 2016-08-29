#include <iostream>
#include <string>
using namespace std;

const int maxn = 100005;
int n, L, start, ending,temp;
double maxd;
int DNA[maxn],cav[maxn];
string str;

inline int cntAverage(int L, int r, int LL, int rr, int DNA[]){
	return (DNA[r]-DNA[L])*(rr-LL) - (DNA[rr]-DNA[LL])*(r-L);
}

inline void changePoint(int pits,int bump){
	double temp;
	temp = cntAverage(pits, bump, start-1, ending, DNA);
	if (temp < 0) return;
	if (temp || (bump-pits) < (ending-start+1)){
		maxd = temp;
		start = pits + 1;
		ending = bump;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int cas;
	cin >> cas;
	while (cas--){
		int find = 0, cor = -1;
		cin >> n >> L; cin.get();
		getline(cin, str);
		for (int i = 1; i <= n; ++i)
			DNA[i] = DNA[i-1] + (str[i-1] == '1');
		maxd = DNA[L] / L, start = 1, ending = L;
		for (int i = L; i <= n; ++i){
			temp = i - L;
			while (find < cor && cntAverage(cav[cor], temp, cav[cor - 1], cav[cor], DNA) <= 0)
				--cor;
			cav[++cor] = temp;
			while (find < cor && cntAverage(cav[find], i, cav[find + 1], i, DNA) <= 0)
				++find;
			changePoint(cav[find],i);
		}
		cout << start << ' ' << ending << '\n';
	}
	return 0;
}
