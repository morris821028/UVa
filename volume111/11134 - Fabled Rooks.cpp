#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int maxn = 5100;
int n, possi;
set<int> setX, setY;
int idxX[maxn], idxY[maxn]; 

class rect{
public:
	int l, r, id;
	bool operator<(rect &);
} rectX[maxn],rectY[maxn];

bool rect::operator< (rect &rectB){
	return r < rectB.r;
}

inline void inputRect(){
	setX.clear();
	setY.clear();
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &rectX[i].l, &rectY[i].l,
						  &rectX[i].r, &rectY[i].r);
		rectX[i].id = rectY[i].id = i;
		setX.insert(i);
		setY.insert(i);
	}
	setX.insert(maxn);
	setY.insert(maxn);
}

int main(){
	while (scanf("%d", &n) == 1 && n){
		inputRect();
		sort(rectX+1, rectX+n+1);
		sort(rectY+1, rectY+n+1);
		possi = true;
		for (int i = 1; i <= n && possi; ++i) {
			int tempX = *setX.lower_bound(rectX[i].l);
			if (tempX > rectX[i].r) { 
				possi = false;
			}
			idxX[rectX[i].id] = tempX;
			setX.erase(tempX);

			int tempY = *setY.lower_bound(rectY[i].l);
			if (tempY > rectY[i].r) { 
				possi = false;
			}
			idxY[rectY[i].id] = tempY;
			setY.erase(tempY);
		}
		if (possi)
			for (int i = 1; i <= n; ++i)
				printf("%d %d\n", idxX[i], idxY[i]);
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}
