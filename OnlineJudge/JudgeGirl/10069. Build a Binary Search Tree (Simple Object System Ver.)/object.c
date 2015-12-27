#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self, Object proto) {
    Object *obj = self;
	if (proto.destroy != NULL)
		proto.destroy(self);
    if (obj)
        free(obj);
}
int Object_init(void *self) {
    return 1;
}
void *Object_new(int size, Object proto) {
    if (!proto.init) 
		proto.init = Object_init;
    if (!proto.destroy) 
		proto.destroy = Object_destroy;

    Object *el = calloc(1, size);
    *el = proto;

    if(!el->init(el)) {
        el->destroy(el);
        return NULL;
    } else {
        return el;
    }
}
