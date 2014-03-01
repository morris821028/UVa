#include<stdlib.h>
#include<stdio.h>
main()
{
 int l1,l2,m2,m1,r1,r2,n,m;
 while(scanf("%d %d",&n,&m)==2&&n!=0)
  {
      if(n == 1 && m == 1)
        break;
   int t1,t2;
   l1=0;l2=1;
   m1=1;m2=1;
   r1=1;r2=0;
   while(m1!=n||m2!=m)
    {
     if(m1*m>m2*n)/*走左邊*/
      {
       t1=m1;t2=m2;
       m1+=l1;
       m2+=l2;
       r1=t1;r2=t2;
       printf("L");
      }
     else /*走右邊*/
      {
       t1=m1;t2=m2;
       m1+=r1;
       m2+=r2;
       l1=t1;l2=t2;
       printf("R");
      }
    }
    printf("\n");
  }
 return 0;
}
