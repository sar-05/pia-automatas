#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "validate.h"
#include "machine.h"
#include "optparse.h"
#include "m2.h"
#include "m8.h"

struct ValidateArgs {
	char *string;
	int lang;
	bool list;
	bool trace;
	bool prompt;
	bool invalid;
	char *errmsg;
};

static int _is_valid_lang(char *lang)
{
	if (!strcmp(lang, "l2") || !strcmp(lang, "m2") || !strcmp(lang, "2"))
		return 2;

	if (!strcmp(lang, "l8") || !strcmp(lang, "m8") || !strcmp(lang, "8"))
		return 8;

	return 0;
}

static void _list_languages(void)
{
	printf("Lenguaje 2 = a^{2n}b^3\n"
	       "Lenguaje 8 = a^{n+1}(aba)^nc^2\n");
}

static struct optparse_long long_opts[] = {
    {"string", 's', OPTPARSE_REQUIRED},
    {"in", 'i', OPTPARSE_REQUIRED},
    {"list-languages", 'l', OPTPARSE_NONE},
    {"trace", 't', OPTPARSE_NONE},
    {"prompt", 'p', OPTPARSE_REQUIRED},
    {0}};

static struct ValidateArgs _parse_validate_args(char **argv)
{
	struct ValidateArgs args = {0};
	struct optparse opts;
	optparse_init(&opts, argv);
	int lang, opt;
	while ((opt = optparse_long(&opts, long_opts, NULL)) != -1) {
		switch (opt) {
		case 'i':
			lang = _is_valid_lang(opts.optarg);
			args.lang = (lang != -1) ? lang : 0;
			if (lang == -1) {
				args.invalid = true;
				args.errmsg =
				    "lenguaje desconocido. Use -l "
				    "para ver los lenguajes disponibles";
			}
			break;
		case 'l':
			args.list = true;
			break;
		case 'p':
			args.prompt = true;
			lang = _is_valid_lang(opts.optarg);
			args.lang = (lang != -1) ? lang : 0;
			if (lang == -1) {
				args.invalid = true;
				args.errmsg =
				    "lenguaje desconocido. Use -l "
				    "para ver los lenguajes disponibles";
			}
			break;
		case 't':
			args.trace = true;
			break;
		case '?':
			args.invalid = true;
			args.errmsg = opts.errmsg;
			break;
		}
	}
	args.string = optparse_arg(&opts);
	// Relationship validation
	if (args.list && (args.lang || args.string || args.prompt)) {
		args.invalid = true;
		args.errmsg = "-l no puede combinarse con ninguna otra opción";
	}
	if (!args.invalid && args.prompt && (args.lang == 0 || args.string)) {
		args.invalid = true;
		args.errmsg = "uso: validate -p <lenguaje> [-t]";
	}
	if (!args.invalid && !args.list && !args.prompt && !args.lang) {
		args.invalid = true;
		args.errmsg = "se requiere de -i / --in";
	}
	if (!args.invalid && !args.list && !args.prompt && !args.string) {
		args.invalid = true;
		args.errmsg = "hace falta argumento";
	}
	return args;
}
static const struct Transition *_get_transitions(int lang)
{

	assert(lang == 2 || lang == 8);

	switch (lang) {
	case 2:
		return m2_transitions;
	case 8:
		return m8_transitions;
	}

	return 0;
}

static int _get_fstate(int lang)
{

	assert(lang == 2 || lang == 8);

	switch (lang) {
	case 2:
		return M2_FINAL_STATE;
	case 8:
		return M8_FINAL_STATE;
	}

	return 0;
}

static void _run_machine_prompt(const struct Transition *transitions,
				int final_state,
				bool trace)
{
	struct Machine *m;

	m = (struct Machine *)malloc(sizeof(struct Machine));

	if (m == NULL)
		return;

	char *line;
	ic_set_history(NULL, -1);
	while ((line = ic_readline(NULL)) != NULL) {
		machine_init(m, line, final_state, transitions);
		free(line);
		while (!(m->halt))
			delta(m);
		printf("Cadena %s\n",
		       (*(m->state) == m->final_state) ? "válida" : "inválida");
		machine_destroy(m);
	}

	free(m);
}

static bool _run_machine_single(char *tape,
				const struct Transition *transitions,
				int final_state,
				bool trace)
{
	struct Machine *m;

	m = malloc(sizeof(struct Machine));

	if (m == NULL)
		return false;

	machine_init(m, tape, final_state, transitions);
	while (!(m->halt))
		delta(m);
	bool r = *(m->state) == m->final_state;

	machine_destroy(m);

	free(m);

	return r;
}

void handle_validate(char **argv)
{
	struct ValidateArgs args = _parse_validate_args(argv);
	if (args.invalid) {
		fprintf(stderr, "validate: %s\n", args.errmsg);
		return;
	}

	if (args.list) {
		_list_languages();
		return;
	}

	if (args.prompt) {
		_run_machine_prompt(_get_transitions(args.lang),
				    _get_fstate(args.lang),
				    args.trace);
		return;
	}

	/* TODO: verify that transitions and state aren't empty */
	bool v;
	v = _run_machine_single(args.string,
				_get_transitions(args.lang),
				_get_fstate(args.lang),
				args.trace);

	printf("Cadena %s\n", (v) ? "válida" : "inválida");
}
