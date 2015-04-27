// NLP, n-gram, shingle
#include <stdio.h> 
#include <map>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <string.h>
using namespace std;

int map_product(pair<string, int> l, pair<string, int> r) {
	return l.second * r.second;
}
class Stat {
public:
	int kShingle;
	int sqsum;
	map<string, int> count;
	void init(int k) {
		kShingle = k, sqsum = 0;
		count.clear();
	}
	string toKey(string &s) { // retain for hash function
		return s;
	}
	void add(char s[]) {
		if (s[0] == '\0' || s[1] == '\0')	
			return;
		char end = '\0';
		for (int i = 2; s[i]; i++) {
			swap(s[i+1], end);
			string shingle = s+i-2;
			swap(s[i+1], end);
			count[toKey(shingle)] ++;
		}
	}
	void flush() {
		sqsum = inner_product(count.begin(), count.end(), count.begin(), 0,
           plus<int>(), map_product);
	}
	double distance(Stat &other) {
		double sum = 0;
		for (map<string, int>::iterator it = count.begin(), jt;
			it != count.end(); it++) {
			jt = other.count.find(it->first);
			if (jt != other.count.end()) {
				sum += it->second * jt->second;
			}
		}
		return (double) sum / sqrt((double) sqsum * other.sqsum);
	}
} spam, nonspam, msg;

const int MAXN = 1048576;
char buf[MAXN];
int main() {
	int cases = 0;
	int n, m, q;
	while (scanf("%d %d %d", &n, &m, &q) == 3 && n + m + q) {
		
		while (getchar() != '\n');
		spam.init(3), nonspam.init(3);
		
		for (int i = 0; i < n; i++) {
			while(gets(buf) && strcmp("ENDMESSAGE", buf))
				spam.add(buf);
		}
		for (int i = 0; i < m; i++) {
			while(gets(buf) && strcmp("ENDMESSAGE", buf))
				nonspam.add(buf);
		}
		spam.flush(), nonspam.flush();
			
		printf("Set %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			msg.init(3);
			while(gets(buf) && strcmp("ENDMESSAGE", buf))
				msg.add(buf);
			msg.flush();
			
			double spam_dist = msg.distance(spam);
			double nonspam_dist = msg.distance(nonspam);
			printf("%.5lf %.5lf\n", spam_dist, nonspam_dist);
			puts(spam_dist > nonspam_dist + 1e-10 ? "spam" : "non-spam");
		}
	}
	return 0;
}
/*
2 1 1
AAAA
BBBB CCCC
ENDMESSAGE
BBBB
ENDMESSAGE
AAAABBBB
ENDMESSAGE
AAABB
ENDMESSAGE

2 1 2
AAAA
BBBB CCCC
ENDMESSAGE
BBBB
ENDMESSAGE
AAAABBBB
ENDMESSAGE
AAABB
ENDMESSAGE
AAABB
ENDMESSAGE

0 0 0
*/
