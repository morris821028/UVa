#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int map[10000062][2]={0};
main()
{
 int x1,x2,x3,x4,x5,x6,x7,x8;
 for(x1=0;x1<10;x1++)
   for(x2=0;x2<10;x2++)
     for(x3=0;x3<10;x3++)
       for(x4=0;x4<10;x4++)
        for(x5=0;x5<10;x5++)
          for(x6=0;x6<10;x6++)
            for(x7=0;x7<10;x7++)
              {
               if(map[x7*2+x6*11+x5*101+x4*1001+x3*10001+x2*100001+x1*1000001][0]==0)
                 map[x7*2+x6*11+x5*101+x4*1001+x3*10001+x2*100001+x1*1000001][0]=x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000;
               if(map[x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000][0]==0&&x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000!=0)
                map[x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000][1]=1+map[x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000-1][1];
               else
                map[x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000][1]=map[x7+x6*10+x5*100+x4*1000+x3*10000+x2*100000+x1*1000000-1][1];
              }
  map[10000000][1]=map[9999999][1];
  int n;
  char x[100],time=0;
  scanf("%d",&n);
  while(getchar() != '\n');
      while(n--)
      {
      gets(x);
      time++;
      int a,b,c,m=strlen(x),num1=0,num2=0;
      for(a=0;a<m;a++)
       if(x[a]<=57&&x[a]>=48)
        num1=num1*10+x[a]-48;
       else
        for(a=a+1;a<m;a++)
         if(x[a]<=57&&x[a]>=48)
          num2=num2*10+x[a]-48;
       if(num2==0) printf("Case %d: %d\n",time,(map[num1][0]==0)?-1:map[num1][0]);
       else
         {
           int ans=map[num2][1]-map[num1-1][1];
       /*    printf("%d %d %d %d\n",map[num2][1],map[num1][1],num2,num1);*/
           //if(map[num1][1]==map[num1-1][1]) ans--;
           printf("Case %d: %d\n",time,ans < 0 ? 0 : ans);
         }
      }
  return 0;
}
/*
10
1 10000000
2 10000000
977786977787
3
101
1 9
20
*/
