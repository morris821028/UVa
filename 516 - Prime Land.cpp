   #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    main()
    {
     int sum,temp1,temp2;
     char x[32767];
     int a,b,c,flag,time1;
     while(gets(x)!=0)
      {
       if(x[0]==48&&strlen(x)==1) break;
       int ansmath[2000]={0},anstemp[2000]={0};
       sum=1;temp1=0;flag=0;time1=-1;
       for(a=0;a<strlen(x);a++)
        {
         if(x[a]>=48&&x[a]<=57)
          {temp1=temp1*10+x[a]-48;}
         else
          {
           if(flag==0)
           {temp2=temp1;flag=1;}
           else
           {
            c=temp2;
            for(b=1;b<temp1;b++)
             {
             temp2=temp2*c;
             }
            sum=sum*temp2;
            flag=0;
           }
           temp1=0;
          }
         }
        c=temp2;
        for(b=1;b<temp1;b++)
             temp2=temp2*c;
            sum=sum*temp2;
         sum=sum-1;
        for(a=2;a<=sum;a++)
         {
          int time=0;
         if(sum%a==0)
         {
          if(sum%a==0)
           time1++;
          while(sum%a==0)
           {

            sum=sum/a;
            time++;
           }
          ansmath[time1]=a;
          anstemp[time1]=time;
          }
         }
        for(a=time1;a>=0;a--)
         {
          printf("%d %d",ansmath[a],anstemp[a]);
          if(a != 0)
            printf(" ");
         }
        printf("\n");
      }
     return 0;
    }
