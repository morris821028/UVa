#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int>& A, int target) {
    	vector< vector<int> > ret;
    	unordered_map<int, vector< pair<int, int> > > PR;
    	int n = (int) A.size();
    	
        sort(A.begin(), A.end());
        
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < i; j++)
        		PR[A[j] + A[i]].push_back(make_pair(j, i));
        }
        
        for (int i = 0; i < n; i++) {
        	while (i+1 < n && A[i+1] == A[i])
        		i++;
        	for (int j = 0; j < i; j++) {
        		while (j+1 < i && A[j+1] == A[j])
        			j++;
        		int t = target - A[i] - A[j];
        		if (PR.count(t)) {
        			vector< pair<int, int> > &B = PR[t];
        			int f = 0, fB;
        			for (int k = 0; k < B.size(); k++) {
        				if (B[k].second < j) {
        					// (B[k].first, B[k].second, j, i)
        					if (f == 0 || fB != A[B[k].second]) {
        						int sol[] = {A[B[k].first], A[B[k].second], A[j], A[i]};
        						ret.push_back(vector<int>(sol, sol+4));
        						fB = A[B[k].second], f = 1;
        					}
        				} else {
        					break;
        				}
        			}
        		}
        	}
        }
        
        return ret;
    }
};

int main() {
	Solution s;
//	int S[] = {-1, 0, 1, 2, -1, -4};
//	vector<int> A(S, S+6);
	int S[] = {-3,-2,-1,0,0,1,2,3};
	vector<int> A(S, S+8);
	vector< vector<int> > test = s.fourSum(A, 0);
	for (int i = 0; i < test.size(); i++)
		printf("%d %d %d %d\n", test[i][0], test[i][1], test[i][2], test[i][3]);
	return 0;
}
