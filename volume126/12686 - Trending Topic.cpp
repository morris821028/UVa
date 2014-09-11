#include <stdio.h> 
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
bool cmp(pair<int, string> a, pair<int, string> b) {
	if(a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}
int main() {
	char s[1024];
	int day = 0, N;
	map<string, int> R[7], Top;
	while(scanf("%s", s) == 1) {
		if (!strcmp(s, "<text>")) {
			day = (day + 1)%7;
			for (map<string, int>::iterator it = R[day].begin();
				it != R[day].end(); it++)
				Top[it->first] -= it->second;
			R[day].clear();
			while(scanf("%s", s) == 1) {
				if(!strcmp(s, "</text>"))
					break;
				if(strlen(s) < 4)
					continue;
				R[day][s]++, Top[s]++;
			}
		} else if (!strcmp(s, "<top")) {
			scanf("%d %*s", &N);
			vector< pair<int, string> > A;
			for (map<string, int>::iterator it = Top.begin();
				it != Top.end(); it++)
				if (it->second > 0)
					A.push_back(make_pair(it->second, it->first));
			sort(A.begin(), A.end(), cmp);
			int M = 0;
			printf("<top %d>\n", N);
			for (int i = 0; i < A.size(); i++) {
				printf("%s %d\n", A[i].second.c_str(), A[i].first);	
				M++;	
				if (i+1 < A.size() && A[i].first > A[i+1].first) {
					if (M >= N)
						break;
				}				
			}
			printf("</top>\n");
		}
	}
	return 0;
}
/*
<text>
imagine you are in the hiring process of a company whose
main business is analyzing the information that appears
in the web
</text>
<text>
a simple test consists in writing a program for
maintaining up to date a set of trending topics
</text>
<text>
you will be hired depending on the efficiency of your solution
</text>
<top 5 />
<text>
they provide you with a file containing the text
corresponding to a highly active blog
</text>
<text>
the text is organized daily and you have to provide the
sorted list of the n most frequent words during last week
when asked
</text>
<text>
each input file contains one test case the text corresponding
to a day is delimited by tag text
</text>
<text>
the query of top n words can appear between texts corresponding
to two different days
</text>
<top 3 />
<text>
blah blah blah blah blah blah blah blah blah
please please please
</text>
<top 3 />
*/
