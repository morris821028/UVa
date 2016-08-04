#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

#define pos_now link[i][j]
#define pos_next link[i+next[0][k]][j+next[1][k]]
#define pos_a conn[queue_fro[fro_fro].a][i]
#define pos_b conn[queue_fro[fro_fro].b][j]
#define pos_c conn[queue_fro[fro_fro].c][k]
#define pos_A conn[queue_back[back_fro].a][i]
#define pos_B conn[queue_back[back_fro].b][j]
#define pos_C conn[queue_back[back_fro].c][k]

class Node{
public:
	int a; int b; int c;
};

const int next[2][4] = { { 0, 1, 0, -1 },
			 { 1, 0, -1, 0 } };
int w, h, n, num;
int link[20][20], conn[305][7], vis[305][305][305];
int beg[3], end[3];
int step_fro, step_back,
	back_fro, back_rear,
	 fro_fro,  fro_rear;
Node queue_fro[4000000], queue_back[4000000];
char map[20][20];

void bfs(){
	int fro_cnt = 1, back_cnt = 1;
	vis[beg[0]][beg[1]][beg[2]] = ++step_fro;
	vis[end[0]][end[1]][end[2]] = ++step_back;
	fro_fro  = back_fro  = 0;
	fro_rear = back_rear = 1;
	queue_fro[0].a  = beg[0],queue_fro[0].b  = beg[1],queue_fro[0].c  = beg[2];
	queue_back[0].a = end[0],queue_back[0].b = end[1],queue_back[0].c = end[2];

	while (fro_fro < fro_rear){
		++step_fro;
		while (fro_cnt--){
			for (int i = 0; pos_a != 0; ++i)
			for (int j = 0; pos_b != 0; ++j)
			for (int k = 0; pos_c != 0; ++k){
				if (beg[2] != 303){
					if (pos_a == queue_fro[fro_fro].b && pos_b == queue_fro[fro_fro].a) continue;
					if (pos_a == queue_fro[fro_fro].c && pos_c == queue_fro[fro_fro].a) continue;
					if (pos_b == queue_fro[fro_fro].c && pos_c == queue_fro[fro_fro].b) continue;
					if (pos_a == pos_b || pos_a == pos_c || pos_b == pos_c) continue;
				}
				else if (beg[1] != 303){
					if (pos_a == queue_fro[fro_fro].b && pos_b == queue_fro[fro_fro].a) continue;
					if (pos_a == pos_b) continue;
				}

				if (vis[pos_a][pos_b][pos_c] > 1000) return;
				if (vis[pos_a][pos_b][pos_c] > 0)  continue;

				vis[pos_a][pos_b][pos_c] = step_fro;
				queue_fro[fro_rear].a = pos_a;
				queue_fro[fro_rear].b = pos_b;
				queue_fro[fro_rear].c = pos_c;
				++fro_rear;
			}
			++fro_fro;
		}
		fro_cnt = fro_rear - fro_fro;

		++step_back;
		while (back_cnt--){
			for (int i = 0; pos_A != 0; ++i)
			for (int j = 0; pos_B != 0; ++j)
			for (int k = 0; pos_C != 0; ++k){
				if (beg[2] != 303){
					if (pos_A == queue_back[back_fro].b && pos_B == queue_back[back_fro].a) continue;
					if (pos_A == queue_back[back_fro].c && pos_C == queue_back[back_fro].a) continue;
					if (pos_B == queue_back[back_fro].c && pos_C == queue_back[back_fro].b) continue;
					if (pos_A == pos_B || pos_A == pos_C || pos_B == pos_C) continue;
				}
				else if (beg[1] != 303){
					if (pos_A == queue_back[back_fro].b && pos_B == queue_back[back_fro].a) continue;
					if (pos_A == pos_B) continue;
				}

				if (vis[pos_A][pos_B][pos_C] > 1000) continue;
				if (vis[pos_A][pos_B][pos_C] > 0) return;

				vis[pos_A][pos_B][pos_C] = step_back;
				queue_back[back_rear].a = pos_A;
				queue_back[back_rear].b = pos_B;
				queue_back[back_rear].c = pos_C;
				++back_rear;
			}
			++back_fro;
		}
		back_cnt = back_rear - back_fro;
	}
}

int main(){
	while (scanf("%d%d%d", &w, &h, &n)==3 && n){
		getchar();
		//初始化
		memset(map,  0, sizeof(map));
		memset(vis,  0, sizeof(vis));
		memset(link, 0, sizeof(link));
		memset(conn, 0, sizeof(conn));
		num = step_fro = 0;
		step_back = 1000;

		//对图进行输入并处理，建立可移动区域的图
		for (int i = 0; i < h; ++i)
			gets(map[i]);

		for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
			if (map[i][j] != '#')  link[i][j] = ++num;
		for (int i =0; i < h;++i)
		for (int j = 0; j < w; ++j){
			if (link[i][j]){
				for (int k = 0; k < 4; ++k){
					if (pos_next)
						conn[pos_now][++conn[pos_now][0]] = pos_next;
				}
				conn[pos_now][0] = pos_now;
			}
		}

		beg[0] = beg[1] = beg[2] = end[0] = end[1] = end[2] = 303;
		conn[303][0] = 303;
		for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j){
			if (islower(map[i][j]))
				beg[map[i][j] - 'a'] = pos_now;
			else if (isupper(map[i][j]))
				end[map[i][j] - 'A'] = pos_now;
		}
		bfs();
		printf("%d\n", step_fro + step_back - 1002);
	}
	return 0;
}
