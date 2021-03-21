#include "geometry.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define threshold 0.000001

/**
 * Verifica se dois números do tipo double possuem uma diferença menor que
 * a tolerância;
 */
int is_equal(double a, double b) { return abs(a - b) < threshold; }

/**
 * Verifica se dois pontos são iguais;
 */
int points_equal(point a, point b) { return a.x == b.x && a.y == b.y; }

/**
 * Calcula a proporção entre os segmentos AP e AB
 */
double calc_lambda(point p, point a, point b) {
    int delta_ab_x = b.x - a.x;
    int delta_ab_y = b.y - a.y;
    int delta_ap_x = p.x - a.x;
    int delta_ap_y = p.y - a.y;

    if (delta_ab_x != 0 && delta_ap_x != 0) {
        return delta_ap_x / (double)delta_ab_x;
    } else if (delta_ab_y != 0 && delta_ap_y != 0) {
        return delta_ap_y / (double)delta_ab_y;
    }
    return 0;
}

/**
 * Verifica se um número do tipo double está dentro de um intervalo
 * entre dois outros números do tipo double levando em conta a
 * tolerância;
 */
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
 * Verifica se determinado ponto P está contido na reta que
 * passa pelos pontos A e B;
 */
int ab_contains(point p, point a, point b) {
    return (p.y - a.y) * (a.x - b.x) == (p.x - a.x) * (a.y - b.y);
}

/**
 * Verifica se um ponto P está sobre o segmento de reta AB
 */
int case_2(point p, point a, point b) {
    if (a.x == p.x && b.x == p.x && a.y == b.y) {
        return 1;
    }

    double lambda = calc_lambda(p, a, b);
    return ab_contains(p, a, b) && is_between(lambda, 0.0, 1.0);
}

/**
 * Verifica se a projeção na horizontal de um determinado
 * ponto P cruza o segmento AB;
 */
int case_1(point p, point a, point b) {
    // caso trivial em que p.y é menor ou igual a ambas as
    // extremidades do segmento AB;
    if (p.y <= b.y && p.y <= a.y) {
        return 0;
    }
    // p.y deve estar entre a.y e b.y;
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
    // caso triviail: se A e B forem coincidentes, os únicos
    // casos possíveis são 2 ou 0;
    if (points_equal(a, b)) {
        // caso A == B == P, o ponto pertence ao segmento
        // e ao polígono;
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
