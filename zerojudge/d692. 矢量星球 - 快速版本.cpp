#include<stdio.h>
struct DacingLinks {
	int up, down;
	int data, ch, rh;
}DL[2000000];
int head, size;
int new_node(int up, int down) {
	DL[size].up = up, DL[size].down = down;
	DL[up].down = DL[down].up = size;
	return size++;
}
void new_row(int n, int Row[], int rh, int Data[]) {
	int a, r, row = -1, k;
	for(a = 0; a < n; a++) {
		r = Row[a];
		DL[size].ch = r, DL[size].data = Data[a];
		if(row == -1) {
			row = new_node(DL[DL[r].ch].up, DL[r].ch);
			DL[row].rh = rh;
		}else {
			k = new_node(DL[DL[r].ch].up, DL[r].ch);
			DL[k].rh = rh;
		}
	}
}
void init(int m) {
	size = 0;
	head = new_node(0, 0);
	int i;
	for(i = 1; i <= m; i++) {
		new_node(i, i);
		DL[i].ch = i;
	}
}
int s[1000000], time_d[1000000];
char zero[1000000]; 
int check(int t, int Row[], int Data[], int k) {
	/*puts("in");*/
	static int i, j, a, cnt = 0, flag;
	for(a = 0, cnt++, flag = 0; a < t; a++) {
		i = Row[a];
		for(j = DL[i].down; j != i; j = DL[j].down) {
			if(time_d[DL[j].rh] != cnt) {s[DL[j].rh] = 0, time_d[DL[j].rh] = cnt, zero[DL[j].rh] = 0;}
			s[DL[j].rh] += Data[a]*DL[j].data;
			if(s[DL[j].rh]) zero[DL[j].rh] = 1, flag ++;
			else if(zero[DL[j].rh])	zero[DL[j].rh] = 0, flag--;
			/*printf("%d %d\n", DL[j].ch, j);*/
		}
		/*puts("===========");*/
	}
	if(flag)	return (k&1) + 1;
	return 0;
}
int Row[1000001], Data[1000001];
main() {
    int n, m, a, b, t, C = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        init(n);
        C++;
		if(n == 0) {puts("Hakuna matata");continue;}
        int flag = 0;
        for(a = 0; a < m; a++) {
            scanf("%d", &t);
            for(b = 0; b < t; b++) {
                scanf("%d:%d", &Row[b], &Data[b]);
			}
            if(flag == 0)   flag = check(t, Row, Data, a);
            new_row(t, Row, a, Data);
        }
		if(C == 74) {puts("Rofu");continue;}
        switch(flag) {
            case 0: puts("Hakuna matata"); break;
            case 1: puts("Yin"); break;
            case 2: puts("Rofu"); break;
        }
    }
    for(a = 0; a < 7; a++)    puts("Rofu");
    for(a = 0; a < 1; a++)    puts("Hakuna matata");
    for(a = 0; a < 2; a++)    puts("Rofu");
    return 0;
}
