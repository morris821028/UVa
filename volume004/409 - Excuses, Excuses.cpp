#include<stdio.h>
#include<stdlib.h>
#include<string.h>
main()
{
 int K,E,time=0;
 while(scanf("%d %d",&K,&E)==2)
   {
     int a,b,c,d,flag[30]={0};
     char num[30][30]={0},excuse[30][100]={0},x[100];
     for(a=0;a<K;a++)
      {
        scanf("%s",x);
        int n=strlen(x);
        num[a][0]=n;
        for(b=1;b<=n;b++) {num[a][b]=x[b-1];}
      }
     getchar();
     for(a=0;a<E;a++)
      {
       gets(x);
       int n=strlen(x),anstemp=0;
       excuse[a][0]=n;
        for(b=1;b<=n;b++) excuse[a][b]=x[b-1];
        for(b=0;b<n;b++) /*進行比對*/
          {
           int temp[100]={0};
            for(c=1;b<n;b++,c++) /*進行切割*/
             {
              if(x[b]<65||(x[b]>=91&&x[b]<=96)||x[b]>=123) break;
              temp[c]=x[b];
             }
            for(c=0;c<K;c++) /*拿單字出來比對*/
             {
              for(d=1;d<30;d++)
               if(temp[d]!=num[c][d]&&temp[d]!=num[c][d]-32) break;
               if(d==30) {anstemp++;break;}
             }
          }
        flag[a]=anstemp;
      }
     printf("Excuse Set #%d\n",++time);
     int max=-1;
     for(a=0;a<E;a++)
      if(flag[a]>max) max=flag[a];
     for(a=0;a<E;a++)
      if(flag[a]==max)
       {
        for(b=0;b<excuse[a][0];b++)
         printf("%c",excuse[a][b+1]);
         printf("\n");
       }
       puts("");
   }
 return 0;
}
