#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isocline.h"
#include "validate.h"
#include "argv.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(void)
{
#ifdef _WIN32
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
#endif
	char *line;
	ic_set_history(NULL, -1);
	while ((line = ic_readline(NULL)) != NULL) {
		char **argv = make_argv(line, NULL);
		if (!argv || !argv[0]) {
			free_argv(argv);
			free(line);
			continue;
		}

		if (!strcmp(argv[0], "validate"))
			handle_validate(argv);
		else if (!strcmp(argv[0], "clear"))
			puts("\033[H\033[2J");
		else if (!strcmp(argv[0], "exit")) {
			free_argv(argv);
			free(line);
			break;
		} else
			fprintf(stderr, "Comando desconocido: %s\n", argv[0]);

		free_argv(argv);
		free(line);
	}

	return 0;
}
