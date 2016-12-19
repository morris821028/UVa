#ifndef _RESERVATION_H
#define _RESERVATION_H

typedef struct RoomStatus {
	int capacity;
	struct Reservation *reservation;
} RoomStatus;

typedef struct Reservation {
	int nP;
	int StartTime;
	int EndTime;
	struct Reservation *next;
} Reservation;

int ReserveRoom(RoomStatus list[], int n, int nP, int StartTime, int EndTime);

#endif
