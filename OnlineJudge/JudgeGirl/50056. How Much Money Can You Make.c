#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		char m_str[128][64];
		int m_cnt[128], m_pri[128];
		for (int i = 0; i < n; i++)
			scanf("%s %d %d", m_str[i], &m_cnt[i], &m_pri[i]);
		
		char ret[128] = "";
		int mx_profit = -1;
		for (int i = 0; i < m; i++) {
			char p_str[128], t_str[128];
			int o, sell;
			scanf("%s %d", p_str, &o);
			int mn = INT_MAX, unit_pri = 0;
			for (int j = 0; j < o; j++) {
				int amount = 0, dv;
				scanf("%s %d", t_str, &dv);
				for (int k = 0; k < n; k++) {
					if (!strcmp(t_str, m_str[k]))
						amount = m_cnt[k] / dv, unit_pri -= dv * m_pri[k];
				}
				mn = mn < amount ? mn : amount;
			}
			
			scanf("%d", &sell);
			unit_pri += sell;
			if (unit_pri * mn > mx_profit || 
				(unit_pri * mn == mx_profit && strcmp(p_str, ret) < 0))
				mx_profit = unit_pri * mn, strcpy(ret, p_str);
//			printf("%s %d\n", p_str, unit_pri * mn);
		}
		printf("%s %d\n", ret, mx_profit);
	}
	return 0;
}


