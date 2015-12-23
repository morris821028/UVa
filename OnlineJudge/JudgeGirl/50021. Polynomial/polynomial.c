#include "polynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIGHESTX 4095
static void normalize(Polynomial *poly) {
	int n = HIGHESTX;
	while (n > 0 && poly->v[n] == 0)
		n--;
	poly->n = n;
}
void init(Polynomial *poly, int coef[], int n) {
	memset(poly->v, 0, sizeof(poly->v));
	memcpy(poly->v, coef, sizeof(int) * n);
	normalize(poly);
}
Polynomial add(Polynomial *poly1, Polynomial *poly2) {
	Polynomial ret = *poly1;
	for (int i = 0; i <= poly2->n; i++)
		ret.v[i] += poly2->v[i];
	normalize(&ret);
	return ret;
}
Polynomial multiply(Polynomial *poly1, Polynomial *poly2) {
	static int tmp[4096];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i <= poly1->n; i++) {
		if (poly1->v[i])
		for (int j = 0; j <= poly2->n; j++)
			tmp[i+j] += poly1->v[i] * poly2->v[j];
	}
	Polynomial ret;
	init(&ret, tmp, poly1->n + poly2->n + 1);
	normalize(&ret);
	return ret;
}
void print(Polynomial *poly) {
	normalize(poly);
//	if (poly->n && abs(poly->v[poly->n]) == 1)
//		printf("%s", poly->v[poly->n] == 1 ? "" : "-");
//	else
		printf("%+d", poly->v[poly->n]);
	if (poly->n)	printf("x");
	if (poly->n > 1)	printf("^%d", poly->n);
	for (int i = poly->n-1; i >= 0; i--) {
		if (poly->v[i] == 0)
			continue;
//		if (i && abs(poly->v[i]) == 1)
//			printf("%c", "-+"[poly->v[i] == 1]);
//		else
			printf("%+d", poly->v[i]);
		if (i)	printf("x");
		if (i > 1)	printf("^%d", i);
	}
	puts("");
}
