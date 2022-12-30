/*
 *   UNIFESP SJC
 *
 *   COMPUTACAO GRAFICA
 *   OPENGL - CENARIO
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED

#include "fractal.h"
#include "animacao.h"
#include "paleteCores.h"
#include "textura.h"

#define SLICES  10
#define STACKS  10

#define CAMERA_RIGHT_DIRECTION  (cameraAlpha > 0.50 && cameraAlpha < 2.80) || cameraTheta > 1.15
#define CAMERA_BACK_DIRECTION   (cameraAlpha > 2.15 && cameraAlpha < 4.40) || cameraTheta > 1.15
#define CAMERA_LEFT_DIRECTION   (cameraAlpha > 3.70 && cameraAlpha < 5.90) || cameraTheta > 1.15
#define CAMERA_FRONT_DIRECTION  (cameraAlpha > 5.25 || cameraAlpha < 1.20) || cameraTheta > 1.15

float cameraAlpha, cameraTheta;
float roomSize      = 40.0;
float rackSize      = 20.0;
float doorSize      = 10.0;
float humanWidth    = 10.0;
float windowSize    = 8.0;
float matSize       = 7.0;
float paintingSize  = 6.0;
float shelfSize     = 5.0;
float wallSize      = 1.0;

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

    if (!CAMERA_RIGHT_DIRECTION) {

        /* Parede direita */
        glVertex3f(roomSize + wallSize - 1.0, -humanWidth,      roomSize);
        glVertex3f(roomSize + wallSize - 1.0, -humanWidth,     -roomSize);
        glVertex3f(roomSize + wallSize - 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(roomSize + wallSize - 1.0,  humanWidth * 3,  roomSize);
    }

    if (!CAMERA_BACK_DIRECTION) {

        /* Parede traseira */
        glVertex3f( roomSize + wallSize - 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3, -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,     -roomSize);
        glVertex3f( roomSize + wallSize - 1.0, -humanWidth,     -roomSize);
    }

    if (!CAMERA_LEFT_DIRECTION) {

        /* Parede esquerda */
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,     -roomSize);
        glVertex3f(-roomSize - wallSize + 1.0, -humanWidth,      roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3,  roomSize);
        glVertex3f(-roomSize - wallSize + 1.0,  humanWidth * 3, -roomSize);
    }

    if (!CAMERA_FRONT_DIRECTION) {

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

    glPushMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);

        glBegin(GL_QUADS);

            glVertex3f(-roomSize, -humanWidth,  roomSize);
            glVertex3f( roomSize, -humanWidth,  roomSize);
            glVertex3f( roomSize, -humanWidth, -roomSize);
            glVertex3f(-roomSize, -humanWidth, -roomSize);

        glEnd();

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
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
void drawTVRack() {

    glPushMatrix();

        glScalef(0.8, 0.8, 1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glTranslatef(0, -2.5, 10.0);

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
            glTranslatef(-rackSize * 2.30, -2.0, -5.0);

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
            glTranslatef(rackSize * 2.30, -2.0, -5.0);

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
            glTranslatef(0.0, -11.0, -5.0);

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
            glTranslatef(0.0, -10.5, -0.5);

            glBegin(GL_QUADS);

                /* Parte frontal superior do rack */
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize);
                glVertex3f( rackSize + wallSize - 1.0,  humanWidth * 0.5, roomSize - 4.5);
                glVertex3f(-rackSize - wallSize + 1.0,  humanWidth * 0.5, roomSize - 4.5);

            glEnd();

        glPopMatrix();

    glPopMatrix();

    /* Desenha Puxadores */
    glPushMatrix();

        glColor3fv(sienna.color);
        glScalef(0.5, 1.0, 1.0);
        glTranslatef(roomSize * 1.8, -1.0, 0.0);

        glPushMatrix();

            glTranslatef(0.0, 0.0, -rackSize / 1.5);

            /* Desenha puxador esquerdo */
            gluSphere(quad, 0.75, SLICES, STACKS);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(0.0, 0.0, rackSize / 1.5);

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

            glTranslatef(-roomSize / 2, -4.5, -roomSize / 1.5);

            /* Desenha banco esquerdo */
            glutSolidCube(10);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(roomSize / 2, -4.5, -roomSize / 1.5);

            /* Desenha banco direito */
            glutSolidCube(10);

        glPopMatrix();

    glPopMatrix();
}

void buildWindow() {

    glBegin(GL_QUADS);

        glVertex3f( windowSize + wallSize - 1.0,  windowSize, -roomSize);
        glVertex3f(-windowSize - wallSize + 1.0,  windowSize, -roomSize);
        glVertex3f(-windowSize - wallSize + 1.0, -windowSize, -roomSize);
        glVertex3f( windowSize + wallSize - 1.0, -windowSize, -roomSize);

    glEnd();
}

void drawWindow() {

    if (!CAMERA_BACK_DIRECTION) {

        glPushMatrix();

            glScalef(0.9, 0.9, 1.0);
            glTranslatef(-windowSize + 1.5, windowSize * 1.5, 0.5);

            glPushMatrix();

                glScalef(1.01, 1.0, 1.0);
                glColor3fv(black.color);

                /* Desenha janela esquerda */
                buildWindow();

                glPushMatrix();

                    glTranslatef(windowSize * 2.30, 0.0, 0.0);

                    /* Desenha janela direita */
                    buildWindow();

                glPopMatrix();

            glPopMatrix();

            /* Desenha divisoria vertical entre janelas */
            glPushMatrix();

                glScalef(0.15, 1.0, 1.0);
                glColor3fv(sienna.color);

                glPushMatrix();

                    glTranslatef(-roomSize * 1.55, 0.0, 0.0);
                    buildWindow();

                glPopMatrix();

                glPushMatrix();

                    glTranslatef(roomSize * 1.55, 0.0, 0.0);
                    buildWindow();

                glPopMatrix();

                glPushMatrix();

                    glTranslatef(roomSize * 4.65, 0.0, 0.0);
                    buildWindow();

                glPopMatrix();

                glScalef(0.5, 1.0, 1.0);
                glTranslatef(0.0, 0.0, 0.25);

                glPushMatrix();

                    buildWindow();

                    glTranslatef(roomSize * 6.25, 0.0, 0.0);
                    buildWindow();

                glPopMatrix();

            glPopMatrix();

            /* Desenha divisoria horizontal entre janelas */
            glPushMatrix();

                glRotatef(90, 0.0, 0.0, 1.0);
                glScalef(0.15, 2.475, 1.0);

                glPushMatrix();

                    glTranslatef(roomSize * 1.53, -3.75, 0.0);
                    buildWindow();

                glPopMatrix();

                glPushMatrix();

                    glTranslatef(-roomSize * 1.53, -3.75, 0.0);
                    buildWindow();

                glPopMatrix();

                glScalef(0.5, 1.0, 1.0);

                glPushMatrix();

                    glTranslatef(-1.0, -3.75, 0.30);
                    buildWindow();

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();
    }
}

void drawDoor() {

    if (!CAMERA_FRONT_DIRECTION) {

        glPushMatrix();

            glScalef(0.8, 0.8, 1.0);
            glTranslatef(0.0, -2.5, 0.0);

            glBegin(GL_QUADS);

                glColor3fv(sienna.color);

                /* Desenha porta */
                glVertex3f( doorSize + wallSize - 1.0,  humanWidth * 2.0, roomSize - 0.4);
                glVertex3f(-doorSize - wallSize + 1.0,  humanWidth * 2.0, roomSize - 0.4);
                glVertex3f(-doorSize - wallSize + 1.0, -humanWidth,       roomSize - 0.4);
                glVertex3f( doorSize + wallSize - 1.0, -humanWidth,       roomSize - 0.4);

            glEnd();

            glPushMatrix();

                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(0.5, 1.0, 1.0);
                glTranslatef(-roomSize * 1.95, doorSize / 2, 5.5);

                glColor3fv(burlywood.color);

                /* Desenha macaneta */
                gluSphere(quad, 1.0, SLICES, STACKS);

            glPopMatrix();

        glPopMatrix();
   }
}

/* Desenha tapete */
void drawMat() {

    glPushMatrix();

        glTranslatef(1.5, 0.0, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);

        glColor3fv(royalblue.color);
        glBegin(GL_QUADS);

            glVertex3f(-matSize, -humanWidth + 0.1,  matSize * 2);
            glVertex3f( matSize, -humanWidth + 0.1,  matSize * 2);
            glVertex3f( matSize, -humanWidth + 0.1, -matSize * 2);
            glVertex3f(-matSize, -humanWidth + 0.1, -matSize * 2);

        glEnd();

    glPopMatrix();
}

void drawTV() {

    if (!CAMERA_RIGHT_DIRECTION) {

        glPushMatrix();

            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(0.0, 2.0, 0.0);

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

/* Desenha controle remoto da TV */
void drawRemoteController() {

    glPushMatrix();

        glTranslatef(-roomSize + 8.0, 0.8, roomSize / 1.5);
        glRotatef(45, 0.0, 1.0, 0.0);

        glPushMatrix();

            glRotatef(90, 0.0, 0.0, 1.0);
            glScalef(0.25, 2.5, 1.0);
            glColor3fv(black.color);

            /* Desenha controle remoto da TV */
            glutSolidCube(2);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(2.0, 0.30, -0.5);
            glScalef(0.25, 0.10, 0.5);
            glColor3fv(red.color);

            /* Desenha botao de ligar/desligar */
            glutSolidCube(1);

        glPopMatrix();

        glPushMatrix();

            /* Desenha botoes extra */
            glTranslatef(1.0, 0.30, -0.5);
            glScalef(0.25, 0.10, 0.5);
            glColor3fv(dimgray.color);

            glutSolidCube(1);

            glTranslatef(0.0, 0.0, 2.0);
            glutSolidCube(1);

            glTranslatef(-3.0, 0.0, 0.0);
            glutSolidCube(1);

            glTranslatef(0.0, 0.0, -2.0);
            glutSolidCube(1);

        glPopMatrix();

        glPushMatrix();

            glTranslatef(-1.0, 0.2, 0.0);
            glRotatef(90, 0.0, 0.0, 1.0);
            glScalef(0.25, 1.0, 1.0);
            glColor3fv(dimgray.color);

            gluSphere(quad, 0.7, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha abajur de mesa */
void drawTableLamp() {

    glPushMatrix();

        glTranslatef(-roomSize + 6.0, 0.8, roomSize / 1.25);

        glPushMatrix();

            glRotatef(90, 0.0, 0.0, 1.0);
            glScalef(0.5, 1.0, 1.0);
            glColor3fv(black.color);

            /* Desenha base do abajur */
            gluSphere(quad, 1.0, SLICES, STACKS);

        glPopMatrix();

        glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, -5.3);

        glPushMatrix();

            /* Desenha suporte */
            gluCylinder(quad, 0.3, 0.3, 5.0, SLICES, STACKS);

            glTranslatef(0.0, 0.0, -0.5);
            glColor3fv(gold.color);

            /* Desenha lampada */
            gluSphere(quad, 0.6, SLICES, STACKS);

            glTranslatef(0.0, 0.0, -1.0);
            glColor3fv(whitesmoke.color);

            /* Desenha cupula */
            gluCylinder(quad, 1.0, 1.5, 2.5, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha caixa de som */
void drawSpeakers() {

    glPushMatrix();

        glScalef(0.8, 0.8, 1.0);
        glTranslatef(10, -2.5, 0.0);

        glPushMatrix();

            glColor3fv(dimgray.color);
            glScalef(1.25, 2.0, 1.0);
            glTranslatef(roomSize - 9.75, 4.0, 0.0);

            glPushMatrix();

                glTranslatef(0.0, 0.0, rackSize - 2.0);

                /* Desenha caixa de som esquerda */
                glutSolidCube(3);

            glPopMatrix();

            glPushMatrix();

                glTranslatef(0.0, 0.0, -rackSize + 2.0);

                /* Desenha caixa de som direita */
                glutSolidCube(3);

            glPopMatrix();

        glPopMatrix();

        glPushMatrix();

            glScalef(0.5, 1.0, 1.0);
            glColor3fv(silver.color);

            glPushMatrix();

                glTranslatef(roomSize * 1.80, rackSize / 2.15, rackSize - 2.0);

                /* Desenha speaker superior direito */
                gluSphere(quad, 1.0, SLICES, STACKS);

                glTranslatef(0.0, -2.5, 0.0);

                /* Desenha speaker inferior direito */
                gluSphere(quad, 1.2, SLICES, STACKS);

            glPopMatrix();

            glPushMatrix();

                glTranslatef(roomSize * 1.80, rackSize / 2.15, -rackSize + 2.0);

                /* Desenha speaker superior esquerdo */
                gluSphere(quad, 1.0, SLICES, STACKS);

                glTranslatef(0.0, -2.5, 0.0);

                /* Desenha speaker inferior esquerdo */
                gluSphere(quad, 1.2, SLICES, STACKS);

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

void drawFlowerPot() {

    glPushMatrix();

        glTranslatef(-0.8, -0.5, -3.0);

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

/* Desenha halteres (peso) */
void drawDumbbell() {

    glPushMatrix();

        glScalef(0.7, 0.7, 0.7);

        glPushMatrix();

            gluCylinder(quad, 0.4, 0.4, 3.0, SLICES, STACKS);

            glTranslatef(0.0, 0.0, -0.75);
            gluSphere(quad, 1.0, SLICES, STACKS);

            glTranslatef(0.0, 0.0, 3.75);
            gluSphere(quad, 1.0, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha rack para halteres */
void drawDumbbellRack() {

    glPushMatrix();

        glColor3fv(whitesmoke.color);
        glTranslatef(roomSize - 1.5, -3.75, roomSize - 10.0);

        glPushMatrix();

            glScalef(1.0, 5.0, 1.0);
            glutSolidCube(2.5);

        glPopMatrix();

        glPushMatrix();

            /* Desenha o suporte para os halteres */

            glTranslatef(-1.8, 4.0, 0.0);
            glScalef(1.0, 1.0, 2.5);
            glutSolidCube(1.0);

            glTranslatef(0.0, -4.0, 0.0);
            glutSolidCube(1.0);

            glTranslatef(0.0, -4.0, 0.0);
            glutSolidCube(1.0);

        glPopMatrix();

        glPushMatrix();

            /* Desenha haltere inferior */

            glColor3fv(darkgreen.color);
            glTranslatef(-2.0, -3.0, -1.0);
            drawDumbbell();

        glPopMatrix();

        glPushMatrix();

            glTranslatef(leftDumbbellPos.current[0], leftDumbbellPos.current[1], leftDumbbellPos.current[2]);
            glRotatef(leftDumbbellRot.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(leftDumbbellRot.rotation[1], 0.0, 1.0, 0.0);
            glRotatef(leftDumbbellRot.rotation[2], 0.0, 0.0, 1.0);

            glPushMatrix();

                glTranslatef(-2.0, 5.0, -1.0);
                /* Desenha haltere da mao esquerda */
                drawDumbbell();

            glPopMatrix();

        glPopMatrix();

        glPushMatrix();

            /* Desenha haltere da mao direita */
            glTranslatef(rightDumbbellPos.current[0], rightDumbbellPos.current[1], rightDumbbellPos.current[2]);
            glRotatef(rightDumbbellRot.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(rightDumbbellRot.rotation[1], 0.0, 1.0, 0.0);
            glRotatef(rightDumbbellRot.rotation[2], 0.0, 0.0, 1.0);

            glPushMatrix();

                glTranslatef(-2.0, 1.0, -1.0);

                /* Desenha haltere da mao direita */
                drawDumbbell();

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

/* Desenha todas as mobiliarias */
void drawFurniture() {

    drawDumbbellRack();
    drawSofa();
    drawTVRack();
    drawStool();
}

/* Desenha todos os objetos */
void drawObjects() {

    drawWindow();
    drawDoor();
    drawTV();
    drawRemoteController();
    drawMat();
    drawFlowerPot();
    drawSpeakers();
    drawTableLamp();
}

/* Desenha todo o cenario */
void drawScenario(float alpha, float theta) {

    cameraAlpha = alpha;
    cameraTheta = theta;

    drawWalls();
    drawFloor();
    drawFurniture();
    drawObjects();
}

#endif // CENARIO_H_INCLUDED
