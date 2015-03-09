//============================================================================
// Name        : pd.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
/*
typedef struct {
	int st, ed;
}Work;
Work JOB[10000];
int main() {
	int  T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &JOB[i].st, &JOB[i].ed);
	}
	qsort(JOB, n, )
	return 0;
}
*/
struct job_t{
	int s,f;
}job[100000];

char use[100000];

int cmp_job(const void*ta,const void*tb)
{
	job_t *a=(job_t*)ta,*b=(job_t*)tb;
	if(a->f != b->f)return a->f - b->f;
	return a->s - b->s;
}
int main()
{
	ifstream fin("pd.in");
	int t1;
	fin>>t1;
	while(t1--)
	{
		int ia;
		fin>>ia;
		for(int i=0;i<ia;i++)
		{
			fin>>job[i].s>>job[i].f;
			if(job[i].s>job[i].f)swap(job[i].s,job[i].f);
		}
		for(int i=0;i<ia;i++)use[i]=0;
		qsort(job,ia,sizeof(job_t),cmp_job);
		//for(int i=0;i<ia;i++)cout<<job[i].s<<' '<<job[i].f<<endl;
		//cout<<"==="<<endl;
		int rest=ia,regcnt=0;
		while(rest>0)
		{
			int regend=-2147483647;
			regcnt++;
			for(int i=0;i<ia && regend<=10000;i++)
				if( !use[i] && regend<job[i].s)
				{
					//cout<<regend<<' ';
					regend = job[i].f;
					use[i]=1;
					rest--;
				}
			//cout<<endl;
		}
		cout<<regcnt<<endl;
	}
	return 0;
}
/*
2
4
10 30
5 35
37 50
30 40
*/
