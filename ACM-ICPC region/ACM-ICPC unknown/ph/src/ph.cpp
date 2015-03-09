//============================================================================
// Name        : ph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct pe_t{
	int m,i;
}pe[250000];
struct ov_t{
	double t;
	int a,b;
}ov[1000000];

int cmp_ov(const void*i,const void*j)
{
	ov_t *a=(ov_t*)i,*b=(ov_t*)j;
	if(a->t > b->t)return 1;
	if(a->t < b->t)return -1;
	return 0;
}

int main() {
	freopen("ph.in", "r", stdin);
	int t1,ia,ib,ov_c;
	double ta;
	scanf("%d",&t1);
	while(t1--)
	{
		scanf("%d %d",&ia,&ib);
		ov_c=0;
		for(int i=0;i<ia;i++)
			scanf("%d %d",&pe[i].m,&pe[i].i);
		for(int i=0;i<ia;i++)
			for(int j=0;j<ia;j++)
				if(pe[i].m<pe[j].m && pe[i].i>pe[j].i)
				{
					ta=((double)pe[j].m-pe[i].m)/(pe[i].i-pe[j].i);
					if(ta<=ib)
					{
						ov[ov_c].t=ta;ov[ov_c].a=i+1;ov[ov_c].b=j+1;
						ov_c++;
					}
				}
		qsort(ov,ov_c,sizeof(ov_t),cmp_ov);
		printf("%d\n",ov_c);
		for(int i=0;i<ov_c;i++)
			printf("%d %d\n",ov[i].a,ov[i].b);
	}
	return 0;
}
/*
1
4 1000000
0 2
2 1
3 8
6 3
 */
