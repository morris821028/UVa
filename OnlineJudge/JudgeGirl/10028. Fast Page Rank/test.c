#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
const double eps = 1e-10;

#define N 3000+10

double G[N][N];

const double alpha = 0.85;
char buf[N][N];

bool ok(double *q1,double *q2,int n)
{
    double s = 0;
    for(int i = 0; i < n; i++) s += fabs(q1[i]-q2[i]);
    return s < eps;
}
double q0[N];
double q1[N];
double q2[N];

int main()
{
   // freopen("in.txt","r",stdin);
    int n;
    for(int i = 0; i < N; i++) q0[i] = 1;
    while(~scanf("%d",&n)){
        double beta = (1-alpha)/n;
        for(int i = 0; i < n; i++){
            scanf("%s",buf[i]);
        }
        for(int i = 0; i < n; i++){
            int cnt = 0;
            for(int j = 0; j < n; j++)
                if(buf[i][j] == '1') cnt++;
            for(int j = 0; j < n; j++)
                if(buf[i][j] == '1'){
                    G[j][i] = (cnt?alpha/cnt:0)+beta;
                }
                else G[j][i] = beta;
        }
        memcpy(q1,q0,sizeof(double)*n);
        double *qCur = q1, *qNxt = q2;
        do{
        	#pragma omp parallel for schedule(dynamic, 4)
            for(int i = 0; i < n; i++){
                qNxt[i] = 0;
                for(int j = 0; j < n; j++){
                    qNxt[i] += G[i][j]*qCur[j];
                }
            }
            for (int i = 0; i < n; i++) {
            	double t;
            	t = qCur[i], qCur[i] = qNxt[i], qNxt[i] = t;
			}
        }while(!ok(qCur,qNxt,n));
        for(int i = 0,sz = n-1; i < sz; i++)
            printf("%.2lf ",qCur[i]);
        printf("%.2lf\n",qCur[n-1]);
    }
    return 0;
}
