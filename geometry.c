#include "geometry.h"

#include <math.h>

#include "helpers.c"

int verify(point p, point a, point b) {
    if (case_2(p, a, b)) {
        return 2;
    }
    return 0;
}

int inside(point p, point poly[], int n) { return 0; }
