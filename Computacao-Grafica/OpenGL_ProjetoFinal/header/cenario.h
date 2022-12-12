/*
 *   UNIFESP SJC
 *
 *   COMPUTACAOO GRAFICA
 *   OPENGL - CENARIO
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED

#include "paleteCores.h"
#include "fractal.h"

#define SLICES  10
#define STACKS  10

float alpha, theta;

float humanWidth = 9.5;
float roomSize = 40.0;
float wallSize = 1.0;
float matSize = 7.0;
float rackSize = 20.0;
float paintingSize = 6.0;
float windowSize = 15.0;

/* Declaracao da superficie quadrica */
GLUquadricObj *quad;

void initScenarioQuadrics() {

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);
}

/* Desenha todas as paredes da sala */
void drawWalls() {

    glColor3fv(whitesmoke.color);
    glBegin(GL_QUADS);

    if (!(alpha > 0.50 && alpha < 2.80) || theta > 1.30) {

        /* Parede direita */
        glVertex3f(roomSize + wallSize - 1.0, -humanWidth,      roomSize);
        glVertex3f(roomSize + wallSize - 1.0, -humanWidth,     -roomSize);
        glVertex3f(roomSize + wallSize - 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(roomSize + wallSize - 1.0,  humanWidth * 3,  roomSize);
    }

    if (!(alpha > 2.15 && alpha < 4.40) || theta > 1.30) {

        /* Parede traseira */
        glVertex3f( roomSize + wallSize - 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,     -roomSize);
        glVertex3f( roomSize + wallSize - 1.0, -humanWidth,     -roomSize);
    }

    if (!(alpha > 3.70 && alpha < 5.90) || theta > 1.30) {

        /* Parede esquerda */
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,     -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,      roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3,  roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3, -roomSize);
    }

    if (!(alpha > 5.25 || alpha < 1.20) || theta > 1.30) {

        /* Parede frontal */
        glVertex3f( roomSize + wallSize - 1.0,  humanWidth * 3, roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3, roomSize);
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,     roomSize);
        glVertex3f( roomSize + wallSize - 1.0, -humanWidth,     roomSize);
    }

    glEnd();
}

/* Desenha chao da sala */
void drawFloor() {

    glColor3fv(saddlebrown.color);
    glBegin(GL_QUADS);

        glVertex3f(-roomSize, -humanWidth,  roomSize);
        glVertex3f( roomSize, -humanWidth,  roomSize);
        glVertex3f( roomSize, -humanWidth, -roomSize);
        glVertex3f(-roomSize, -humanWidth, -roomSize);

    glEnd();
}

void drawSofa() {

    glColor3fv(maroon.color);
    glPushMatrix();

        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(0.5, 0.6, 1.0);
        glTranslatef(0.0, -roomSize / 6.5, 0.25);

        glPushMatrix();

            glScalef(19.5, 4.8, 1.0);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glTranslatef(0.0, roomSize - 2, 0.0);

            /* Parte traseira do sofa */
            glutSolidCube(4.0);

        glPopMatrix();

        glPushMatrix();

            glScalef(1.0, 1.3, 1.0);
            glTranslatef(-roomSize + 5.1, -2.3, -roomSize + 9);

            /* Braco esquerdo do sofa */
            glutSolidCube(10.0);

            glTranslatef(roomSize * 1.73, 0.0, 0.0);

            /* Braco direito do sofa */
            glutSolidCube(10.0);

        glPopMatrix();

        glPushMatrix();

            glScalef(5.9, 0.8, 1.0);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glTranslatef(0.0, roomSize / 1.3, -6.5);

            /* Assento do sofa */
            glutSolidCube(10);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha rack para sala */
void drawRack() {

    glPushMatrix();

        glRotatef(90, 0.0, 1.0, 0.0);

        glBegin(GL_QUADS);

            glColor3fv(sienna.color);

            /* Parte traseira do rack */
            glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize - 0.5);
            glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize - 0.5);
            glVertex3f(-rackSize - wallSize + 1.0, -humanWidth,       roomSize - 0.5);
            glVertex3f( rackSize + wallSize - 1.0, -humanWidth,       roomSize - 0.5);

            /* Parte esquerda do rack */
            glVertex3f(-rackSize - wallSize + 1.0, -humanWidth,       roomSize - 5.0);
            glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize - 5.0);
            glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
            glVertex3f(-rackSize - wallSize + 1.0, -humanWidth,       roomSize);

            /* Parte direita do rack */
            glVertex3f(rackSize + wallSize - 1.0, -humanWidth,         roomSize - 5.0);
            glVertex3f(rackSize + wallSize - 1.0, -humanWidth,         roomSize);
            glVertex3f(rackSize + wallSize - 1.0,  humanWidth * 0.5,   roomSize);
            glVertex3f(rackSize + wallSize - 1.0,  humanWidth * 0.5,   roomSize - 5.0);

            /* Parte superior do rack */
            glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
            glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize);
            glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize - 5);
            glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize - 5);

        glEnd();

        glColor3fv(oldlace.color);
        glPushMatrix();

            glScalef(0.3, 1.25, 1.0);
            glTranslatef(-rackSize * 2.30, -1.9, -5.0);

            glBegin(GL_QUADS);

                /* Parte frontal esquerdo do rack */
                glVertex3f( rackSize + wallSize - 1.0, -humanWidth * 0.6, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0, -humanWidth * 0.6, roomSize);

            glEnd();

        glPopMatrix();

        glPushMatrix();

            glScalef(0.3, 1.25, 1.0);
            glTranslatef(rackSize * 2.30, -1.9, -5.0);

            glBegin(GL_QUADS);

                /* Parte frontal direito do rack */
                glVertex3f( rackSize + wallSize - 1.0, -humanWidth * 0.6, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0, -humanWidth * 0.6, roomSize);

            glEnd();

        glPopMatrix();

        glPushMatrix();

            glScalef(0.39, 0.6, 1.0);
            glTranslatef(0.0, -10.0, -5.0);

            glBegin(GL_QUADS);

                /* Parte frontal central do rack */
                glVertex3f( rackSize + wallSize - 1.0, -humanWidth * 0.6, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.6, roomSize);
                glVertex3f(-rackSize - wallSize + 1.0, -humanWidth * 0.6, roomSize);

            glEnd();

        glPopMatrix();

        glPushMatrix();

            glScalef(0.95, 0.6, 1.0);
            glTranslatef(0.0, -9.5, -0.5);

            glBegin(GL_QUADS);

                /* Parte frontal superior do rack */
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize - 4.5);
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize - 4.5);

            glEnd();

        glPopMatrix();

    glPopMatrix();

    glPushMatrix();

        glColor3fv(sienna.color);
        glScalef(0.5, 1.0, 1.0);
        glPushMatrix();

            glTranslatef(roomSize * 1.75, 1.0, -rackSize / 1.5);

            /* Desenha puxador esquerdo */
            gluSphere(quad, 0.75, SLICES, STACKS);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(roomSize * 1.75, 1.0, rackSize / 1.5);

            /* Desenha puxador direito */
            gluSphere(quad, 0.75, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha movel */
void drawStool() {

    glColor3fv(oldlace.color);

    glPushMatrix();

        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(1.5, 1.0, 1.25);

        glPushMatrix();

            glTranslatef(-roomSize / 2, -4.0, -roomSize / 1.5);

            /* Desenha banco esquerdo */
            glutSolidCube(10);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(roomSize / 2, -4.0, -roomSize / 1.5);

            /* Desenha banco direito */
            glutSolidCube(10);

        glPopMatrix();

    glPopMatrix();
}

void drawWindow() {

    if (!(alpha > 2.15 && alpha < 4.40) || theta > 1.30) {

        glPushMatrix();

            glPushMatrix();

                glTranslatef(0.0, windowSize / 2, 0.5);

                glBegin(GL_QUADS);

                    glColor3fv(lightcyan.color);

                    /* Desenha janela */
                    glVertex3f( windowSize + wallSize - 1.0,  humanWidth * 1.5, -roomSize);
                    glVertex3f(-windowSize - wallSize + 1.0,  humanWidth * 1.5, -roomSize);
                    glVertex3f(-windowSize - wallSize + 1.0, -humanWidth,       -roomSize);
                    glVertex3f( windowSize + wallSize - 1.0, -humanWidth,       -roomSize);

                glEnd();

            glPopMatrix();

        glPopMatrix();
    }
}

/* Desenha tapete */
void drawMat() {

    glPushMatrix();

        glRotatef(-90, 0.0, 1.0, 0.0);

        glColor3fv(navy.color);
        glBegin(GL_QUADS);

            glVertex3f(-matSize, -humanWidth + 0.1,  matSize * 2);
            glVertex3f( matSize, -humanWidth + 0.1,  matSize * 2);
            glVertex3f( matSize, -humanWidth + 0.1, -matSize * 2);
            glVertex3f(-matSize, -humanWidth + 0.1, -matSize * 2);

        glEnd();

    glPopMatrix();
}

void drawTV() {

    if (!(alpha > 0.50 && alpha < 2.80) || theta > 1.30) {

        glPushMatrix();

            glRotatef(90, 0.0, 1.0, 0.0);

            glPushMatrix();

                glTranslatef(0.0, rackSize, -0.5);

                glBegin(GL_QUADS);

                    glColor3fv(sienna.color);

                    /* Desenha suporte da TV */
                    glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize);
                    glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
                    glVertex3f(-rackSize - wallSize + 1.0, -humanWidth,       roomSize);
                    glVertex3f( rackSize + wallSize - 1.0, -humanWidth,       roomSize);

                glEnd();

            glPopMatrix();

            glPushMatrix();

                glScalef(0.8, 0.8, 1.0);
                glTranslatef(0.0, rackSize * 1.20, -1.0);

                glBegin(GL_QUADS);

                    glColor3fv(black.color);

                    /* Desenha TV */
                    glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize);
                    glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
                    glVertex3f(-rackSize - wallSize + 1.0, -humanWidth,       roomSize);
                    glVertex3f( rackSize + wallSize - 1.0, -humanWidth,       roomSize);

                glEnd();

            glPopMatrix();

        glPopMatrix();
    }
}

void drawFlowerPot() {

    glPushMatrix();

        glTranslatef(-0.4, 0.0, -4.0);

        glPushMatrix();

            glColor3fv(maroon.color);

            glRotatef(90.0, 1.0, 0.0, 0.0);
            glScalef(1.5, 1.2, 1.0);
            glTranslatef(-roomSize / 1.85, -roomSize / 1.75, -4.0);

            /* Desenha pote de flor */
            gluCylinder(quad, 1.5, 1.4, 3.0, SLICES, STACKS);

            glColor3fv(saddlebrown.color);

            /* Desenha terra do pote */
            gluDisk(quad, 0, 1.5, SLICES, SLICES);

        glPopMatrix();

        glPushMatrix();

            glScalef(1.25, 1.25, 1.0);
            glTranslatef(-roomSize / 1.55, 4.0, -roomSize + 12.5);

            /* Desenha Arvore de Pitagoras (fractal) */
            buildPythagorasTree(7);

        glPopMatrix();

    glPopMatrix();
}

void drawPaintingFrame() {

    if (!(alpha > 3.70 && alpha < 5.90) || theta > 1.30) {

        glPushMatrix();

            glTranslatef(0.0, -2.0, 0.0);

            glPushMatrix();

                glScalef(0.25, 0.30, 1.0);
                glTranslatef(-roomSize * 3.75, roomSize * 1.5, 0.0);

                glBegin(GL_QUADS);

                    glColor3fv(sienna.color);

                    /* Desenha quadro de pintura */
                    glVertex3f(-paintingSize - wallSize + 1.0, -humanWidth,     -paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0, -humanWidth,      paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0,  humanWidth * 2,  paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0,  humanWidth * 2, -paintingSize);

                glEnd();

                glScalef(0.9, 1.25, 0.9);
                glTranslatef(0.0, 4.0, 0.0);

                glBegin(GL_QUADS);

                    glColor3fv(black.color);

                    /* Desenha borda de pintura */
                    glVertex3f(-paintingSize - wallSize + 1.0, -humanWidth, -paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0, -humanWidth,  paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0,  humanWidth,  paintingSize);
                    glVertex3f(-paintingSize - wallSize + 1.0,  humanWidth, -paintingSize);

                glEnd();

            glPopMatrix();

            glPushMatrix();

                glRotatef(-90, 0.0, 1.0, 0.0);
                glScalef(6.0, 6.0, 1.0);
                glTranslatef(0.0, 3.25, roomSize - 1.20);

                /* Desenha Triangulo de Sierpinski (fractal) */
                buildSierpinskiTriangle(2);

            glPopMatrix();

        glPopMatrix();
    }
}

/* Desenha todas as mobiliarias */
void drawFurniture() {

    drawSofa();
    drawRack();
    drawStool();
}

/* Desenha todos os objetos */
void drawObjects() {

    drawMat();
    drawTV();
    drawFlowerPot();
    drawPaintingFrame();
    drawWindow();
}

/* Desenha todo o cenario */
void drawScenario(float newAlpha, float newTheta) {

    alpha = newAlpha;
    theta = newTheta;

    drawWalls();
    drawFloor();
    drawFurniture();
    drawObjects();
}

#endif // CENARIO_H_INCLUDED
