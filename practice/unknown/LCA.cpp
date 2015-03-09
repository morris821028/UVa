/**********************************************************************************/
/*  Problem: d767 "¦å½tÃö«Y" from RMQ & LCA                                   */
/*  Language: CPP (2406 Bytes)                                                    */
/*  Result: AC judge by zeroserver@ZeroJudge                                      */
/*  Author: morris1028 at 2010-08-18 21:15:42                                     */
/**********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
int Link[30001][6],Lt[30001]={0},First[30001]={0};
int Visit[60002],Depth[60002],T;
int tree[140003][2];
void DFS(int P,int D)
{
   if(!First[P]) First[P]=T;
   Visit[T]=P,Depth[T++]=D;
   int a;
   for(a=0;a<Lt[P];a++)
      DFS(Link[P][a],D+1),Visit[T]=P,Depth[T++]=D;
}
int Min(int x,int y)
{
   if(x>y) return y;
   return x;
}
void Set_tree(int l,int r,int k)
{
   if(l==r) tree[k][0]=Depth[l],tree[k][1]=l;
   else
      {
         int m=(l+r)/2;
         Set_tree(l,m,2*k);
         Set_tree(m+1,r,2*k+1);
         if(tree[2*k][0]<tree[2*k+1][0])     tree[k][0]=tree[2*k][0],tree[k][1]=tree[2*k][1];
         else                            tree[k][0]=tree[2*k+1][0],tree[k][1]=tree[2*k+1][1];
      }
}
int get (int l,int r,int k,int x,int y,int &L)
{
     if(l==x&&r==y)  {L=tree[k][1];return tree[k][0];}
     else
        {
          int m=(l+r)/2,LCA1,LCA2,V1,V2;
          if(m>=y)     {V1=get(l,m,2*k,x,y,LCA1),L=LCA1;    return V1;}
          else if(m<x) {V2=get(m+1,r,2*k+1,x,y,LCA2),L=LCA2;return V2;}
          else
               {
                  V1=get(l,m,2*k,x,m,LCA1);
                  V2=get(m+1,r,2*k+1,m+1,y,LCA2);
                  if(V1<V2) {L=LCA1;return V1;}
                  else      {L=LCA2;return V2;}
               }
        }
}
void Clear(int N)
{
     int a;
     for(a=1,T=1;a<=N;Lt[a]=0,First[a]=0,a++) ;
}
int Input()
{
  char cha;
  int x=0;
  while(cha=getchar())    if(cha!=' '&&cha!='\n') break;
  x=cha-48;
  while(cha=getchar())
    {
      if(cha==' '||cha=='\n') break;
      x=x*10+cha-48;
    }
    return x;
}
main()
{
   int N,Q,P,X,Y,a,t,L,A,B;
   scanf("%d %d",&N,&Q);
       {
          Clear(N);
          for(a=1;a<=N;a++)
            {
             while(1)
                {
                  P=Input();
                  if(P==0) break;
                  Link[a][Lt[a]++]=P;
                }
             }
          DFS(1,0);
          Set_tree(1,T-1,1);
          while(Q--)
               {
                 X=Input(),Y=Input();
                 A=First[X],B=First[Y];
                 if(A>B) t=A,A=B,B=t;
                 get(1,T-1,1,A,B,L);
                 printf("%d %d\n",Visit[L],Depth[First[X]]+Depth[First[Y]]-2*Depth[L]);
               }
       }
   return 0;
}
