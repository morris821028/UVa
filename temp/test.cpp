#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
const int MAX = 1100000;
const long long MAXA = 1000000;
int prime[MAX], nprime = 0;
int cnt = 0, maxDeep;
int rank[MAX];
bool vised[MAX];

void dfs(long long p, int x, int d)
{
if(d == maxDeep)
{
   if(p <= MAXA) rank[cnt++] = p;
   return ;
}
while(x < nprime)
{
   if(p * prime[x] > MAXA) return ;
   dfs(p * prime[x], x, d + 1);
   x++;
}
}

void init()
{
memset(vised, true, sizeof(vised));
for(int i = 2; i < MAX; i++)
{
   if(vised[i])
    for(int j = i << 1; j < MAX; j += i)
     vised[j] = false;
}
for(int i = 2; i < MAX; i++)
   if(vised[i]) prime[nprime++] = i;
for(maxDeep = 1; maxDeep < 20; maxDeep++)
   dfs(1, 0, 0);
}

void decompose(int a)
{
int i = 0;
while(a != 1)
{
   while(a % prime[i] == 0)
   {
    printf("%d", prime[i]);
    a /= prime[i];
    if(a != 1) putchar(' ');
    else putchar('\n');
   }
   i++;
}
}

int main()
{
init();
int t;

scanf("%d", &t);
for(int nc = 1; nc <= t; nc++)
{
   int k, i;
   int a, b;
   scanf("%d%d%d", &a, &b, &k);
   if(k > (b - a) / 2)
   {
    for(i = MAX - 1, k = b - a - k + 2; k; i--) if(rank[i] >= a && rank[i] <= b) k--;
    ++i;
   }
   else
   {
    for(i = 0; k; i++) if(rank[i] >= a && rank[i] <= b) k--;
    --i;
   }
   printf("Case %d: ", nc);
   decompose(rank[i]);
}
return 0;
}
