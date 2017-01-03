#include "elevator.h"
#include <stdlib.h>
#include <string.h>

struct Elevator {
	int u, d, F;
	int now, err[2];
	int visited[MAXF+5];
};
static int validLv(Elevator *e, int lv) {
	return lv >= 1 && lv <= e->F;
}
Elevator* newElevator(int u, int d, int F) {
	Elevator *ret = (Elevator *) calloc(1, sizeof(Elevator));
	ret->u = u, ret->d = d, ret->F = F;
	ret->now = 1, ret->visited[1] = 1;
	return ret;
}
int up(Elevator* e) {
	e->err[1] = 0;
	if (!validLv(e, e->now + e->u)) {
		e->err[0]++;
		if (e->err[0] > 3 || e->err[1] > 3)
			return -1;
		return 0; 
	}
	e->now += e->u, e->err[0] = 0;
	e->visited[e->now] = 1;
	return 1;
}
int down(Elevator* e) {
	e->err[0] = 0;
	if (!validLv(e, e->now - e->d)) {
		e->err[1]++;
		if (e->err[0] > 3 || e->err[1] > 3)
			return -1;
		return 0; 
	}
	e->now -= e->d, e->err[1] = 0;
	e->visited[e->now] = 1;
	return 1;

}
int visited(Elevator* e, int lv) {
	if (!validLv(e, lv))
		return 0;
	return e->visited[lv];
}
int getPosition(Elevator* e) {
	return e->now;
}
