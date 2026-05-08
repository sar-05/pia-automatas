#ifndef MACHINES_H
#define MACHINES_H

#include <stdbool.h>
#include <stdlib.h>

enum Move { L, R, S };

struct Transition {
	int state;
	char symbol;
	int next_state;
	char write;
	enum Move move;
};

#define END_TRANSITION {-1, '\0', -1, '\0', S}

#define IS_END_TRANSITION(t) ((t).state == -1)

struct Machine {
	const int *state;
	char *tape;
	char *tape_ptr;
	size_t tape_len;
	bool halt;
	const struct Transition *transitions;
	int final_state;
};

void machine_init(struct Machine *,
		  char *tape,
		  int final_state,
		  const struct Transition *transitions);

void machine_destroy(struct Machine *m);

void delta(struct Machine *m);

#endif
