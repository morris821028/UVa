#include <iostream>
#include <sstream>
using namespace std;
long long Pow(long long x, long long y) {
    if(y == 0)
        return 1;
    if(y&1)
        return x*Pow(x*x, y/2);
    else
        return Pow(x*x, y/2);
}
long long a[1000000];
int main() {
    long long x;
    while(cin >> x) {
        string line;
        getline(cin, line);
        getline(cin, line);
        stringstream sin;
        sin << line;
        long long n = 0;
        while(sin >> a[n])
            n++;
        long long ans = 0;
        for(int i = 0; i < n-1; i++) {
            ans += Pow(x, n-i-2)*a[i]*(n-i-1);
        }
        cout << ans << endl;
    }
    return 0;
}
