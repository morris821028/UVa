#include "doll.h"

#include <stdlib.h>
#include <string.h>

Doll *newDoll(char top, char bottom) {
	Doll *d = (Doll*) malloc(sizeof(Doll));
	d->top = top, d->bottom = bottom, d->interior = NULL;
	return d;
}
void package(Doll *outer, Doll *inter) {
	outer->interior = inter;
}
static void rprint(char *buf, int *idx, Doll *d) {
	if (d == NULL)
		return ;
	buf[*idx] = d->top, (*idx)++;
	rprint(buf, idx, d->interior);
	buf[*idx] = d->bottom, (*idx)++;
}
const char* doll_c_str(Doll *doll) {
	static char *buf = NULL;
	static int bufsz = 0;
	
	int cnt = 0, idx = 0;
	Doll *d = doll;
	while (d != NULL)
		d = d->interior, cnt++;
	if (bufsz < cnt*2) {
		free(buf);
		buf = (char *) malloc(sizeof(char) * (cnt*2+1));
		bufsz = cnt*2+1;
	}
	rprint(buf, &idx, doll);
	buf[idx] = '\0';
	return buf;
}
