#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **make_argv(const char *line, int *argc_out)
{
	int argc = 0;
	int capacity = 8;
	char **argv = malloc(capacity * sizeof(char *));
	if (!argv)
		return NULL;

	const char *p = line;
	while (*p) {
		while (*p && isspace((unsigned char)*p))
			p++;
		if (!*p)
			break;

		if (argc >= capacity - 1) {
			capacity *= 2;
			argv = realloc(argv, capacity * sizeof(char *));
			if (!argv)
				return NULL;
		}

		char token[1024];
		int len = 0;
		char quote = 0;

		if (*p == '\'' || *p == '"') {
			quote = *p++;
			while (*p && *p != quote)
				token[len++] = *p++;
			if (*p == quote)
				p++;
		} else {
			while (*p && !isspace((unsigned char)*p))
				token[len++] = *p++;
		}

		token[len] = '\0';
		argv[argc++] = memcpy(malloc(len + 1), token, len + 1);
	}

	argv[argc] = NULL;
	if (argc_out)
		*argc_out = argc;
	return argv;
}

void free_argv(char **argv)
{
	if (!argv)
		return;
	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}
