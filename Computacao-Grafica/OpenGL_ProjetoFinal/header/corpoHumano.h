/*
 *   UNIFESP SJC
 *
 *   COMPUTACAO GRAFICA
 *   OPENGL - CORPO HUMANO 3D
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#ifndef CORPOHUMANO_H_INCLUDED
#define CORPOHUMANO_H_INCLUDED

#include "paleteCores.h"
#include "animacao.h"

#define SLICES  10
#define STACKS  10

typedef struct {

    float height, radius;

} Body_Structure;


/* Estruturas do corpo humano */
Body_Structure  torso =      {4.0, 2.0},    /*  Torso      */
                neck =       {1.0, 0.4},    /*  Pescoco    */
                head =       {1.5, 1.0},    /*  Cabeca     */
                eye =        {0.0, 0.3},    /*  Olho       */
                shoulder =   {0.0, 0.6},    /*  Ombro      */
                upperArm =   {3.5, 0.5},    /*  Braco      */
                elbow =      {0.0, 0.4},    /*  Cotovelo   */
                lowerArm =   {3.0, 0.4},    /*  Antebraco  */
                hand     =   {0.0, 0.5},    /*  Mao        */
                waist =      {3.5, 1.7},    /*  Cintura    */
                hip =        {0.0, 0.6},    /*  Quadril    */
                upperLeg =   {2.5, 0.6},    /*  Coxa       */
                knee =       {0.0, 0.5},    /*  Joelho     */
                lowerLeg =   {3.0, 0.5},    /*  Canela     */
                feet     =   {0.0, 0.8};    /*  Pe         */


/* Declaracao da superficie quadrica */
GLUquadricObj *quadHuman;

/* Inicializacao das quadricas */
void initBodyQuadrics() {

    quadHuman = gluNewQuadric();
    gluQuadricDrawStyle(quadHuman, GLU_FILL);
    gluQuadricNormals(quadHuman, GLU_SMOOTH);
}

/* Desenha torso */
void drawTorso() {

    glPushMatrix();

        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, torso.radius / 1.2, torso.radius, torso.height, SLICES, STACKS);

	glPopMatrix();
}

/* Desenha pescoco */
void drawNeck() {

    glPushMatrix();

        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluSphere(quadHuman, neck.radius, SLICES, STACKS);
        gluCylinder(quadHuman, neck.radius, neck.radius, neck.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha cabeca e olhos */
void drawHead() {

    glPushMatrix();

        glTranslatef(0.0, head.height, 0.0);

        /* Desenha cabeca */
        glPushMatrix();

            glScalef(1.0, 1.2, 1.0);
            gluSphere(quadHuman, head.radius, SLICES, STACKS);

        glPopMatrix();

        /* Cor dos Olhos */
        glColor3fv(black.color);

        /* Desenha olho esquerdo */
        glPushMatrix();

            glTranslatef(head.radius * 0.45, 0.0, head.radius - eye.radius);
            gluSphere(quadHuman, eye.radius, SLICES, STACKS);

        glPopMatrix();

        /* Desenha olho direito */
        glPushMatrix();

            glTranslatef(-head.radius * 0.45, 0.0, head.radius - eye.radius);
            gluSphere(quadHuman, eye.radius, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha ombro */
void drawShoulder() {

    gluSphere(quadHuman, shoulder.radius, SLICES, STACKS);
}

/* Desenha braco */
void drawUpperArm() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, upperArm.radius, elbow.radius, upperArm.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha cotovelo */
void drawElbow() {

    gluSphere(quadHuman, elbow.radius, SLICES, STACKS);
}

/* Desenha antebraco */
void drawLowerArm() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, lowerArm.radius, lowerArm.radius, lowerArm.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha mao */
void drawHand() {

    gluSphere(quadHuman, hand.radius, SLICES, STACKS);
}

/* Desenha cintura */
void drawWaist() {

    glPushMatrix();

        glTranslatef(0.0, - (torso.height * 0.7), 0.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, waist.radius / 1.2, waist.radius, waist.height * 0.8, SLICES, STACKS);

	glPopMatrix();
}

/* Desenha quadril */
void drawHip() {

    gluSphere(quadHuman, hip.radius, SLICES, STACKS);
}

/* Desenha coxa */
void drawUpperLeg() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, upperLeg.radius, upperLeg.radius - 0.1, upperLeg.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha joelho */
void drawKnee() {

    gluSphere(quadHuman, knee.radius, SLICES, STACKS);
}

/* Desenha canela */
void drawLowerLeg() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quadHuman, lowerLeg.radius, lowerLeg.radius - 0.1, lowerLeg.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha pe */
void drawFeet() {

    glPushMatrix();

        glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(0.5, 1.0, 1.5);
        gluSphere(quadHuman, feet.radius, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha corpo humano */
void drawHuman() {

    glPushMatrix();

        glTranslatef(humanBodyPosition.current[0], humanBodyPosition.current[1], humanBodyPosition.current[2]);
        glRotatef(humanBodyRot.rotation[0], 1.0, 0.0, 0.0);
        glRotatef(humanBodyRot.rotation[1], 0.0, 1.0, 0.0);
        glRotatef(humanBodyRot.rotation[2], 0.0, 0.0, 1.0);

        glPushMatrix();

            /* Define cor da camisa */
            glColor3fv(indianred.color);

            glRotatef(torsoJoint.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(torsoJoint.rotation[1], 0.0, 1.0, 0.0);
            glRotatef(torsoJoint.rotation[2], 0.0, 0.0, 1.0);

            drawTorso();

            glTranslatef(0.0, torso.height, 0.0);

            glPushMatrix();

                glRotatef(-90, 1.0, 0.0, 0.0);
                gluDisk(quadHuman, 0, torso.radius, SLICES, SLICES);

            glPopMatrix();

            /* Define cor da cabeca e do pescoco */
            glColor3fv(bisque.color);

            glPushMatrix();

                glRotatef(neckJoint.rotation[0], 1.0, 0.0, 0.0);
                glRotatef(neckJoint.rotation[1], 0.0, 1.0, 0.0);
                glRotatef(neckJoint.rotation[2], 0.0, 0.0, 1.0);

                drawNeck();
                drawHead();

            glPopMatrix();

            /* Define cor do braco esquerdo */
            glColor3fv(bisque.color);

            glPushMatrix();

                glTranslatef(-torso.radius, -shoulder.radius, 0.0);
                glRotatef(leftShoulderJoint.rotation[0], 1.0, 0.0, 0.0);
                glRotatef(leftShoulderJoint.rotation[2], 0.0, 0.0, 1.0);

                drawShoulder();
                drawUpperArm();

                glTranslatef(0.0, - (upperArm.height + lowerArm.radius * 0.3), 0.0);
                glRotatef(leftElbowJoint.rotation[0], 1.0, 0.0, 0.0);
                glRotatef(leftElbowJoint.rotation[2], 0.0, 0.0, 1.0);

                drawElbow();
                drawLowerArm();

                /* Desenha mao esquerda */
                glTranslatef(0.0, -lowerArm.height, 0.0);
                drawHand();

            glPopMatrix();

            /* Define cor do braco direito */
            glColor3fv(bisque.color);

            glPushMatrix();

                glTranslatef(torso.radius, -shoulder.radius, 0.0);
                glRotatef(rightShoulderJoint.rotation[0], 1.0, 0.0, 0.0);
                glRotatef(rightShoulderJoint.rotation[2], 0.0, 0.0, 1.0);

                drawShoulder();
                drawUpperArm();

                glTranslatef(0.0, - (upperArm.height + lowerArm.radius * 0.3), 0.0);
                glRotatef(rightElbowJoint.rotation[0], 1.0, 0.0, 0.0);
                glRotatef(rightElbowJoint.rotation[2], 0.0, 0.0, 1.0);

                drawElbow();
                drawLowerArm();

                /* Desenha mao direita */
                glTranslatef(0.0, -lowerArm.height, 0.0);
                drawHand();

            glPopMatrix();

        glPopMatrix();

        /* Define cor da calca */
        glColor3fv(navy.color);

        glRotatef(waistJoint.rotation[0], 1.0, 0.0, 0.0);
        glRotatef(waistJoint.rotation[1], 0.0, 1.0, 0.0);
        glRotatef(waistJoint.rotation[2], 0.0, 0.0, 1.0);
        glTranslatef(waistPosition.current[0], waistPosition.current[1], waistPosition.current[2]);

        drawWaist();

        glPushMatrix();

            glTranslated(-waist.radius * 0.5, -waist.height * 0.7, 0.0);
            glTranslatef(0.0, leftLegPosition.current[1], 0.0);
            glRotatef(leftHipJoint.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(leftHipJoint.rotation[2], 0.0, 0.0, 1.0);

            drawHip();
            drawUpperLeg();

            glTranslatef(0.0, - (upperLeg.height + lowerLeg.radius * 0.3), 0.0);
            glRotatef(leftKneeJoint.rotation[0], 1.0, 0.0, 0.0);

            drawKnee();
            drawLowerLeg();

            /* Define cor do sapato esquerdo */
            glColor3fv(black.color);

            glTranslatef(0.0, - lowerLeg.height, lowerLeg.radius + 0.2);
            drawFeet();

        glPopMatrix();

        glColor3fv(navy.color);

        glPushMatrix();

            glTranslated(waist.radius * 0.5, -waist.height * 0.7, 0.0);
            glTranslatef(0.0, rightLegPosition.current[1], 0.0);
            glRotatef(rightHipJoint.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(rightHipJoint.rotation[2], 0.0, 0.0, 1.0);

            drawHip();
            drawUpperLeg();

            glTranslatef(0.0, - (upperLeg.height + lowerLeg.radius * 0.3), 0.0);
            glRotatef(rightKneeJoint.rotation[0], 1.0, 0.0, 0.0);

            drawKnee();
            drawLowerLeg();

            /* Define cor do sapato direito */
            glColor3fv(black.color);

            glTranslatef(0.0, - lowerLeg.height, lowerLeg.radius + 0.2);
            drawFeet();

        glPopMatrix();

    glPopMatrix();
}

#endif // CORPOHUMANO_H_INCLUDED
