#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
int main()
{
    int len;
    double a,left,right;
    char s[20];
    while(scanf("%s",s)!=EOF)
    {
        len=strlen(s)+1;
        a=atof(s);
        while(1)
        {
            left=log(a)/log(2)+len*log(10)/log(2);
            right=log(a+1)/log(2)+len*log(10)/log(2);
            if((int)left<(int)right)
            break;
            len++;
        }
        int ans=ceil(left);
        printf("%d\n",ans);
    }
    return 0;
}
