/*
 *   UNIFESP SJC
 *
 *   COMPUTACAO GRAFICA
 *   OPENGL - FRACTAL
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#ifndef FRACTAL_H_INCLUDED
#define FRACTAL_H_INCLUDED

#include "paleteCores.h"

/* Numero de iteracoes */
int n;

float triangle[3][2] = { {-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5} };


typedef struct Coords {

    float px, py;

} Coords;

Coords  a = { 1.0, -1.0},
        b = {-1.0, -1.0};


/* Define a cor da Arvore de Pitagoras */
void setPythagorasTreeColor(int n) {

    int color = n;

    if (n <= 4) glColor3fv(forestgreen.color);
    else glColor3fv(saddlebrown.color);
}

/* Desenha a Arvore de Pitagoras */
void drawPythagorasTree(Coords a, Coords b, Coords c, Coords d, int n) {

    setPythagorasTreeColor(n);
    glBegin(GL_POLYGON);

        glVertex2f(a.px, a.py);
        glVertex2f(b.px, b.py);
        glVertex2f(c.px, c.py);
        glVertex2f(d.px, d.py);

    glEnd();
}

/* Desenha Triangulo de Sierpinski */
void drawSierpinskiTriangle(float *v1, float *v2, float *v3) {

    glBegin(GL_TRIANGLES);

        glColor3fv(gold.color);
        glVertex2fv(v1);
        glVertex2fv(v2);
        glVertex2fv(v3);

    glEnd();
}

void pythagorasTreeAlgorithm(Coords a, Coords b, int n) {

    Coords c, d, e;

    c.px = b.px - (a.py -  b.py);
	c.py = b.py - (b.px - a.px);

	d.px = a.px - (a.py -  b.py);
	d.py = a.py - (b.px - a.px);

	e.px = d.px + (b.px - a.px - (a.py -  b.py)) / 2;
	e.py = d.py - (b.px - a.px + a.py -  b.py) / 2;

    if (n >= 0) {

        drawPythagorasTree(a, b, c, d, n);
        pythagorasTreeAlgorithm(d, e, n - 1);
        pythagorasTreeAlgorithm(e, c, n - 1);
    }
}

void sierpinskiTriangleAlgorithm(float *v1, float *v2, float *v3, int n) {

    float mid[3][3];
    int k;

    if (n > 0) {

        for (k = 0; k < 2; k++) mid[0][k] = (v1[k] + v2[k]) / 2;
        for (k = 0; k < 2; k++) mid[1][k] = (v1[k] + v3[k]) / 2;
        for (k = 0; k < 2; k++) mid[2][k] = (v2[k] + v3[k]) / 2;

        sierpinskiTriangleAlgorithm(v1, mid[0], mid[1], n - 1);
        sierpinskiTriangleAlgorithm(v3, mid[1], mid[2], n - 1);
        sierpinskiTriangleAlgorithm(v2, mid[2], mid[0], n - 1);
    }
    else {
        drawSierpinskiTriangle(v1, v2, v3);
    }
}

void buildPythagorasTree(int numIteration) {

    n = numIteration;
    pythagorasTreeAlgorithm(a, b, n);
}

void buildSierpinskiTriangle(int numIteration) {

    n = numIteration;
    sierpinskiTriangleAlgorithm(triangle[0], triangle[1], triangle[2], n);
}

#endif // FRACTAL_H_INCLUDED
