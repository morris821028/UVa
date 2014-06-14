#include <stdio.h> 

int main() {
	int testcase, cases = 0;
	int M; /* the device takes a reading every M seconds. */
	int S; /* The device will instantly take a reading when the ¡¥Startup delay¡¦ ends. */
	int threshold[4]; /* */
	int C; /* */
	int enable[4], trigger[4]; /* trigger 0 <, 1 > */
	int K, time, temp;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &M);
		scanf("%d", &S);
		for(int i = 0; i < 4; i++)
			scanf("%d", &threshold[i]);
		scanf("%d", &C);
		
		for(int i = 0; i < 4; i++)
			enable[i] = (C>>i)&1;
		for(int i = 4; i < 8; i++)
			trigger[i - 4] = (C>>i)&1;
		
		int result[4] = {};
		int now_time = 0, L, R;
		scanf("%d", &K);
		while(K--) {
			scanf("%d %d", &time, &temp);
			L = now_time;
			R = now_time + time;
			if(R < S) {
				
			} else {
				int last_read = R / M * M;
				if(L <= last_read && last_read <= R && last_read >= S) {
					for(int i = 0; i < 4; i++) {
						if(trigger[i] == 0) {
							result[i] |= (temp < threshold[i])&enable[i];
						} else {
							result[i] |= (temp > threshold[i])&enable[i];
						}
					}
				}
			}
			now_time = R;
		}
		printf("Case %d:", ++cases);
		for(int i = 0; i < 4; i++)
			printf(" %s", result[i] ? "yes" : "no");
		puts("");
	}
	return 0;
}
