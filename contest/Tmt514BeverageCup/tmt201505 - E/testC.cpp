//program C

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>
#include<queue>
#include<bitset>
#include<ctime>

using namespace std;

struct point
{
  long long x,y;
  int num;
};

int get()
{
  char c;
  while(c=getchar(),(c<'0'||c>'9')&&(c!='-'));
  bool flag=(c=='-');
  if(flag)
    c=getchar();
  int x=0;
  while(c>='0'&&c<='9')
    {
      x=x*10+c-48;
      c=getchar();
    }
  return flag?-x:x;
}

void output(int x)
{
  if(x<0)
    {
      putchar('-');
      x=-x;
    }
  int len=0,data[10];
  while(x)
    {
      data[len++]=x%10;
      x/=10;
    }
  if(!len)
    data[len++]=0;
  while(len--)
    putchar(data[len]+48);
  putchar('\n');
}

point p[6000],q[6000];

long long operator *(point a,point b)
{
  return a.x*b.y-a.y*b.x;
}

int zone(point a)
{
  if(a.x>0&&a.y>=0)
    return 0;
  if(a.y>0&&a.x<=0)
    return 1;
  if(a.x<0&&a.y<=0)
    return 2;
  return 3;
}

bool operator <(point a,point b)
{
  int p=zone(a),q=zone(b);
  if(p!=q)
    return p<q;
  return a*b>0;
}

int main()
{
  int totaltest=get();
  for(int test=1;test<=totaltest;test++)
    {
      int n=get();
      for(int i=0;i<n;i++)
        {
          p[i].x=get();
          p[i].y=get();
          p[i].num=i;
        }
      printf("Case #%d:\n",test);
      for(int i=0;i<n;i++)
        {
          for(int j=1;j<n;j++)
            if(p[j].num==i)
              swap(p[j],p[0]);
          int m=n-1;
          for(int j=0;j<m;j++)
            {
              q[j].x=p[j+1].x-p[0].x;
              q[j].y=p[j+1].y-p[0].y;
            }
          sort(q,q+m);
          for(int j=0;j<m;j++)
            q[m+j]=q[j];
          int ans=n;
          for(int l=0,r=0;l<m;l++)
            {
              while(r<l+m&&q[l]*q[r]>=0)
                r++;
              ans=min(ans,m-(r-l));
            }
          if(n<=2)
            ans=0;
          output(ans);
        }
    }
  return 0;
}
