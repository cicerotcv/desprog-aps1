
#include <stdlib.h>

#define threshold 1e-6

double is_equal(double a, double b) { return abs(a - b) < threshold; }

double calc_lambda(point p, point a, point b) {
    if (!is_equal(a.x, b.x)) {
        return (p.x - a.x) / (b.x - a.x);
    }
    return (p.y - a.y) / (b.y - a.y);
}

double is_between(double number, double a, double b) {
    double min, max;
    if (a > b) {
        min = b;
        max = a;
    } else {
        min = a;
        max = b;
    }
    return min - threshold < number && number < max + threshold;
}

/**
 * Verifica se o ponto está sob o segmento de reta AB
 */
int case_2(point p, point a, point b) {
    double lambda = calc_lambda(p, a, b);
    return is_equal((p.y - a.y) * (a.x - b.x), (p.x - a.x) * (a.y - b.y)) &&
           is_between(lambda, 0.0, 1.0);
}