#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
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

	machine_init(m, tp, tp_len, &m8_delta, &m8_is_final);

	while (!(m->halt)) {
		machine_next_state(m);
	}

	machine_destroy(m);

	free(tp);

	printf("%s\n",
	       (m->is_final(m->state)) ? "Cadena válida" : "Cadena inválida");
}
