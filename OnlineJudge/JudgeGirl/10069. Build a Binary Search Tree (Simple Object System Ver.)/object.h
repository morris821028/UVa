#ifndef _object_h
#define _object_h

typedef struct {
    int (*init)(void *self);
    void (*destroy)(void *self);
} Object;

int Object_init(void *self);
void Object_destroy(void *self, Object proto);
void *Object_new(int size, Object proto);

#define NEW(T) Object_new(sizeof(T), T##Proto)
#define FREE(T, t) Object_destroy(t, T##Proto)

#endif
