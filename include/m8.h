#ifndef M8__H
#define M8__H

#include "machine.h"

struct deltaResult *m8_delta(struct Machine *m);

bool m8_is_final(int state);

#endif
