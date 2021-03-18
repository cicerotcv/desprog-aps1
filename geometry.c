#include "geometry.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define threshold 0.000001

int is_equal(double a, double b) { return abs(a - b) < threshold; }
int points_equal(point a, point b) { return a.x == b.x && a.y == b.y; }

double calc_lambda(point p, point a, point b) {
    if (a.x != b.x) {
        return (p.x - a.x) / (b.x - a.x);
    }
    return (p.y - a.y) / (b.y - a.y);
}

int is_between(double number, double a, double b) {
    double min, max;
    if (a > b) {
        min = b;
        max = a;
    } else {
        min = a;
        max = b;
    }
    return (min - threshold < number) && (number < max + threshold);
}

/**
 * Verifica se o ponto está sob o segmento de reta AB
 */
int case_2(point p, point a, point b) {
    if (a.x == p.x && b.x == p.x && a.y == b.y) {
        return 1;
    }
    double lambda = calc_lambda(p, a, b);
    return (p.y - a.y) * (a.x - b.x) == (p.x - a.x) * (a.y - b.y) &&
           is_between(lambda, 0.0, 1.0);
}

int case_1(point p, point a, point b) {
    if (p.y <= b.y && p.y <= a.y) {
        return 0;
    }
    if (is_between(p.y, a.y, b.y)) {
        if (a.x == b.x) {
            return p.x < a.x;
        }
        double delta_x = a.x - b.x;
        double delta_y = a.y - b.y;
        double x_intersect = a.x + (delta_x / delta_y) * (p.y - a.y);
        return p.x < x_intersect;
    }
    return 0;
}

int verify(point p, point a, point b) {
    if (points_equal(a, b)) {
        if (points_equal(a, p)) {
            return 2;
        }
        return 0;
    }
    if (case_2(p, a, b)) {
        return 2;
    } else if (case_1(p, a, b)) {
        return 1;
    }
    return 0;
}

int inside(point p, point poly[], int n) {
    return 0;
}
