#include <cstdio>
using namespace std;
class EllysXors {
    public:
        long long getXor(long long l, long long r) {
            long long ans = 0, i;
            for(i = 1; i < 40; i++) {
                long long s1 = 0, s2 = 0;
                long long tl = l, tr = r;
                if((l>>i)&1) {
                    tl = ((l>>i)<<i)|((1<<i)-1);
                    if(tl > r)
                        s1 = r-l+1;
                    else
                        s1 = tl-l+1;
                }
                if((r>>i)&1){
                    tr = (r>>i)<<i;
                    if(tr > l)
                        s2 = r-tr+1;

                }
                if((s1+s2)&1)
                    ans |= (long long)1<<i;
            }
            if(l%2 == 0)    l++;
            if(r%2 == 0)    r--;
            if((r-l)/2%2 == 0) ans |= 1;

            return ans;
        }
};
