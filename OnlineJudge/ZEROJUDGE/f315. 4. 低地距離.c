#include <stdio.h>
#include <memory.h>

#define GET(x) (cnt[x>>5]>>(x&31)&1)
#define SET(x) (cnt[x>>5] |= 1<<(x&31))
#define REV(x) (cnt[x>>5] ^= 1<<(x&31))

static long long ret = 0;
static int cnt[2048];
void divide2(unsigned short a[], unsigned short b[], int n) {
	if (n <= 1) return 0;
	int mid = n/2;
	int l = 0, r = mid*2;

	int sum = 0;
	for (int i = 0; i < 2*n; i++) {
		if (a[i] <= mid) {
			sum++;
			b[l++] = a[i];
		} else {
			b[r++] = a[i] - mid;
			if (GET(a[i]-mid) == 0) {
				ret -= sum;
				SET(a[i]-mid);
			} else {
				ret += sum;
				REV(a[i]-mid);
			}
		}
	}
	divide2(b, a, l/2);
	divide2(b+mid*2, a, r/2-mid);
}

int main() {
	int n, x;
	static unsigned short b[200005];
	scanf("%d", &n);
	
	int mid = n/2;
	int l = 0, r = mid*2;

	int sum = 0;
	for (int i = 0; i < 2*n; i++) {
		scanf("%d", &x);
		if (x <= mid) {
			sum++;
			b[l++] = x;
		} else {
			b[r++] = x - mid;
			if (GET(x-mid) == 0) {
				ret -= sum;
				SET(x-mid);
			} else {
				ret += sum;
				REV(x-mid);
			}
		}
	}
	static unsigned short a[100005];
	divide2(b, a, l/2);
	divide2(b+mid*2, a, r/2-mid);
	printf("%lld\n", ret);
	return 0;
}
