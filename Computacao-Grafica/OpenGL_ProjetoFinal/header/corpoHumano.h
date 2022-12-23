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
                upperArm =   {3.0, 0.5},    /*  Braco      */
                elbow =      {0.0, 0.4},    /*  Cotovelo   */
                lowerArm =   {2.5, 0.5},    /*  Antebraco  */
                hand     =   {0.0, 0.5},    /*  Mao        */
                waist =      {4.0, 1.6},    /*  Cintura    */
                hip =        {0.0, 0.6},    /*  Quadril    */
                upperLeg =   {3.0, 0.6},    /*  Coxa       */
                knee =       {0.0, 0.5},    /*  Joelho     */
                lowerLeg =   {2.5, 0.6},    /*  Canela     */
                feet     =   {0.0, 0.8};    /*  Pe         */

/* Juntas (articulacoes) do corpo humano */
Animation   neckJoint =           {{0.0, 0.0, 0.0}, {20.0, 20.0, 15.0}, {20.0, 20.0, 15.0}},  /*  Juntas do pescoco            */
            leftShoulderJoint =   {{0.0, 0.0, 0.0}, {170.0, 0.0, 90.0}, {60.0, 0.0, 0.0}},    /*  Juntas do ombro esquerdo     */
            rightShoulderJoint =  {{0.0, 0.0, 0.0}, {170.0, 0.0, 0.0},  {60.0, 0.0, 90.0}},   /*  Juntas do ombro direito      */
            leftElbowJoint =      {{0.0, 0.0, 0.0}, {120.0, 0.0, 0.0},  {0.0, 0.0, 60.0}},    /*  Juntas do cotovelo esquerdo  */
            rightElbowJoint =     {{0.0, 0.0, 0.0}, {120.0, 0.0, 60.0}, {0.0, 0.0, 0.0}},     /*  Juntas do cotovelo direito   */
            leftHipJoint =        {{0.0, 0.0, 0.0}, {60.0, 0.0, 30.0},  {60.0, 0.0, 30.0}},   /*  Juntas do quadril esquerdo   */
            rightHipJoint =       {{0.0, 0.0, 0.0}, {60.0, 0.0, 30.0},  {60.0, 0.0, 30.0}},   /*  Juntas do quadril direito    */
            leftKneeJoint =       {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},    {55.0, 0.0, 0.0}},    /*  Juntas do joelho esquerdo    */
            rightKneeJoint =      {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},    {55.0, 0.0, 0.0}};    /*  Juntas do joelho direito     */


/* Declaracao da superficie quadrica */
GLUquadricObj *quad;

/* Inicializacao das quadricas */
void initBodyQuadrics() {

    quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricNormals(quad, GLU_SMOOTH);
}

/* Desenha torso */
void drawTorso() {

    glPushMatrix();

        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, torso.radius / 1.2, torso.radius, torso.height, SLICES, STACKS);

	glPopMatrix();
}

/* Desenha pescoco */
void drawNeck() {

    glPushMatrix();

        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluSphere(quad, neck.radius, SLICES, STACKS);
        gluCylinder(quad, neck.radius, neck.radius, neck.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha cabeca e olhos */
void drawHead() {

    glPushMatrix();

        glTranslatef(0.0, head.height, 0.0);

        /* Desenha cabeca */
        glPushMatrix();

            glScalef(1.05, 1.2, 1.0);
            gluSphere(quad, head.radius, SLICES, STACKS);

        glPopMatrix();

        /* Cor dos Olhos */
        glColor3fv(black.color);

        /* Desenha olho esquerdo */
        glPushMatrix();

            glTranslatef(head.radius * 0.5, 0.0, head.radius - eye.radius);
            gluSphere(quad, eye.radius, SLICES, STACKS);

        glPopMatrix();

        /* Desenha olho direito */
        glPushMatrix();

            glTranslatef(-head.radius * 0.5, 0.0, head.radius - eye.radius);
            gluSphere(quad, eye.radius, SLICES, STACKS);

        glPopMatrix();

    glPopMatrix();
}

/* Desenha ombro */
void drawShoulder() {

    gluSphere(quad, shoulder.radius, SLICES, STACKS);
}

/* Desenha braco */
void drawUpperArm() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, upperArm.radius, upperArm.radius - 0.1, upperArm.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha cotovelo */
void drawElbow() {

    gluSphere(quad, elbow.radius, SLICES, STACKS);
}

/* Desenha antebraco */
void drawLowerArm() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, lowerArm.radius - 0.1, lowerArm.radius - 0.1, lowerArm.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha mao */
void drawHand() {

    gluSphere(quad, hand.radius, SLICES, STACKS);
}

/* Desenha cintura */
void drawWaist() {

    glPushMatrix();

        glTranslatef(0.0, - (torso.height * 0.8), 0.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, waist.radius / 1.2, waist.radius, waist.height * 0.8, SLICES, STACKS);

	glPopMatrix();
}

/* Desenha quadril */
void drawHip() {

    gluSphere(quad, hip.radius, SLICES, STACKS);
}

/* Desenha coxa */
void drawUpperLeg() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, upperLeg.radius, upperLeg.radius - 0.1, upperLeg.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha joelho */
void drawKnee() {

    gluSphere(quad, knee.radius, SLICES, STACKS);
}

/* Desenha canela */
void drawLowerLeg() {

    glPushMatrix();

        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, lowerLeg.radius - 0.1, lowerLeg.radius - 0.2, lowerLeg.height, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha pe */
void drawFeet() {

    glPushMatrix();

        glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(0.5, 1.0, 1.5);
        gluSphere(quad, feet.radius, SLICES, STACKS);

    glPopMatrix();
}

/* Desenha corpo humano */
void drawHuman() {

    glPushMatrix();

        glPushMatrix();

            /* Define cor da camisa */
            glColor3fv(indianred.color);
            drawTorso();

            glTranslatef(0.0, torso.height, 0.0);

            glPushMatrix();

                glRotatef(-90, 1.0, 0.0, 0.0);
                gluDisk(quad, 0, torso.radius, SLICES, SLICES);

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

                glTranslatef(0.0, - (upperArm.height + lowerArm.radius * 0.25), 0.0);
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

                glTranslatef(0.0, - (upperArm.height + lowerArm.radius * 0.25), 0.0);
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
        drawWaist();

        /* Define cor da perna esquerda */
        glColor3fv(bisque.color);

        glPushMatrix();

            glTranslated(-waist.radius * 0.5, -waist.height * 0.85, 0.0);
            glRotatef(leftHipJoint.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(leftHipJoint.rotation[2], 0.0, 0.0, 1.0);

            drawHip();
            drawUpperLeg();

            glTranslatef(0.0, - (upperLeg.height + lowerLeg.radius * 0.25), 0.0);
            glRotatef(leftKneeJoint.rotation[0], 1.0, 0.0, 0.0);

            drawKnee();
            drawLowerLeg();

            /* Define cor do sapato esquerdo */
            glColor3fv(black.color);

            glTranslatef(0.0, - lowerLeg.height, lowerLeg.radius + 0.1);
            drawFeet();

        glPopMatrix();

        /* Define cor da perna direita */
        glColor3fv(bisque.color);

        glPushMatrix();

            glTranslated(waist.radius * 0.5, -waist.height * 0.85, 0.0);
            glRotatef(rightHipJoint.rotation[0], 1.0, 0.0, 0.0);
            glRotatef(rightHipJoint.rotation[2], 0.0, 0.0, 1.0);

            drawHip();
            drawUpperLeg();

            glTranslatef(0.0, - (upperLeg.height + lowerLeg.radius * 0.25), 0.0);
            glRotatef(rightKneeJoint.rotation[0], 1.0, 0.0, 0.0);

            drawKnee();
            drawLowerLeg();

            /* Define cor do sapato direito */
            glColor3fv(black.color);

            glTranslatef(0.0, - lowerLeg.height, lowerLeg.radius + 0.1);
            drawFeet();

        glPopMatrix();

    glPopMatrix();
}

#endif // CORPOHUMANO_H_INCLUDED
