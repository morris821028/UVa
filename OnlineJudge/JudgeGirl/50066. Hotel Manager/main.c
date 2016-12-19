#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
	int n;
	assert(scanf("%d", &n)==1);
	RoomStatus list[n];
	for(int i=0; i < n; i++){
		int capacity;
		assert(scanf("%d", &capacity)==1);
		list[i].capacity = capacity;
		list[i].reservation = NULL;
	}
	int nP, sTime, eTime;
	while(scanf("%d %d %d", &nP, &sTime, &eTime)!=EOF)
		printf("%d", ReserveRoom(list, n, nP, sTime, eTime));
	puts("");
	printf("---Room Status List---\n");
	for(int i=0; i<n; i++){
		printf("%d ---", list[i].capacity);
		for(Reservation *tmp = list[i].reservation; tmp!=NULL; tmp=tmp->next)
			printf("->(%d:%d, %d)", tmp->nP, tmp->StartTime, tmp->EndTime);
		puts("");
	}
	printf("---      End       ---\n");
	return 0;
}
