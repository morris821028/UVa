#include <stdio.h> 

/*
6 4 -> 0 1 2 3 4 5 -> 1st: 0 1 2 3(X) 4(_) 5 -> 4(_) 2 1 0 5
5 4 -> 0 1 2 3 4 -> 1st: 0 1 2 3(X) 4(_) -> 4(_) 2 1 0
4 4 -> 0 1 2 3   -> 1st: 0(_) 1 2 3(X)   -> 0(_) 2 1
3 4 -> 0 1 2     -> 1st: 0(X) 1(_) 2	 -> 1(_) 2
2 4 -> 0 1		 -> 1st: 0(_) 1(X)		 -> 0(_)
1 4 -> 0		 -> 1st: 0				 
										 ^^trim, and then reverse squence
1 4 save 0
2 4 save 0
3 4 save 1 by (n, m) = (2, 4), 1 = pos(1 2)[0]
4 4 save 2 by (n, m) = (3, 4), 2 = pos(0, 2, 1)[1]
5 4 save 1 by (n, m) = (4, 4), 1 = pos(4, 2, 1, 0)[2]
*/
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		int s = 0;
		for (int i = 1; i <= n; i++) {
			int pos = m%i; // (_) pos, (m-1)%i = (X) pos
			if (s == 0)
				s = pos;
			else if (s < pos)
				s = (pos - 1 - s)%i;
			else
				s = (i - 1 - (s - pos))%i;
		}
		printf("%d\n", s+1);
	}
	return 0;
}
/*
10 1
10 5
10 10
5 5
5 4
*/

/*
1 4
2 4
3 4
4 4
5 4
6 4  

1
1
2
3
2
3
*/ 
