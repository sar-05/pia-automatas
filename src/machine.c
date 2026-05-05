#include "machine.h"

void machine_init(struct Machine *m,
		  char *tape,
		  size_t tape_len,
		  int final_state,
		  const struct Transition *transitions)
{
	/* Copy tape_len to int to avoid overflow */
	int n;

	for (n = tape_len - 2; n >= 0; n--) {
		tape[n + 1] = tape[n];
	}
	tape[++n] = '\0';

	m->state = &(transitions[0].state);
	m->tape = tape;
	m->tape_len = tape_len;
	m->halt = false;
	m->final_state = final_state;
	m->transitions = transitions;
}

void delta(struct Machine *m)
{
	size_t i;
	const int *q = m->state;
	char s = *(m->tape);

	for (i = 0; !(IS_END_TRANSITION(m->transitions[i])); i++) {
		if (m->transitions[i].state == *q &&
		    m->transitions[i].symbol == s) {
			m->state = &(m->transitions[i].next_state);
			*(m->tape) = m->transitions[i].write;

			if (m->transitions[i].move == R) {
				m->tape++;
				return;
			} else if (m->transitions[i].move == L) {
				m->tape--;
				return;
			} else if (m->transitions[i].move == S) {
				m->halt = true;
				return;
			} else
				exit(1);
		}
	}

	/* Halt by default if no transition matches */
	m->halt = true;
}
