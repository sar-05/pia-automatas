#define _POSIX_C_SOURCE 200809L
#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include "m8.h"

int main(void)
{
	char *tp = NULL;
	size_t buf_size;
	size_t tp_len;

	tp_len = getline(&tp, &buf_size, stdin);

	if (tp == NULL)
		return 1;

	struct Machine *m;

	m = (struct Machine *)malloc(sizeof(struct Machine));

	if (m == NULL)
		return 1;

	machine_init(m, tp, tp_len, 11, m8_transitions);

	while (!(m->halt))
		delta(m);

	free(tp);

	printf("Cadena %s\n",
	       (*(m->state) == m->final_state) ? "válida" : "inválida");
	return 0;
}
