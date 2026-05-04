#include "m8.h"

struct deltaResult *m8_delta(struct Machine *m)
{
	int q = m->state;
	char s = *(m->tape);
	/* d1 */
	if (q == 0 && s == '\0') {
		m->result->state = 1;
		m->result->sigma = '\0';
		m->result->move = R;
		/* d2 */
	} else if (q == 1 && s == 'a') {
		m->result->state = 2;
		m->result->sigma = '\0';
		m->result->move = R;
		/* d3 */
	} else if (q == 2 && (s == 'a' || s == 'b' || s == 'c')) {
		m->result->state = 2;
		m->result->sigma = s;
		m->result->move = R;
		/* d4 */
	} else if (q == 2 && s == '\0') {
		m->result->state = 3;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d5 */
	} else if (q == 3 && s == 'c') {
		m->result->state = 4;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d6 */
	} else if (q == 4 && s == 'c') {
		m->result->state = 5;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d7 */
	} else if (q == 5 && (s == 'a' || s == 'b')) {
		m->result->state = 5;
		m->result->sigma = s;
		m->result->move = L;
		/* d8 */
	} else if (q == 5 && s == '\0') {
		m->result->state = 6;
		m->result->sigma = '\0';
		m->result->move = R;
		/* d9 */
	} else if (q == 6 && s == '\0') {
		m->result->state = 11;
		m->result->sigma = '\0';
		m->result->move = S;
		/* d10 */
	} else if (q == 6 && s == 'a') {
		m->result->state = 7;
		m->result->sigma = '\0';
		m->result->move = R;
		/* d11 */
	} else if (q == 7 && (s == 'a' || s == 'b')) {
		m->result->state = 7;
		m->result->sigma = s;
		m->result->move = R;
		/* d12 */
	} else if (q == 7 && s == '\0') {
		m->result->state = 8;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d13 */
	} else if (q == 8 && s == 'a') {
		m->result->state = 9;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d14 */
	} else if (q == 9 && s == 'b') {
		m->result->state = 10;
		m->result->sigma = '\0';
		m->result->move = L;
		/* d15 */
	} else if (q == 10 && s == 'a') {
		m->result->state = 5;
		m->result->sigma = '\0';
		m->result->move = L;
	} else {
		m->result->state = q;
		m->result->sigma = s;
		m->result->move = S;
	}

	return m->result;
}

bool m8_is_final(int state)
{
	if (state == 11)
		return true;
	return false;
}
