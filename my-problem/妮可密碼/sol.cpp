#include<iostream>
#include<cstdio>
#include<queue>
#include<cassert>

using namespace std;

#define MAX_ALLOCATE 10000
#define MAX_TOK 26
#define FTOK 'a'

class ACauto
{
public:
	struct trie
	{
		trie *sm[MAX_TOK], *flink;
		int index;
	}Am[MAX_ALLOCATE], *q[MAX_ALLOCATE], *_root, *_ans;
	int ap;
	void init()
	{
		ap = -1;
		_root = new_trie();
		_ans = new_trie();
		for(int i = 0 ; i < MAX_TOK ; i ++)
			_ans->sm[i] = _ans;
		_ans->flink = _ans;
	}

	void add(char *fs, int idx)
	{
		if(fs[0] == '\0')
		{
			_root = _ans;
			//cout<<"SXCK"<<endl;
		}
		else
		{
			trie *loc= _root;
			int fh1;
			for(fh1 = 0 ; fs[fh1+1] ; loc=loc->sm[fs[fh1++]-FTOK])
			{
				if(!('a' <= fs[fh1] && fs[fh1] <= 'z'))
				{
					//cout<<fs<<endl;
				}
				assert('a' <= fs[fh1] && fs[fh1] <= 'z');
				if(loc->sm[fs[fh1]-FTOK] == NULL)
					loc->sm[fs[fh1]-FTOK] = new_trie();
			}
			if(!('a' <= fs[fh1] && fs[fh1] <= 'z'))
			{
				//cout<<fs<<endl;
			}
			assert('a' <= fs[fh1] && fs[fh1] <= 'z');
			loc->sm[fs[fh1]-FTOK] = _ans;
		}
	}

	void build()
		{
			qb=qf=0;
			q[qb++]=_root;
			_root->flink=NULL;
			while(qb!=qf)
			{
				trie* fnt=q[qf++];
				for(int fh1=0;fh1<26;fh1++)
					if(fnt->sm[fh1] != NULL && fnt->sm[fh1] != _ans)
					{
						trie* pre=fnt->flink;
						while(pre != NULL&&pre->sm[fh1] == NULL)pre=pre->flink;
						if(pre)
						{
							fnt->index=pre->index;
							fnt->sm[fh1]->flink = pre->sm[fh1];
						}
						else fnt->sm[fh1]->flink = _root;
						q[qb++]=fnt->sm[fh1];
					}
			}
		}

	trie* go(trie* loc, int c)
	{
		while(loc != NULL && loc->sm[c] == NULL)loc=loc->flink;
		return loc == NULL?_root:loc->sm[c];
	}
	inline trie& get(int idx)
	{
		return Am[idx];
	}

	inline int total()
	{
		return ap;
	}

	inline int no(trie& tr)
	{
		return (&tr - Am);
	}

	inline trie& ans()
	{
		return *_ans;
	}

	inline trie& root()
	{
		return *_root;
	}

private:
	int qb,qf;
	trie* new_trie()
	{
		memset(Am[++ap].sm,0,sizeof(trie*)*(MAX_TOK));
		Am[ap].index=-1;
		Am[ap].flink = NULL;
		return &Am[ap];
	}
}ac;

char s[128], pat[128];

#define MOD 1000000007

int dp[128][10000];
bool done[128][10000];

int mul(int a, int b)
{
	int ret = 0;
	for( ; b != 0 ;b>>=1, (a<<=1)%=MOD)
		if(b&1)
			(ret += a) %= MOD;
	return ret;
}

void update(int fh1, int fh2, int val)
{
	if(!done[fh1][fh2])
	{
		done[fh1][fh2] = 1;
		dp[fh1][fh2] = 0;
	}
	(dp[fh1][fh2] += val) %= MOD;
}

void dump_trie()
{
	for(int i = 0 ; i <= ac.total() ; i ++)
	{
		cout<<"===="<<i<<"====="<<ac.no(*(ac.get(i).flink))<<endl;

		for(int j = 0 ; j < 26 ; j ++)
		{
			if(ac.get(i).sm[j] != NULL)
				cout<<j<<":"<<ac.no(*(ac.get(i).sm[j]))<<' ';
		}
		cout<<endl;
	}
}

int main()
{	
	// rn -- recall_number
	int rn, i;
	int idx = 0;
	while(~scanf("%d%s", &rn, pat))
	{
		//cout<<"idx"<<++idx<<endl;
		ac.init();
		for(int i = 0 ; i < rn ; i ++)
		{
			scanf("%s", s);
			//cout<<s<<endl;
			ac.add(s,-1);
		}
		ac.build();
		memset(done, 0, sizeof(done));
		int len = strlen(pat);
		//printf("%p %p\n", &ac.root(), &ac.ans());
		//printf("%ld\n", &ac.ans() - &ac.root());
		
		//dump_trie();
		update(0,/**ac.no(ac.root())**/0, 1);
		//cout<<len<<endl;
		for(i = 0 ; i < len ; i ++)
		{
			vector<int> h;
			if(pat[i] == '*')
			{
				h = vector<int>(26);
				for(int j = 0 ; j < h.size() ; j ++)
					h[j] = j;
			}
			else
				h = vector<int>(1,pat[i]-'a');
			for(int j = 0 ; j <= ac.total() ; j ++)
				if(done[i][j])
				{
					for(int k = 0 ; k < h.size() ; k ++)
					{
						// h[k]
						// dp[i+1][h[k]]
						int x = ac.no(*(ac.go(&(ac.get(j)), h[k])));
						update(i+1,x, dp[i][j]);
					}
				}
		}
		cout<<(done[len][ac.no(ac.ans())]?dp[len][ac.no(ac.ans())]:0)<<endl;
	}
}
