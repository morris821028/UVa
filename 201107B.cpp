#include<stdio.h>

#define inf 999999
#define qbound 999

int n, p, np[202][202], ns[202], cost[202][202]; bool flow[202][202];
int back[202], dist[202], queue[qbound], head, tail; bool inq[202];

bool spfa(void)
{
 int i, j, k;

 for( i=0,head=0,tail=0; i<p; i++ )
 {
  back[i] = -1;
  dist[i] = inf;
  inq[i] = false;
 }
 back[0] = 0;
 dist[0] = 0;
 queue[tail++] = 0;
 inq[0] = true;

 while( head!=tail )
 {
  i = queue[head];
  if( ++head==qbound ) head = 0;
  inq[i] = false;
  for( j=0; j<ns[i]; j++ )
  {
   k = np[i][j];
   if( flow[i][k] && dist[k]>dist[i]+cost[i][k] )
   {
    back[k] = i;
    dist[k] = dist[i]+cost[i][k];
    if( !inq[k] )
    {
     queue[tail] = k;
     if( ++tail==qbound ) tail = 0;
     inq[k] = true;
    }
   }
  }
 }

 return (dist[1]<inf);
}

void addedge(int u, int v, int c)
{
 np[u][ns[u]++] = v;
 np[v][ns[v]++] = u;
 cost[u][v] = c;
 cost[v][u] =-c;
 flow[u][v] = true;
}

int main(void)
{
 int i, j, k, T;
 scanf("%d", &T);
 while( T--)
 {
  scanf("%d", &n);
  if( n==0 ) break;
  p = (n+1)<<1;
  for( i=0; i<p; i++ )
  {
   for( j=0; j<p; j++ )
   {
    cost[i][j] = 0;
    flow[i][j] = false;
   }
   ns[i] = 0;
  }
  for( i=1; i<=n; i++ )
  {
   addedge(0, i+1, 0);
   addedge(i+n+1, 1, 0);
  }
  for( j=1; j<=n; j++ )
  {
   for( i=1; i<=n; i++ )
   {
    scanf("%d", &k);
    addedge(i+1, j+n+1, (k>0 ? -k : 0));
   }
  }
  j = 0;
  while( spfa() )
  {
   i = 1;
   while( i )
   {
    j += cost[back[i]][i];
    flow[back[i]][i] = false;
    flow[i][back[i]] = true;
    i = back[i];
   }
  }
  printf("%d\n", -j);
 }
 return 0;
}
/*
3
5
4 1 6 2 3
5 0 3 7 6
2 3 4 5 8
3 4 6 3 4
4 6 5 8 6
5
3 8 9 15 10
4 10 7 16 14
9 13 11 19 10
8 13 12 20 13
1 7 5 11 9
4
10 8 6 3
6 10 7 8
4 12 10 1
2 9 5 10
*/
