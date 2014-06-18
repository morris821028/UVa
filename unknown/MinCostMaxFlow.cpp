#include<iostream>
#define MAX_A 10000
#define MAX_NODE 1000
#define INF 1000000000
using namespace std;
struct edge
{
	int to,cap,w;
	edge *next,*cdir;
}Am[MAX_A],*em[MAX_NODE],*fm[MAX_NODE];
int np,ap,short_path[MAX_NODE];
bool in_q[MAX_NODE],q[MAX_NODE+1];
bool LC(int Source,int Target)
{
	for(int fh1=0;fh1<=np;fh1++)
	{
		short_path[fh1]=INF;
		in_q[fh1]=false;
	}
	fm[Source]=fm[Target]=NULL;
	short_path[Source]=0;
	int qb=0,qf=0;
	q[qb++]=Source;
	in_q[Source]=true;
	while(qb!=qf)
	{
		int fnt=q[qf];
		qf=(qf+1)%MAX_NODE;
		for(edge* ep=em[fnt];ep!=NULL;ep=ep->next)
			if(ep->cap&&short_path[ep->to]>short_path[fnt]+ep->w)
			{
				short_path[ep->to]=short_path[fnt]+ep->w;
				fm[ep->to]=ep;
				if(!in_q[ep->to])
				{
					in_q[ep->to]=true;
					q[qb]=ep->to;
					qb=(qb+1)%MAX_NODE;
				}
			}
	}
	return fm[Target]!=NULL;
}
void set_pipe(int from,int to,int cap,int w)
{
	edge* ep=&Am[++ap];
	ep->to=to;
	ep->cap=cap;
	ep->w=w;
	ep->next=em[from];
	em[from]=ep;
	ep->cdir=&Am[++ap];
	ep->cdir->to=from;
	ep->cdir->cap=0;
	ep->cdir->w=-w;
	ep->cdir->next=em[to];
	em[to]=ep->cdir;
	ep->cdir->cdir=ep;
}
int new_node()
{
	em[++np]=NULL;
	return np;
}
void ini()
{
	ap=-1;
	np=-1;
}
int MinCostMaxFlow(int Source,int Target)
{
	ini();
	int ans=0,flow=0;
	while(LC(Source,Target))
	{
		int mn=INF;
		for(edge* ep=fm[Target];ep!=NULL;ep=fm[ep->cdir->to])
			mn=min(mn,ep->cap);
		flow+=mn;
		for(edge* ep=fm[Target];ep!=NULL;ep=fm[ep->cdir->to])
		{
			ep->cap-=mn;
			ep->cdir->cap+=mn;
			ans+=mn*ep->w;
		}
	}
	return ans;
}

int main(){
	
}
