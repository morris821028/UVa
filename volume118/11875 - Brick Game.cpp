#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int t, n, cases = 0;
    cin >> t;
    while(t--) {
        cin >> n;
        int a[30];
        for(int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a+n);
        cases++;
        cout << "Case " << cases << ": "<< a[n/2] << endl;
    }
    return 0;
}
