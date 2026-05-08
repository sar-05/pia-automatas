#include <stdio.h>
#include <string.h>
#include "machine.h"

void machine_init(struct Machine *m,
		  char *tape,
		  int final_state,
		  const struct Transition *transitions)
{

	m->tape_len = strlen(tape);

	/* +1 for leading '\0', +1 for null terminator */
	m->tape_ptr = malloc(m->tape_len + 2);
	m->tape = m->tape_ptr;

	if (m->tape == NULL) {
		perror("Error alocating memory for tape");
		return;
	}

	m->tape[0] = '\0';
	snprintf(m->tape + 1, m->tape_len + 1, "%s", tape);

	m->state = &(transitions[0].state);
	m->halt = false;
	m->final_state = final_state;
	m->transitions = transitions;
}

void machine_destroy(struct Machine *m)
{
	free(m->tape_ptr);
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
