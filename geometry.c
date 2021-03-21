#include "geometry.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define threshold 0.000001

int is_equal(double a, double b) { return abs(a - b) < threshold; }
int points_equal(point a, point b) { return a.x == b.x && a.y == b.y; }

/**
 * calcula a proporção entre os segmentos AP e AB
 */
double calc_lambda(point p, point a, point b) {
    int delta_x_ab = b.x - a.x;
    int delta_y_ab = b.y - a.y;
    int delta_x_ap = p.x - a.x;
    int delta_y_ap = p.y - a.y;

    if (delta_x_ab != 0 && delta_x_ap != 0) {
        return delta_x_ap / (double)delta_x_ab;
    } else if (delta_y_ab != 0 && delta_y_ap != 0) {
        return delta_y_ap / (double)delta_y_ab;
    }
    return 0;
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
    int result = (p.y - a.y) * (a.x - b.x) == (p.x - a.x) * (a.y - b.y);
    return result && is_between(lambda, 0.0, 1.0);
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
    int crossings = 0;

    for (int i = 0; i < n; i++) {
        point a = poly[i];
        point b = i == n - 1 ? poly[0] : poly[i + 1];

        int result = verify(p, a, b);
        if (result == 2) {
            return 1;
        } else if (result == 1) {
            crossings++;
        }
    }
    return crossings % 2;
}
