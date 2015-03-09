#include<stdlib.h>
#include<stdio.h>
int A[501][501], Tree[524289];
int Max (int x, int y)
{
    if(x>=y)    return x;
    else        return y;
}
int xxxx = 0;
void Set (int x1, int y1, int x2, int y2, int k)
{
    if(k > xxxx)    xxxx = k;
    if(x1>x2 || y1>y2)  return;
    if(x1==x2 && y1==y2)    Tree[k]=A[x1][y1];
    else
        {
            int mx=(x1+x2)/2, my=(y1+y2)/2;
            Set (x1  ,  y1, mx, my, (k<<2)-2);
            Set (mx+1,  y1, x2, my, (k<<2)-1);
            Set (x1  ,my+1, mx, y2, (k<<2));
            Set (mx+1,my+1, x2, y2, (k<<2)+1);
            Tree[k]=Max(Tree[(k<<2)-2], Max(Tree[(k<<2)-1], Max(Tree[(k<<2)], Tree[(k<<2)+1])));
        }
}
int sx, sy, ex, ey;
int Get(int x1, int y1, int x2, int y2, int k)
{
    if(x1>=sx && y1>=sy && x2<=ex && y2<=ey)    return Tree[k];
    else
        {
            int mx=(x1+x2)/2, my=(y1+y2)/2, r=0;
            if(ex>mx)
                {
                    if(ey>my) /*第四*/
                        {
                            r=Max(r, Get(mx+1, my+1, x2, y2, (k<<2)+1));
                            if(r==Tree[k])  return r;
                        }
                    if(sy<=my)/*第二*/
                        {
                            r=Max(r, Get(mx+1, y1, x2, my, (k<<2)-1));
                            if(r==Tree[k])  return r;
                        }
                }
            if(sx<=mx)
                {
                    if(ey>my) /*第三*/
                        {
                            r=Max(r, Get(x1, my+1, mx, y2, (k<<2)));
                            if(r==Tree[k])  return r;
                        }
                    if(sy<=my)/*第一*/
                        {
                            r=Max(r, Get(x1, y1, mx, my, (k<<2)-2));
                            if(r==Tree[k])  return r;
                        }
                }
            return r;
        }
}
int Input()
{
    char cha;
    int x=0;
    while(cha=getchar())
        if(cha!=' '&&cha!='\n') break;
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
    int a, b, N, M, Q, T;
    while(scanf("%d %d",&N,&M)==2)
        {
            for(a=1;a<=N;a++)
                for(b=1;b<=M;b++)
                    A[a][b]=Input();
            Set (1, 1, N, M, 1);
            scanf("%d",&Q);
            while(Q--)
                {
                    sx=Input(), sy=Input(), ex=Input(), ey=Input();
                    printf("%d\n",Get(1 , 1, N, M, 1));
                }
      }
    printf("%d\n", xxxx);
  return 0;
}
