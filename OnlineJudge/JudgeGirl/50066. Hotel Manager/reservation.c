#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>

static Reservation mem[32767];
static int mIdx = 0;
static inline int place(RoomStatus *u, int req, int stTime, int edTime) {
	Reservation *p = u->reservation, *q = NULL, *r;
	for (; p != NULL; q = p, p = p->next) {
		if (p->StartTime >= edTime)
			break;
		if (p->EndTime > stTime)
			return 0;
	}
//	Reservation *ret = (Reservation *) malloc(sizeof(Reservation));
	Reservation *ret = &mem[mIdx++];
	ret->nP = req, ret->StartTime = stTime, ret->EndTime = edTime;
	if (q == NULL)
		u->reservation = ret;
	else
		q->next = ret;
	ret->next = p;	
	return 1;
}
int ReserveRoom(RoomStatus A[], int n, int req, int stTime, int edTime) {
	for (int i = 0; i < n; i++) {
		if (A[i].capacity < req)
			continue;
		if (place(&A[i], req, stTime, edTime))
			return 1;
	}
	return 0;
}
