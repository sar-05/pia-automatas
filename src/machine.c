#include "machine.h"

void machine_init(struct Machine *m,
		  char *tape,
		  size_t tape_len,
		  struct deltaResult *(*d)(struct Machine *),
		  bool (*is_final)(int state))
{
	/* Copy tape_len to int to avoid overflow */
	int n;

	for (n = tape_len - 2; n >= 0; n--) {
		tape[n + 1] = tape[n];
	}
	tape[++n] = '\0';

	struct deltaResult *dR = malloc(sizeof(struct deltaResult));

	if (dR == NULL)
		exit(1);

	m->state = 0;
	m->tape = tape;
	m->tape_len = tape_len;
	m->halt = false;
	m->delta = d;
	m->result = dR;
	m->is_final = is_final;
}

void machine_next_state(struct Machine *m)
{
	struct deltaResult *(*d)(struct Machine *);
	d = m->delta;

	struct deltaResult *r = (*d)(m);
	m->state = r->state;
	*(m->tape) = r->sigma;

	if (r->move == R)
		m->tape++;
	else if (r->move == L)
		m->tape--;
	else if (r->move == S)
		m->halt = true;
	else
		exit(1);
}

void machine_destroy(struct Machine *m)
{
	free(m->result);
}
