#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int t, n, i;
    cin >> t;
    while(t--) {
        cin >> n;
        string word[n], word2[n], test;
        for(i = 0; i < n; i++)
            cin >> word[i];
        for(i = 0; i < n; i++) {
            word2[i] = word[i];
            sort(word2[i].begin(), word2[i].end());
        }
        while(cin >> test) {
            if(test == "END")
                break;
            cout << "Anagrams for: " << test << endl;
            string test2(test);
            sort(test2.begin(), test2.end());
            int num = 0;
            for(i = 0; i < n; i++) {
                if(test2 == word2[i]) {
                    printf("  %d) ", ++num);
                    cout << word[i] << endl;
                }
            }
            if(!num)
                cout << "No anagrams for: " << test << endl;
        }
        if(t)
            cout << endl;
    }
    return 0;
}
