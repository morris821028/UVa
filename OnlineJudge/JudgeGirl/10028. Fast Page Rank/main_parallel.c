#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAXV 4096
#define MAXE 1048576
#define MAXIT 9999
const double eps = 1e-10;
typedef struct Edge {
    int v;
    struct Edge *next;
} Edge;
Edge edge[MAXE], *adj[MAXV];
int e = 0;
void Addedge(int x, int y){
    edge[e].v = y, edge[e].next = adj[x], adj[x] = &edge[e++];
}
double r[MAXV], beta;
int N, outdeg[MAXV];
void init(int n, double tbeta) {
    N = n, beta = tbeta;
    e = 0;
    for (int i = 0; i < n; i++)
    	adj[i] = NULL, outdeg[i] = 0;
}
bool isComplete(double a[], double b[]) {
    double e = 0;
    for (int i = N - 1; i >= 0; i--)
        e += (a[i] - b[i]) * (a[i] - b[i]);
    return e < eps;
}
void compute() {
	static double next_r[MAXV];
    for (int i = 0; i < N; i++)
    	r[i] = 1, next_r[i] = 0;
    
    for (int it = 0; it < MAXIT; it++) {
        for (int i = 0; i < N; i++) {
            double tmp = 0;
            for (Edge *p = adj[i]; p; p = p->next)
                tmp += r[p->v] / outdeg[p->v];
            next_r[i] = tmp * beta + (1.0 - beta);
        }
        if (isComplete(r, next_r)) {
        	memcpy(r, next_r, sizeof(double)*N);
            return ;
        }
        memcpy(r, next_r, sizeof(double)*N);
    }
}

int main() {
    int N;
    char s[MAXV];
    while (scanf("%d", &N) == 1) {
    	init(N, 0.85f);
        for (int i = 0; i < N; i++) {
            scanf("%s", s);
            for (int j = 0; j < N; j++) {
                if (s[j] == '1')
                    Addedge(j, i), outdeg[i]++;
            }
        }
        compute();        
        for (int i = 0; i < N; i++)
            printf("%.2lf%c", r[i], " \n"[i == N-1]);
    }
    return 0;
}
