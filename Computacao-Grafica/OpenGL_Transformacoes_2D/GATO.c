/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - TRANSFORMAÇÕES GEOMÉTRICAS
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

#define MIN 1
#define MAX 160

/* TAMANHO DA JANELA */
const int WIDTH = 800, HEIGHT = 800;

/* PALETE DE CORES */
float vColorBlack[] = {0.0, 0.0, 0.0};
float vColorWhite[] = {1.0, 1.0, 1.0};
float vColorGrey[] = {0.8, 0.8, 0.8};
float vColorRed[] = {1.0, 0.0, 0.0};

/* VARIÁVEIS DE CONTROLE */
float pos[2] = {0.0, 0.0};
float scaleFactor = 1.0;
float theta = 0.0;
int limit = 100;
int ballCount = 0;
int direction = 0;

/* FLAGS - TRANSFORMAÇÕES 2D */
unsigned int scaleFlag = 0;
unsigned int scaleRotateFlag = 0;
unsigned int scaleTranslateFlag = 0;
unsigned int rotateFlag = 0;
unsigned int translateFlag = 0;

/* FLAGS - CONTROLE DE EXECUÇÃO */
unsigned int angleFlag = 1;
unsigned int antiClockwiseFlag = 1;
unsigned int collisionFlag = 0;
unsigned int directionFlag = 1;
unsigned int xFlag = 0;
unsigned int yFlag = 0;
unsigned int stopFlag = 1;

/* DEFINIÇÃO DE STRUCTS */
typedef struct figLst {

    float px, py;
    float radius;
    int ball_ID;
    struct figLst *next;

}figLst;

typedef struct pGato{

    float px[38], py[38];
    float radius[9];
    int num_vertices;
    int num_radius;

} pGato;

typedef struct pTranslate {

    float px, py;
    float newPx, newPy;

} pTranslate;

/* PONTEIROS GLOBAIS */
pGato *gato = NULL;
pTranslate *pTr = NULL;
figLst *head = NULL;

/* ESCOPO DE FUNÇÕES */
pGato *initCat(pGato *gato);
pTranslate *initTranslation(pTranslate *pTr);
void addNode(float px, float py);
void deleteFirstNode();
void deleteNode(int index);
float dist(float px, float py, float tx, float ty);
int checkOutOfBounds(float px, float py, float radius);
int checkLinePointCollision(float px, float py, float a1, float a2, float b1, float b2);
int checkHitboxCollision(float px, float py, float radius);
int checkPositionX(float px);
int checkPositionY(float py);
int determineRotation(float px, float py, float rx, float ry);
void translate(float tx, float ty);
void scale(float sx, float sy);
void rotate(float rx, float ry, float theta);
void buildCircle(float px, float py, float radius, float vColor[], int fill);
void buildBall();
void buildCat();
int followBall();
void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

pGato *initCat(pGato *gato) {

    gato = (pGato*)malloc(sizeof(pGato));
    gato->num_vertices = 38;
    gato->num_radius = 9;

    float x[] = {-0.2, 0.0, -0.165, -0.09, -0.09, -0.337, -0.36, -0.282, -0.227, -0.172,
                 -0.2, -0.28, -0.12, 0.187, 0.327, -0.155, -0.155, -0.065, -0.065, 0.04,
                 0.04, 0.162, 0.162, -0.16, -0.07, 0.05, 0.17, -0.15, -0.115, -0.15,
                 -0.115, -0.28, -0.245, -0.28, -0.245, -0.02, -0.2, -10.0};

    float y[] = {0.2, 0.0, 0.347, 0.412, 0.3, 0.257, 0.362, 0.33, 0.202, 0.202, 0.172,
                 0.23, 0.23, 0.06, 0.212, -0.110, -0.26, -0.180, -0.26, -0.177, -0.26,
                 -0.105, -0.26, -0.28, -0.28, -0.28, -0.28, 0.18, 0.18, 0.16, 0.16,
                 0.18, 0.18, 0.16, 0.16, 0.05, 0.16, 0.16};

    float radius[] = {0.15, 0.2, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03, 0.425};

    int i;
    for (i = 0; i < gato->num_vertices; i++) {
        gato->px[i] = x[i];
        gato->py[i] = y[i];
    }

    for (i = 0; i < gato->num_radius; i++) {
        gato->radius[i] = radius[i];
    }
    return gato;
}

pTranslate *initTranslation(pTranslate *pTr) {

    pTr = (pTranslate*)malloc(sizeof(pTranslate));
    pTr->newPx = pos[0];
    pTr->newPy = pos[1];
    return pTr;
}

void addNode(float px, float py) {

    figLst *newFig = (figLst*) malloc(sizeof(figLst));
    newFig->px = px;
    newFig->py = py;
    newFig->radius = 0.025;
    newFig->ball_ID = ballCount;
    newFig->next = NULL;

    if (head == NULL) head = newFig;
    else
    {
        figLst *p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newFig;
    }
}

void deleteFirstNode() {

     if (head != NULL) {

        figLst* temp = head;
        head = head->next;
        free(temp);
        ballCount--;
     }
}

void deleteNode(int index) {

    if (head != NULL) {

        if (index == 0) deleteFirstNode();
        else {

            figLst* temp = head;
            int i;
            for (i = 0; temp != NULL && i < index - 1; i++) {
                temp = temp->next;
            }

            figLst* next = temp->next->next;
            free(temp->next);
            temp->next = next;
            ballCount--;
        }
    }
}

float dist(float px, float py, float tx, float ty) {

    /* DISTÂNCIA ENTRE DOIS PONTOS */
    return (sqrt(pow((px - tx), 2) + pow((py - ty), 2)));
}

int checkOutOfBounds(float px, float py, float radius) {

    return (px + radius >= 1 || py + radius >= 1 || px - radius <= -1 || py - radius <= -1);
}

int checkLinePointCollision(float px, float py, float a1, float a2, float b1, float b2) {

    float d1 = dist(px, py, a1, a2);
    float d2 = dist(px, py, b1, b2);
    float lineLen = dist(a1, a2, b1, b2);

    return (d1 + d2 >= lineLen - 0.015 && d1 + d2 <= lineLen + 0.015);
}

int checkHitboxCollision(float px, float py, float radius) {

    float dist_x;
    float dist_y;
    float radius_sum;

    unsigned int headCollision = 0;
    unsigned int index = 0;

    figLst *temp = head;
    while (temp != NULL) {

        dist_x = px - temp->px;
        dist_y = py - temp->py;
        radius_sum = radius + temp->radius;

        if (dist_x * dist_x + dist_y * dist_y <= radius_sum * radius_sum) {

            if (index == 0) headCollision = 1;
            deleteNode(index);
        }
        temp = temp->next;
        index++;
    }
    return headCollision;
}

int checkPositionX(float px) {

    /* VERIFICAR SE O GATO PRECISA TRANSLADAR NO EIXO X */
    return (px >= head->px - 0.015 && px <= head->px + 0.015);
}

int checkPositionY(float py) {

    /* VERIFICAR SE O GATO PRECISA TRANSLADAR NO EIXO Y */
    return (py >= head->py - 0.015 && py <= head->py + 0.015);
}

int determineRotation(float px, float py, float rx, float ry) {

    float clock = -0.001;
    float antiClock = 0.001;

    float clock_x = pos[0] + (rx - pos[0]) * cos(clock) - (ry - pos[1]) * sin(clock);
    float clock_y = pos[1] + (rx - pos[0]) * sin(clock) + (ry - pos[1]) * cos(clock);
    float antiClock_x = pos[0] + (rx - pos[0]) * cos(antiClock) - (ry - pos[1]) * sin(antiClock);
    float antiClock_y = pos[1] + (rx - pos[0]) * sin(antiClock) + (ry - pos[1]) * cos(antiClock);

    float d1 = dist(px, py, clock_x, clock_y);
    float d2 = dist(px, py, antiClock_x, antiClock_y);

    /*  DETERMINAR O SENTIDO DA ROTAÇÃO
     *  d1 > d2 (clockwise) | d2 > d1 (anti-clockwise)
     */

    return (d1 >= d2);
}

void translate(float tx, float ty) {

    int i;
    for (i = 0; i < gato->num_vertices; i++) {
        gato->px[i] = gato->px[i] + tx;
        gato->py[i] = gato->py[i] + ty;
    }
}

void scale(float sx, float sy) {

    float px = gato->px[35] * scaleFactor + sx * (1 - scaleFactor);
    float py = gato->py[35] * scaleFactor + sy * (1 - scaleFactor);
    float radius = gato->radius[8] * scaleFactor;

    if (!checkOutOfBounds(px, py, radius)) {

        int i;
        for (i = 0; i < gato->num_vertices; i++) {
            gato->px[i] = gato->px[i] * scaleFactor + sx * (1 - scaleFactor);
            gato->py[i] = gato->py[i] * scaleFactor + sy * (1 - scaleFactor);
            if (i < 9) gato->radius[i] = gato->radius[i] * scaleFactor;
        }
    }
    else {
        printf("Escala fora do limite da borda.\n");
    }
}

void rotate(float rx, float ry, float theta) {

    int i;
    for (i = 0; i < gato->num_vertices; i++) {
        gato->px[i] = rx + (gato->px[i] - rx) * cos(theta) - (gato->py[i] - ry) * sin(theta);
        gato->py[i] = ry + (gato->px[i] - rx) * sin(theta) + (gato->py[i] - ry) * cos(theta);
    }
}

void buildCircle(float px, float py, float radius, float vColor[], int fill) {

    float x, y;
    float angle;
    int i;

    glColor3fv(vColor);
    if (fill) {

        glBegin(GL_TRIANGLE_FAN);
            for (i = 0; i <= 60; i++)
            {
                angle = 2 * PI * i / 60.0;
                glVertex2f(px + (radius * cos(angle)), py + (radius * sin(angle)));
            }
        glEnd();
    }

    else {

        glBegin(GL_LINE_LOOP);
            for (i = 0; i <= 60; i++)
            {
                angle = 2 * PI * i / 60.0;
                glVertex2f(px + (radius * cos(angle)), py + (radius * sin(angle)));
            }
        glEnd();
    }
}

void buildBall() {

    figLst *p = head;
    while (p != NULL) {

        buildCircle(p->px, p->py, p->radius, vColorRed, 1);
        p = p->next;
    }
}

void buildCat() {

    /* TRANSFORMAÇÃO 2D - ESCALA */
    if ((limit > MIN && limit < MAX) && scaleFlag) {
        scale(pTr->newPx, pTr->newPy);
        scaleFlag = rotateFlag = translateFlag = stopFlag = 0;
        scaleRotateFlag = scaleTranslateFlag = 1;
    }

    /* TRANSFORMAÇÃO 2D - ROTAÇÃO */
    if (rotateFlag) {
        rotate(pos[0], pos[1], theta);
        rotateFlag = 0;
    }

    /* TRANSFORMAÇÃO 2D - TRANSLAÇÃO */
    if (translateFlag) {
        translate(pTr->px, pTr->py);
        translateFlag = 0;
    }

    /*
     *  HITBOX
     *  buildCircle(gato->px[35], gato->py[35], gato->radius[8], vColorRed, 0);
     */


    /*
     *  EIXO DE ROTACAO
     *  glBegin(GL_LINES);
     *
     *      glColor3fv(vColorRed);
     *      glVertex2d(gato->px[36], gato->py[36]);
     *      glVertex2d(gato->px[37], gato->py[37]);
     *
     *  glEnd();
    /*

    /* CABEÇA */
    buildCircle(gato->px[0], gato->py[0], gato->radius[0], vColorGrey, 1);

    /* CORPO */
    buildCircle(gato->px[1], gato->py[1], gato->radius[1], vColorGrey, 1);

    /* ORELHA DIREITA */
    glColor3fv(vColorBlack);
    glBegin(GL_POLYGON);

            glVertex2f(gato->px[2], gato->py[2]);
            glVertex2f(gato->px[3], gato->py[3]);
            glVertex2f(gato->px[4], gato->py[4]);

    glEnd();

    /* ORELHA ESQUERDA */
    glColor3fv(vColorBlack);
    glBegin(GL_POLYGON);

            glVertex2f(gato->px[5], gato->py[5]);
            glVertex2f(gato->px[6], gato->py[6]);
            glVertex2f(gato->px[7], gato->py[7]);

    glEnd();

    /* NARIZ */
    glColor3fv(vColorBlack);
    glBegin(GL_POLYGON);

            glVertex2f(gato->px[8], gato->py[8]);
            glVertex2f(gato->px[9], gato->py[9]);
            glVertex2f(gato->px[10], gato->py[10]);

    glEnd();

    /* OLHO ESQUERDO */
    buildCircle(gato->px[11], gato->py[11], gato->radius[2], vColorBlack, 1);

    /* OLHO DIREITO */
    buildCircle(gato->px[12], gato->py[12], gato->radius[3], vColorBlack, 1);

    /* CAUDA */
    glColor3fv(vColorBlack);
    glLineWidth(7);
    glBegin(GL_LINES);

        glVertex2d(gato->px[13], gato->py[13]);
        glVertex2d(gato->px[14], gato->py[14]);

    glEnd();

    /* PERNAS */
    glColor3fv(vColorGrey);
    glLineWidth(7);
    glBegin(GL_LINES);

        glVertex2d(gato->px[15], gato->py[15]);
        glVertex2d(gato->px[16], gato->py[16]);

        glVertex2d(gato->px[17], gato->py[17]);
        glVertex2d(gato->px[18], gato->py[18]);

        glVertex2d(gato->px[19], gato->py[19]);
        glVertex2d(gato->px[20], gato->py[20]);

        glVertex2d(gato->px[21], gato->py[21]);
        glVertex2d(gato->px[22], gato->py[22]);

    glEnd();

    /* PATAS */
    buildCircle(gato->px[23], gato->py[23], gato->radius[4], vColorBlack, 1);
    buildCircle(gato->px[24], gato->py[24], gato->radius[5], vColorBlack, 1);
    buildCircle(gato->px[25], gato->py[25], gato->radius[6], vColorBlack, 1);
    buildCircle(gato->px[26], gato->py[26], gato->radius[7], vColorBlack, 1);

    /* PELOS */
    glColor3fv(vColorBlack);
    glLineWidth(3);
    glBegin(GL_LINES);

        glVertex2d(gato->px[27], gato->py[27]);
        glVertex2d(gato->px[28], gato->py[28]);
        glVertex2d(gato->px[29], gato->py[29]);
        glVertex2d(gato->px[30], gato->py[30]);

        glVertex2d(gato->px[31], gato->py[31]);
        glVertex2d(gato->px[32], gato->py[32]);
        glVertex2d(gato->px[33], gato->py[33]);
        glVertex2d(gato->px[34], gato->py[34]);

    glEnd();

    glutPostRedisplay();
    glutSwapBuffers();
}

int followBall() {

    if (head != NULL && !checkOutOfBounds(gato->px[35], gato->py[35], gato->radius[8])) {

        /* ROTAÇÃO DO GATO DE ACORDO COM ÂNGULO DA BOLA DO INÍCIO DA FILA E O SENTIDO DA ROTAÇÃO */
        if (angleFlag && !scaleRotateFlag) {

            if (checkHitboxCollision(gato->px[35], gato->py[35], gato->radius[8])) {
                return 0;
            }

            rotateFlag = 1;
            stopFlag = 1;

            if (directionFlag) {
                direction = determineRotation(head->px, head->py, gato->px[gato->num_vertices - 1], gato->py[gato->num_vertices - 1]);
                directionFlag = 0;
            }

            if (direction == antiClockwiseFlag) theta = 0.001;
            else theta = -0.001;

            if (checkLinePointCollision(head->px, head->py, gato->px[36], gato->py[36], gato->px[37], gato->py[37])) {
                angleFlag = rotateFlag = 0;
                antiClockwiseFlag = directionFlag = 1;
            }
        }

        /* TRANSLAÇÃO DO GATO DE ACORDO COM A DISTÂNCIA DA BOLA DO INÍCIO DA FILA E A POSIÇÃO DO GATO */
        else if (!angleFlag && !scaleTranslateFlag) {
            translateFlag = 1;

            /* 1 - QUADRANTE */
            if (pos[0] < head->px && pos[1] < head->py) {

                if (xFlag == yFlag) {
                    pTr->newPx += 0.0001; pTr->newPy += 0.0001;
                    pTr->px = 0.0001; pTr->py = 0.0001;
                }

                if (checkPositionX(pTr->newPx)) {
                    pTr->newPy += 0.0001;
                    pTr->px = 0; pTr->py = 0.0001;
                    xFlag = 1;
                }

                if (checkPositionY(pTr->newPy)) {
                    pTr->newPx += 0.0001;
                    pTr->px = 0.0001; pTr->py = 0;
                    yFlag = 1;
                }
            }

            /* 2 - QUADRANTE */
            else if (pos[0] > head->px && pos[1] < head->py) {

                if (xFlag == yFlag) {
                    pTr->newPx -= 0.0001; pTr->newPy += 0.0001;
                    pTr->px = -0.0001; pTr->py = 0.0001;
                }

                if (checkPositionX(pTr->newPx)) {
                    pTr->newPy += 0.0001;
                    pTr->px = 0; pTr->py = 0.0001;
                    xFlag = 1;
                }

                if (checkPositionY(pTr->newPy)) {
                    pTr->newPx -= 0.0001;
                    pTr->px = -0.0001; pTr->py = 0;
                    yFlag = 1;
                }
            }

            /* 3 - QUADRANTE */
            else if (pos[0] > head->px && pos[1] > head->py) {

                if (xFlag == yFlag) {
                    pTr->newPx -= 0.0001; pTr->newPy -= 0.0001;
                    pTr->px = -0.0001; pTr->py = -0.0001;
                }

                if (checkPositionX(pTr->newPx)) {
                    pTr->newPy -= 0.0001;
                    pTr->px = 0; pTr->py = -0.0001;
                    xFlag = 1;
                }

                if (checkPositionY(pTr->newPy)) {
                    pTr->newPx -= 0.0001;
                    pTr->px = -0.0001; pTr->py = 0;
                    yFlag = 1;
                }
            }

            /* 4 - QUADRANTE */
            else if (pos[0] < head->px && pos[1] > head->py) {

                if (xFlag == yFlag) {
                    pTr->newPx += 0.0001; pTr->newPy -= 0.0001;
                    pTr->px = 0.0001; pTr->py = -0.0001;
                }

                if (checkPositionX(pTr->newPx)) {
                    pTr->newPy -= 0.0001;
                    pTr->px = 0; pTr->py = -0.0001;
                    xFlag = 1;
                }

                if (checkPositionY(pTr->newPy)) {
                    pTr->newPx += 0.0001;
                    pTr->px = 0.0001; pTr->py = 0;
                    yFlag = 1;
                }
            }

            if (checkHitboxCollision(gato->px[35], gato->py[35], gato->radius[8])) {
                pos[0] = pTr->newPx, pos[1] = pTr->newPy;
                angleFlag = 1;
                xFlag = yFlag = 0;
            }
        }
    }
    else if (stopFlag) {
        printf("Fila vazia ou gato fora do limite da borda.\n");
        stopFlag = 0;
    }
}

void display() {

    glClearColor(1.0, 1.0, 1.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    buildBall();
    buildCat();
    followBall();

    scaleRotateFlag = 0;
    scaleTranslateFlag = 0;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case '+':
        case '-':

            scaleFactor = 1;

            if (key == '+' && limit < MAX) {
                scaleFactor += 0.01;
                limit++;
            }

            else if (key == '-' && limit > MIN) {
                scaleFactor -= 0.01;
                limit--;
            }

            scaleFlag = 1;
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        float px = 2 * (x / (float) WIDTH) - 1;
        float py = (2 * ((y / (float) HEIGHT)) - 1) * -1;

        if (!checkOutOfBounds(px, py, 0.15)) {
            addNode(px, py);
            ballCount++;
        }
        else {
            printf("Bolinha fora do limite da borda.\n");
        }
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    gato = initCat(gato);
    pTr = initTranslation(pTr);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Gato - Transformações Geométricas 2D");

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
 }
