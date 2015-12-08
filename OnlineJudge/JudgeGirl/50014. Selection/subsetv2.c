#include "subset.h"
#include <stdlib.h>

#define TEST1 A[i1]
#define TEST2 TEST1 + A[i2]
#define TEST3 TEST2 + A[i3]
#define TEST4 TEST3 + A[i4]
#define TEST5 TEST4 + A[i5]
#define TEST6 TEST5 + A[i6]
#define TEST7 TEST6 + A[i7]
#define TEST8 TEST7 + A[i8]
#define TEST9 TEST8 + A[i9]
#define TEST10 TEST9 + A[i10]
#define TEST11 TEST10 + A[i11]
#define TEST12 TEST11 + A[i12]
#define TEST13 TEST12 + A[i13]
#define TEST14 TEST13 + A[i14]
#define TEST15 TEST14 + A[i15]
#define TEST16 TEST15 + A[i16]
#define TEST17 TEST16 + A[i17]
#define TEST18 TEST17 + A[i18]
#define TEST19 TEST18 + A[i19]
#define TEST20 TEST19 + A[i20]
#define TEST21 TEST20 + A[i21]
#define TEST22 TEST21 + A[i22]
#define TEST23 TEST22 + A[i23]
#define TEST24 TEST23 + A[i24]
#define TEST25 TEST24 + A[i25]
#define TEST26 TEST25 + A[i26]
#define TEST27 TEST26 + A[i27]
#define TEST28 TEST27 + A[i28]
#define TEST29 TEST28 + A[i29]
#define TEST30 TEST29 + A[i30]

#define mfor(x, y) for (int i##x = i##y + 1; i##x < n; i##x ++) if (TEST##x <= K)
#define RECLOOP1 for (int i1 = 0; i1 < n; i1++)
#define RECLOOP2 RECLOOP1 mfor(2, 1)
#define RECLOOP3 RECLOOP2 mfor(3, 2)
#define RECLOOP4 RECLOOP3 mfor(4, 3)
#define RECLOOP5 RECLOOP4 mfor(5, 4)
#define RECLOOP6 RECLOOP5 mfor(6, 5)
#define RECLOOP7 RECLOOP6 mfor(7, 6)
#define RECLOOP8 RECLOOP7 mfor(8, 7)
#define RECLOOP9 RECLOOP8 mfor(9, 8)
#define RECLOOP10 RECLOOP9 mfor(10, 9)
#define RECLOOP11 RECLOOP10 mfor(11, 10)
#define RECLOOP12 RECLOOP11 mfor(12, 11)
#define RECLOOP13 RECLOOP12 mfor(13, 12)
#define RECLOOP14 RECLOOP13 mfor(14, 13)
#define RECLOOP15 RECLOOP14 mfor(15, 14)
#define RECLOOP16 RECLOOP15 mfor(16, 15)
#define RECLOOP17 RECLOOP16 mfor(17, 16)
#define RECLOOP18 RECLOOP17 mfor(18, 17)
#define RECLOOP19 RECLOOP18 mfor(19, 18)
#define RECLOOP20 RECLOOP19 mfor(20, 19)
#define RECLOOP21 RECLOOP20 mfor(21, 20)
#define RECLOOP22 RECLOOP21 mfor(22, 21)
#define RECLOOP23 RECLOOP22 mfor(23, 22)
#define RECLOOP24 RECLOOP23 mfor(24, 23)
#define RECLOOP25 RECLOOP24 mfor(25, 24)
#define RECLOOP26 RECLOOP25 mfor(26, 25)
#define RECLOOP27 RECLOOP26 mfor(27, 26)
#define RECLOOP28 RECLOOP27 mfor(28, 27)
#define RECLOOP29 RECLOOP28 mfor(29, 28)
#define RECLOOP30 RECLOOP29 mfor(30, 29)

#define SUBSET(s)	\
	if (S == s) { \
		RECLOOP##s \
			if (TEST##s == K) \
				return 1; \
	}
static int cmp(const void *a, const void *b) {
	return *(int *) b - *(int *) a;
}
int subset(int A[], int n, int K, int S) {
	SUBSET(1); SUBSET(2);
	SUBSET(3); SUBSET(4);
	SUBSET(5); SUBSET(6);
	SUBSET(7); SUBSET(8);
	SUBSET(9); SUBSET(10);
	SUBSET(11); SUBSET(12);
	SUBSET(13); SUBSET(14);
	SUBSET(15); SUBSET(16);
	SUBSET(17); SUBSET(18);
	SUBSET(19); SUBSET(20);
	SUBSET(21); SUBSET(22);
	SUBSET(23); SUBSET(24);
	SUBSET(25); SUBSET(26);
	SUBSET(27); SUBSET(28);
	SUBSET(29); SUBSET(30);
	return 0;
}
