#include<iostream>
int T,n,t[10000000],i,l,top=0,r;
bool q=0;
main()
{
	freopen("in1.txt", "rt", stdin);   
	freopen("out2.txt", "w+t", stdout);
    clock_t st, ed;
    st = clock();
	while(scanf("%d", &t[top]) == 1) top++;
	/*for(i=0;i<l;i++)
	{
		if(a[i]>='0'&&a[i]<='9')
		r=r*10+a[i]-'0',q=1;
		else if(q)t[top++]=r,r=0,q=0;
	}
	if(q)t[top++]=r;*/
	std::sort(t,t+top);
	/*for(i=0;i<top;i++)printf("%d ",t[i]);*/
	ed = clock();
	printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
}
