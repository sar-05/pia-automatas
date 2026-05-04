#ifndef MACHINES_H
#define MACHINES_H

#include <stdbool.h>
#include <stdlib.h>

enum Move { L, R, S };

struct deltaResult {
	int state;
	char sigma;
	enum Move move;
};

struct Machine {
	int state;
	char *tape;
	size_t tape_len;
	bool halt;
	struct deltaResult *(*delta)(struct Machine *);
	struct deltaResult *result;
	bool (*is_final)(int state);
};

void machine_init(struct Machine *,
		  char *tape,
		  size_t tape_len,
		  struct deltaResult *(*delta)(struct Machine *),
		  bool (*is_final)(int state));

void machine_next_state(struct Machine *);

void machine_destroy(struct Machine *);

#endif
