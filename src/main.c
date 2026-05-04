#include <stdio.h>
#include <stdlib.h>

enum State { q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11 };
enum Move { L, R, S };

struct Config {
	enum State state;
	int halt;
};

struct Result {
	enum State state;
	char sigma;
	enum Move move;
};

struct Result *delta(struct Config *, char *, struct Result *);
void tape_adjust(char *, size_t);
void tape_next(char **, struct Result *, struct Config *);

int main(void)
{
	char *tp = NULL;
	size_t len;
	size_t n;

	n = getline(&tp, &len, stdin);

	tape_adjust(tp, n);

	struct Config conf = {q0, 0};
	struct Result *r = (struct Result *)malloc(sizeof(struct Result));

	char *tp_cpy = tp;

	while (!conf.halt) {
		delta(&conf, tp_cpy, r);
		tape_next(&tp_cpy, r, &conf);
	}

	if (conf.state == q11)
		printf("Cadena válida\n");
	else
		printf("Cadena inválida\n");

	free(tp);

	return 0;
}

void tape_adjust(char *tp, size_t size)
{
	/* Copy size to int to avoid overflow */
	int n;

	for (n = size - 2; n >= 0; n--) {
		tp[n + 1] = tp[n];
	}
	tp[++n] = '\0';
}

/* Update state in config struct and move tape head according to result */
void tape_next(char **tp, struct Result *r, struct Config *conf)
{
	conf->state = r->state;

	**tp = r->sigma;

	if (r->move == R) {
		(*tp)++;
	} else if (r->move == L)
		(*tp)--;
	else if (r->move == S)
		conf->halt = 1;
}

struct Result *delta(struct Config *conf, char *tp, struct Result *r)
{
	enum State q = conf->state;
	char s = *tp;
	/* d1 */
	if (q == q0 && s == '\0') {
		printf("Entra d1\n");
		r->state = q1;
		r->sigma = '\0';
		r->move = R;
		/* d2 */
	} else if (q == q1 && s == 'a') {
		printf("Entra d2\n");
		r->state = q2;
		r->sigma = '\0';
		r->move = R;
		/* d3 */
	} else if (q == q2 && (s == 'a' || s == 'b' || s == 'c')) {
		printf("Entra d3\n");
		r->state = q2;
		r->sigma = s;
		r->move = R;
		/* d4 */
	} else if (q == q2 && s == '\0') {
		printf("Entra d4\n");
		r->state = q3;
		r->sigma = '\0';
		r->move = L;
		/* d5 */
	} else if (q == q3 && s == 'c') {
		printf("Entra d5\n");
		r->state = q4;
		r->sigma = '\0';
		r->move = L;
		/* d6 */
	} else if (q == q4 && s == 'c') {
		printf("Entra d6\n");
		r->state = q5;
		r->sigma = '\0';
		r->move = L;
		/* d7 */
	} else if (q == q5 && (s == 'a' || s == 'b')) {
		printf("Entra d7\n");
		r->state = q5;
		r->sigma = s;
		r->move = L;
		/* d8 */
	} else if (q == q5 && s == '\0') {
		printf("Entra d8\n");
		r->state = q6;
		r->sigma = '\0';
		r->move = R;
		/* d9 */
	} else if (q == q6 && s == '\0') {
		printf("Entra d9\n");
		r->state = q11;
		r->sigma = '\0';
		r->move = S;
		/* d10 */
	} else if (q == q6 && s == 'a') {
		printf("Entra d10\n");
		r->state = q7;
		r->sigma = '\0';
		r->move = R;
		/* d11 */
	} else if (q == q7 && (s == 'a' || s == 'b')) {
		printf("Entra d11\n");
		r->state = q7;
		r->sigma = s;
		r->move = R;
		/* d12 */
	} else if (q == q7 && s == '\0') {
		printf("Entra d12\n");
		r->state = q8;
		r->sigma = '\0';
		r->move = L;
		/* d13 */
	} else if (q == q8 && s == 'a') {
		printf("Entra d13\n");
		r->state = q9;
		r->sigma = '\0';
		r->move = L;
		/* d14 */
	} else if (q == q9 && s == 'b') {
		printf("Entra d14\n");
		r->state = q10;
		r->sigma = '\0';
		r->move = L;
		/* d15 */
	} else if (q == q10 && s == 'a') {
		printf("Entra d15\n");
		r->state = q5;
		r->sigma = '\0';
		r->move = L;
	} else {
		printf("No entra d\n");
		r->state = q;
		r->sigma = s;
		r->move = S;
	}

	return r;
}
