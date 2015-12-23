#include "locker.h"

#define UNLOCK 0
#define LOCKED 1
#define OPERROR -1
#define PEERROR 10000
void init(Lock *lock) {
	lock->status = UNLOCK;
}
int lock(Lock *lock, int combination) {
	if (lock->status == LOCKED)
		return OPERROR;
	if (combination < 0 || combination >= 10000)
		return PEERROR;
	lock->status = LOCKED;
	return lock->pwd = combination;
}
int unlock(Lock *lock, int combination) {
	if (lock->status == UNLOCK)
		return OPERROR;
	if (lock->pwd != combination)
		return LOCKED;
	return lock->status = UNLOCK;
}
int isLocked(Lock *lock) {
	return lock->status;
}

#undef PEERROR
#undef OPERROR
#undef LOCKED
#undef UNLOCK
