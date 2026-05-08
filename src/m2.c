#include "m2.h"

const struct Transition m2_transitions[] = {
    /* EXAMPLE \{STATE, CHAR, NEXT_STATE, NEXT_CHAR, NEXT_MOVE}*/
    /* d1  */ {0, '\0', 1, '\0', R},
    /* d2  */ {1, 'a', 1, 'a', R},
    /* d2  */ {1, 'b', 1, 'b', R},
    /* d3  */ {1, '\0', 2, '\0', L},
    /* d4  */ {2, 'b', 3, '\0', L},
    /* d5  */ {3, 'b', 4, '\0', L},
    /* d6  */ {4, 'b', 5, '\0', L},
    /* d7  */ {5, '\0', 8, '\0', S},
    /* d8  */ {5, 'a', 6, '\0', L},
    /* d9  */ {6, 'a', 7, '\0', L},
    /* d10  */ {7, 'a', 6, '\0', L},
    /* d11  */ {7, '\0', 8, '\0', S},
    /* END */ END_TRANSITION,
};
