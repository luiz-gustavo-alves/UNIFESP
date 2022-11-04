/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - FRACTAL - TRIANGULO DE SIERPINSKI
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

/* TAMANHO DA JANELA */
const int WIDTH = 800, HEIGHT = 800;

/* PALETE DE CORES */
float vColorRed[] = {1.0, 0.0, 0.0};
float vColorOrange[] = {1.0, 0.5, 0.0};
float vColorLimeGreen[] = {0.196, 0.8, 0.196};
float vColorGreen[] = {0.0, 1.0, 0.0};
float vColorAquamarine[] = {0.439, 0.858, 0.576};
float vColorBlue[] = {0.0, 0.0, 1.0};
float vColorBlueViolet[] = {0.623, 0.372, 0.623};
float vColorPurple[] = {0.87, 0.58, 0.98};
float vColorMagenta[] = {1.0, 0.0, 1.0};
float vColorWhite[] = {1.0, 1.0, 1.0};
float *vColor;

/* NÚMERO DE INTERAÇÕES */
int n;

float triangle[3][2] = { {-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5} };

/* ESCOPO DAS FUNÇÕES */
void selectColor();
void menu();
void buildTriangle(float *v1, float *v2, float *v3);
void divideTriangle(float *v1, float *v2, float *v3, int n);
void display();

void selectColor() {

    printf("\n(0) - VERMELHO | (1) - LARANJA | (2) - VERDE LIMAO\n");
    printf("(3) - VERDE | (4) - AZUL MARINHO | (5) AZUL\n");
    printf("(6) - AZUL VIOLETA | (7) - ROXO | (8) MAGENTA\n");
    printf("Define a cor da figura (PADRAO - (9): BRANCO): ");

    int color;
    scanf("%d", &color);

    switch (color) {

        case 0:
            vColor = vColorRed;
            break;

        case 1:
            vColor = vColorOrange;
            break;

        case 2:
            vColor = vColorLimeGreen;
            break;

        case 3:
            vColor = vColorGreen;
            break;

        case 4:
            vColor = vColorAquamarine;
            break;

        case 5:
            vColor = vColorBlue;
            break;

        case 6:
            vColor = vColorBlueViolet;
            break;

        case 7:
            vColor = vColorPurple;
            break;

        case 8:
            vColor = vColorMagenta;
            break;

        default:
            vColor = vColorWhite;
            break;
    }
}

void menu() {

    printf("* * * * * Carpete de Sierpinski * * * * *");

    int errFlag = 1;
    while (errFlag) {
        printf("\nInserir Numero de Interacoes: (LIMITE 10): ");
        scanf("%d", &n);
        if (n >= 0 && n <= 10) errFlag = 0;
    }
    selectColor();
}

void buildTriangle(float *v1, float *v2, float *v3) {

    glBegin(GL_TRIANGLES);

        glColor3fv(vColor);
        glVertex2fv(v1);
        glVertex2fv(v2);
        glVertex2fv(v3);

    glEnd();
}

void divideTriangle(float *v1, float *v2, float *v3, int n) {

    float mid[3][3];
    int k;

    if (n > 0) {

        for (k = 0; k < 2; k++) mid[0][k] = (v1[k] + v2[k]) / 2;
        for (k = 0; k < 2; k++) mid[1][k] = (v1[k] + v3[k]) / 2;
        for (k = 0; k < 2; k++) mid[2][k] = (v2[k] + v3[k]) / 2;

        divideTriangle(v1, mid[0], mid[1], n - 1);
        divideTriangle(v3, mid[1], mid[2], n - 1);
        divideTriangle(v2, mid[2], mid[0], n - 1);
    }
    else {
        buildTriangle(v1, v2, v3);
    }
}

void display() {

    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    divideTriangle(triangle[0], triangle[1], triangle[2], n);
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {

    menu();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Triangulo de Sierpinski");

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
 }
