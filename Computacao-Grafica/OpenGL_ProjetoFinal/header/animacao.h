/*
 *   UNIFESP SJC
 *
 *   COMPUTACAO GRAFICA
 *   OPENGL - ANIMACAO
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <stdlib.h>

#ifndef ANIMACAO_H_INCLUDED
#define ANIMACAO_H_INCLUDED

#define AXIS 3
#define NUM_JOINTS 9
#define STEP 0.1

float timer = 0.01;
int animationFinished = 0;
int newAnimation = 0;
int animationId = -1;

typedef struct {

    /* Coordenadas iniciais de rotacao 3D */
    float rotation[AXIS];

    /* Coordenadas limite para rotacao */
    float minRotation[AXIS];
    float maxRotation[AXIS];

} Animation;

typedef struct {

    /* Coordenadas de posicao */
    float current[AXIS];
    float init[AXIS];

} ObjectPosition;

typedef struct AnimationLst {

    int animationId;
    struct AnimationLst *next;

} AnimationLst;

/* Juntas (articulacoes) do corpo humano */
Animation   neckJoint =           {{0.0, 0.0, 0.0}, {20.0, 20.0, 20.0},  {20.0, 20.0, 20.0}},  /*  Juntas do pescoco            */
            leftShoulderJoint =   {{0.0, 0.0, 0.0}, {200.0, 0.0, 160.0}, {60.0, 0.0, 10.0}},   /*  Juntas do ombro esquerdo     */
            rightShoulderJoint =  {{0.0, 0.0, 0.0}, {200.0, 0.0, 10.0},  {60.0, 0.0, 160.0}},  /*  Juntas do ombro direito      */
            leftElbowJoint =      {{0.0, 0.0, 0.0}, {140.0, 0.0, 0.0},   {0.0, 0.0, 60.0}},    /*  Juntas do cotovelo esquerdo  */
            rightElbowJoint =     {{0.0, 0.0, 0.0}, {140.0, 0.0, 60.0},  {0.0, 0.0, 0.0}},     /*  Juntas do cotovelo direito   */
            leftHipJoint =        {{0.0, 0.0, 0.0}, {70.0, 0.0, 40.0},   {50.0, 0.0, 40.0}},   /*  Juntas do quadril esquerdo   */
            rightHipJoint =       {{0.0, 0.0, 0.0}, {70.0, 0.0, 40.0},   {50.0, 0.0, 40.0}},   /*  Juntas do quadril direito    */
            leftKneeJoint =       {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},     {140.0, 0.0, 0.0}},   /*  Juntas do joelho esquerdo    */
            rightKneeJoint =      {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},     {140.0, 0.0, 0.0}},   /*  Juntas do joelho direito     */
            torsoJoint =          {{0.0, 0.0, 0.0}},                                           /*  Juntas do torso              */
            waistJoint =          {{0.0, 0.0, 0.0}};                                           /*  Juntas do quadril            */


/* Definindo Rotacao e Posicao (inicial) dos halteres que serao utilizados durante o exercicio */
Animation   leftDumbbellRot  = {{0.0, 0.0, 0.0}},
            rightDumbbellRot = {{0.0, 0.0, 0.0}};


/* Posicao inicial do corpo humano e das estruturas do corpo */
ObjectPosition  humanBodyPosition   = {{0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}},
                leftLegPosition     = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
                rightLegPosition    = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

/* Posicao inicial e atual dos halteres */
ObjectPosition  leftDumbbellPos  = {{-2.0, 5.0, -1.0}, {-2.0, 5.0, -1.0}},
                rightDumbbellPos = {{-2.0, 1.0, -1.0}, {-2.0, 1.0, -1.0}};

/* Inicio da lista */
AnimationLst *headNode = NULL;

void inverseKinematics(int optAnimation, int resetFlag, int optUser);
void kinematics(int optAnimation, int resetFlag, int optUser);


void addNode() {

    AnimationLst *newAnimation = (AnimationLst*)malloc(sizeof(AnimationLst));
    newAnimation->animationId = animationId;
    newAnimation->next = NULL;

    if (headNode == NULL) headNode = newAnimation;
    else {

        AnimationLst *temp = headNode;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAnimation;
    }
}

void deleteFirstNode() {

    if (headNode == NULL) {
        printf("Lista vazia - Erro interno.");
        exit(1);
    }
    else {
        AnimationLst *temp = headNode;
        headNode = headNode->next;
        free(temp);
    }
}

void deleteList() {

    AnimationLst* current = headNode;
    AnimationLst* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    headNode = NULL;
}

void printList() {

    AnimationLst *temp = headNode;

    if (temp == NULL) printf("null");

    while (temp != NULL) {
        printf("%d -> ", temp->animationId);
        temp = temp->next;
    }
    printf("\n");
}

void leftLegExercise(int animationCycle) {

    timer += 0.01;

    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] < 30) leftShoulderJoint.rotation[0] += STEP * 0.6;
        if (leftShoulderJoint.rotation[2] < 6 && leftShoulderJoint.rotation[0] > 24) leftShoulderJoint.rotation[2] += STEP * 0.2;
        if (leftElbowJoint.rotation[0] > -12 && leftKneeJoint.rotation[0] < 50) leftElbowJoint.rotation[0] -= STEP * 0.3;
        if (leftHipJoint.rotation[0] < 30) leftHipJoint.rotation[0] += STEP;
        if (leftKneeJoint.rotation[0] < 106) leftKneeJoint.rotation[0] += STEP * 1.5;
    }

    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] < 31 && leftShoulderJoint.rotation[0] >= 0)
            leftShoulderJoint.rotation[0] -= STEP * 0.6;

        if (leftShoulderJoint.rotation[2] < 7 && leftShoulderJoint.rotation[0] <= 25 && leftShoulderJoint.rotation[2] >= 0)
            leftShoulderJoint.rotation[2] -= STEP * 0.2;

        if (leftElbowJoint.rotation[0] > -13 && leftShoulderJoint.rotation[0] <= 25 && leftElbowJoint.rotation[0] <= 0)
            leftElbowJoint.rotation[0] += STEP * 0.3;

        if (leftHipJoint.rotation[0] < 31 && leftHipJoint.rotation[0] >= 0)
            leftHipJoint.rotation[0] -= STEP * 0.5;

        if (leftKneeJoint.rotation[0] < 107 && leftKneeJoint.rotation[0] >= 0)
            leftKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

void rightLegExercise(int animationCycle) {

    timer += 0.01;

    if (animationCycle == 1) {

        if (rightShoulderJoint.rotation[0] < 30) rightShoulderJoint.rotation[0] += STEP * 0.6;
        if (rightShoulderJoint.rotation[2] > -6 && rightShoulderJoint.rotation[0] > 24) rightShoulderJoint.rotation[2] -= STEP * 0.2;
        if (rightElbowJoint.rotation[0] < 12 && rightKneeJoint.rotation[0] < 50) rightElbowJoint.rotation[0] += STEP * 0.3;
        if (rightHipJoint.rotation[0] < 30) rightHipJoint.rotation[0] += STEP;
        if (rightKneeJoint.rotation[0] < 106) rightKneeJoint.rotation[0] += STEP * 1.5;
    }

    else if (animationCycle == 2) {

        if (rightShoulderJoint.rotation[0] < 31 && rightShoulderJoint.rotation[0] >= 0)
            rightShoulderJoint.rotation[0] -= STEP * 0.6;

        if (rightShoulderJoint.rotation[2] > -7 && rightShoulderJoint.rotation[0] <= 25 && rightShoulderJoint.rotation[2] <= 0)
            rightShoulderJoint.rotation[2] += STEP * 0.2;

        if (rightElbowJoint.rotation[0] < 13 && rightShoulderJoint.rotation[0] <= 25 && rightElbowJoint.rotation[0] >= 0)
            rightElbowJoint.rotation[0] -= STEP * 0.3;

        if (rightHipJoint.rotation[0] < 31 && rightHipJoint.rotation[0] >= 0)
            rightHipJoint.rotation[0] -= STEP * 0.5;

        if (rightKneeJoint.rotation[0] < 107 && rightKneeJoint.rotation[0] >= 0)
            rightKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

void neckExercise(int animationCycle) {

    timer += 0.01;

    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -172) leftShoulderJoint.rotation[0] -= STEP * 3;
        if (leftShoulderJoint.rotation[2] > -26 && leftShoulderJoint.rotation[0] <= -30) leftShoulderJoint.rotation[2] -= STEP;
        if (leftElbowJoint.rotation[0] > -150 && leftShoulderJoint.rotation[2] <= -10) leftElbowJoint.rotation[0] -= STEP * 2.5;
        if (leftElbowJoint.rotation[2] < 54 && leftShoulderJoint.rotation[2] <= -10) leftElbowJoint.rotation[2] += STEP * 1.5;
        if (neckJoint.rotation[2] < 22 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[2] += STEP * 0.3;
        if (neckJoint.rotation[0] < 16 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[0] += STEP * 0.3;
        if (neckJoint.rotation[1] > -6 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[1] -= STEP * 0.3;
    }

    if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] > -173 && leftShoulderJoint.rotation[0] <= 0)
            leftShoulderJoint.rotation[0] += STEP * 2;

        if (leftShoulderJoint.rotation[2] > -27 && leftShoulderJoint.rotation[2] <= 0)
            leftShoulderJoint.rotation[2] += STEP;

        if (leftElbowJoint.rotation[0] > -151 && leftElbowJoint.rotation[0] <= 0)
            leftElbowJoint.rotation[0] += STEP * 2.5;

        if (leftElbowJoint.rotation[2] < 55 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP * 1.5;

        if (neckJoint.rotation[2] < 23 && neckJoint.rotation[2] >= 0)
            neckJoint.rotation[2] -= STEP * 0.3;

        if (neckJoint.rotation[0] < 17 && neckJoint.rotation[0] >= 0)
            neckJoint.rotation[0] -= STEP * 0.3;

        if (neckJoint.rotation[1] > -7 && neckJoint.rotation[1] <= 0)
            neckJoint.rotation[1] += STEP * 0.3;
    }

    if (animationCycle == 3) {

        if (rightShoulderJoint.rotation[0] > -172) rightShoulderJoint.rotation[0] -= STEP * 3;
        if (rightShoulderJoint.rotation[2] < 26 && rightShoulderJoint.rotation[0] <= -30) rightShoulderJoint.rotation[2] += STEP;
        if (rightElbowJoint.rotation[0] > -150 && rightShoulderJoint.rotation[2] >= 10) rightElbowJoint.rotation[0] -= STEP * 2.5;
        if (rightElbowJoint.rotation[2] > -54 && rightShoulderJoint.rotation[2] >= 10) rightElbowJoint.rotation[2] -= STEP * 1.5;
        if (neckJoint.rotation[2] > -22 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[2] -= STEP * 0.3;
        if (neckJoint.rotation[0] < 16 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[0] += STEP * 0.3;
        if (neckJoint.rotation[1] < 6 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[1] += STEP * 0.3;
    }

    if (animationCycle == 4) {

        if (rightShoulderJoint.rotation[0] > -173 && rightShoulderJoint.rotation[0] <= 0)
            rightShoulderJoint.rotation[0] += STEP * 2;

        if (rightShoulderJoint.rotation[2] < 27 && rightShoulderJoint.rotation[2] >= 0)
            rightShoulderJoint.rotation[2] -= STEP;

        if (rightElbowJoint.rotation[0] > -151 && rightElbowJoint.rotation[0] <= 0)
            rightElbowJoint.rotation[0] += STEP * 2.5;

        if (rightElbowJoint.rotation[2] > -55 && rightElbowJoint.rotation[2] <= 0)
            rightElbowJoint.rotation[2] += STEP * 1.5;

        if (neckJoint.rotation[2] > -23 && neckJoint.rotation[2] <= 0)
            neckJoint.rotation[2] += STEP * 0.3;

        if (neckJoint.rotation[0] < 17 && neckJoint.rotation[0] >= 0)
            neckJoint.rotation[0] -= STEP * 0.3;

        if (neckJoint.rotation[1] < 7 && neckJoint.rotation[1] >= 0)
            neckJoint.rotation[1] -= STEP * 0.3;
    }
}

void torsoExercise(int animationCycle) {

     timer += 0.01;

    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] < 36) leftShoulderJoint.rotation[0] += STEP * 1.5;
        if (leftShoulderJoint.rotation[2] > -46) leftShoulderJoint.rotation[2] -= STEP * 1.5;
        if (leftElbowJoint.rotation[0] > -150) leftElbowJoint.rotation[0] -= STEP * 2;
        if (leftElbowJoint.rotation[2] < 42) leftElbowJoint.rotation[2] += STEP * 1.5;
        if (rightShoulderJoint.rotation[0] > -180) rightShoulderJoint.rotation[0] -= STEP * 2.5;
        if (rightShoulderJoint.rotation[2] > -14 && rightShoulderJoint.rotation[0] <= -120) rightShoulderJoint.rotation[2] -= STEP;
        if (rightElbowJoint.rotation[2] > -40 && rightShoulderJoint.rotation[0] <= -80) rightElbowJoint.rotation[2] -= STEP;
        if (neckJoint.rotation[0] > -14) neckJoint.rotation[0] -= STEP * 0.2;
        if (neckJoint.rotation[2] < 14) neckJoint.rotation[2] += STEP * 0.2;
        if (torsoJoint.rotation[2] < 14) torsoJoint.rotation[2] += STEP * 0.2;
        if (waistJoint.rotation[2] < 14) waistJoint.rotation[2] += STEP * 0.2;
        if (leftHipJoint.rotation[2] > -14) leftHipJoint.rotation[2] -= STEP * 0.2;
        if (rightHipJoint.rotation[2] > -8) {
            rightHipJoint.rotation[2] -= STEP * 0.2;
            rightLegPosition.current[1] = -(waistJoint.rotation[2] * 0.05);
        }
    }

    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] < 37 && leftShoulderJoint.rotation[0] >= 0)
            leftShoulderJoint.rotation[0] -= STEP * 1.5;

        if (leftShoulderJoint.rotation[2] > -47 && leftShoulderJoint.rotation[2] <= 0)
            leftShoulderJoint.rotation[2] += STEP * 1.5;

        if (leftElbowJoint.rotation[0] > -151 && leftElbowJoint.rotation[0] <= 0)
            leftElbowJoint.rotation[0] += STEP * 2;

        if (leftElbowJoint.rotation[2] < 43 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP * 1.5;

        if (rightShoulderJoint.rotation[0] > -181 && rightShoulderJoint.rotation[0] <= 0)
            rightShoulderJoint.rotation[0] += STEP * 2.5;

        if (rightShoulderJoint.rotation[2] > -15 && rightShoulderJoint.rotation[0] <= -121 && rightShoulderJoint.rotation[2] <= 0)
            rightShoulderJoint.rotation[2] += STEP;

        if (rightElbowJoint.rotation[2] > -41 && rightShoulderJoint.rotation[0] <= -81 && rightElbowJoint.rotation[2] <= 0)
            rightElbowJoint.rotation[2] += STEP;

        if (neckJoint.rotation[0] > -15 && neckJoint.rotation[0] <= 0)
            neckJoint.rotation[0] += STEP * 0.2;

        if (neckJoint.rotation[2] < 15 && neckJoint.rotation[2] >= 0)
            neckJoint.rotation[2] -= STEP * 0.2;

        if (torsoJoint.rotation[2] < 15 && torsoJoint.rotation[2] >= 0)
            torsoJoint.rotation[2] -= STEP * 0.2;

        if (waistJoint.rotation[2] < 15 && waistJoint.rotation[2] >= 0)
            waistJoint.rotation[2] -= STEP * 0.2;

        if (leftHipJoint.rotation[2] > -15 && leftHipJoint.rotation[2] <= 0)
            leftHipJoint.rotation[2] += STEP * 0.2;

        if (rightHipJoint.rotation[2] > -9 && rightHipJoint.rotation[2] <= 0)
            rightHipJoint.rotation[2] += STEP * 0.2;

        if (rightLegPosition.current[1] <= rightLegPosition.init[1])
            rightLegPosition.current[1] = -(waistJoint.rotation[2] * 0.04);
    }

    else if (animationCycle == 3) {

        if (rightShoulderJoint.rotation[0] < 36) rightShoulderJoint.rotation[0] += STEP * 1.5;
        if (rightShoulderJoint.rotation[2] < 46) rightShoulderJoint.rotation[2] += STEP * 1.5;
        if (rightElbowJoint.rotation[0] > -150) rightElbowJoint.rotation[0] -= STEP * 2;
        if (rightElbowJoint.rotation[2] > -42) rightElbowJoint.rotation[2] -= STEP * 1.5;
        if (leftShoulderJoint.rotation[0] > -180) leftShoulderJoint.rotation[0] -= STEP * 2.5;
        if (leftShoulderJoint.rotation[2] < 14 && leftShoulderJoint.rotation[0] <= -120) leftShoulderJoint.rotation[2] += STEP;
        if (leftElbowJoint.rotation[2] < 40 && leftShoulderJoint.rotation[0] <= -80) leftElbowJoint.rotation[2] += STEP;
        if (neckJoint.rotation[0] > -14) neckJoint.rotation[0] -= STEP * 0.2;
        if (neckJoint.rotation[2] > -14) neckJoint.rotation[2] -= STEP * 0.2;
        if (torsoJoint.rotation[2] > -14) torsoJoint.rotation[2] -= STEP * 0.2;
        if (waistJoint.rotation[2] > -14) waistJoint.rotation[2] -= STEP * 0.2;
        if (rightHipJoint.rotation[2] < 14) rightHipJoint.rotation[2] += STEP * 0.2;
        if (leftHipJoint.rotation[2] < 8) {
            leftHipJoint.rotation[2] += STEP * 0.2;
            leftLegPosition.current[1] = waistJoint.rotation[2] * 0.05;
        }
    }

    else if (animationCycle == 4) {

        if (rightShoulderJoint.rotation[0] < 37 && rightShoulderJoint.rotation[0] >= 0)
            rightShoulderJoint.rotation[0] -= STEP * 1.5;

        if (rightShoulderJoint.rotation[2] < 47 && rightShoulderJoint.rotation[2] >= 0)
            rightShoulderJoint.rotation[2] -= STEP * 1.5;

        if (rightElbowJoint.rotation[0] > -151 && rightElbowJoint.rotation[0] <= 0)
            rightElbowJoint.rotation[0] += STEP * 2;

        if (rightElbowJoint.rotation[2] > -43 && rightElbowJoint.rotation[2] <= 0)
            rightElbowJoint.rotation[2] += STEP * 1.5;

        if (leftShoulderJoint.rotation[0] > -181 && leftShoulderJoint.rotation[0] <= 0)
            leftShoulderJoint.rotation[0] += STEP * 2.5;

        if (leftShoulderJoint.rotation[2] < 15 && leftShoulderJoint.rotation[0] <= -121 && leftShoulderJoint.rotation[2] >= 0)
            leftShoulderJoint.rotation[2] -= STEP;

        if (leftElbowJoint.rotation[2] < 41 && leftShoulderJoint.rotation[0] <= -81 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP;

        if (neckJoint.rotation[0] > -15 && neckJoint.rotation[0] <= 0)
            neckJoint.rotation[0] += STEP * 0.2;

        if (neckJoint.rotation[2] > -15 && neckJoint.rotation[2] <= 0)
            neckJoint.rotation[2] += STEP * 0.2;

        if (torsoJoint.rotation[2] > -15 && torsoJoint.rotation[2] <= 0)
            torsoJoint.rotation[2] += STEP * 0.2;

        if (waistJoint.rotation[2] > -15 && waistJoint.rotation[2] <= 0)
            waistJoint.rotation[2] += STEP * 0.2;

        if (rightHipJoint.rotation[2] < 15 && rightHipJoint.rotation[2] >= 0)
            rightHipJoint.rotation[2] -= STEP * 0.2;

        if (leftHipJoint.rotation[2] < 9 && leftHipJoint.rotation[2] >= 0)
            leftHipJoint.rotation[2] -= STEP * 0.2;

        if (leftLegPosition.current[1] <= leftLegPosition.init[1])
            leftLegPosition.current[1] = waistJoint.rotation[2] * 0.04;
    }
}

void resetTorsoExerciseAnimation(int animationCycle) {

    leftShoulderJoint.rotation[0] = 0;
    leftShoulderJoint.rotation[2] = 0;
    leftElbowJoint.rotation[0] = 0;
    leftElbowJoint.rotation[2] = 0;
    rightShoulderJoint.rotation[0] = 0;
    rightShoulderJoint.rotation[2] = 0;
    rightElbowJoint.rotation[2] = 0;
    neckJoint.rotation[0] = 0;
    neckJoint.rotation[2] = 0;
    torsoJoint.rotation[2] = 0;
    waistJoint.rotation[2] = 0;
    leftHipJoint.rotation[2] = 0;
    rightHipJoint.rotation[2] = 0;

    if (animationCycle == 1) rightLegPosition.current[1] = rightLegPosition.init[1];
    if (animationCycle == 2) leftLegPosition.current[1] = leftLegPosition.init[1];

    timer += 1;
}

/* Polichinelo */
void jumpingJackExercise(int animationCycle) {

    timer += 0.01;

    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -176) leftShoulderJoint.rotation[0] -= STEP * 4;
        if (leftElbowJoint.rotation[2] < 30 && leftShoulderJoint.rotation[0] <= -100) leftElbowJoint.rotation[2] += STEP * 1.5;
        if (rightShoulderJoint.rotation[0] > -176) rightShoulderJoint.rotation[0] -= STEP * 4;
        if (rightElbowJoint.rotation[2] > -30 && rightShoulderJoint.rotation[0] <= -100) rightElbowJoint.rotation[2] -= STEP * 1.5;
        if (leftHipJoint.rotation[2] > -24) leftHipJoint.rotation[2] -= STEP * 0.7;
        if (rightHipJoint.rotation[2] < 24) rightHipJoint.rotation[2] += STEP * 0.7;
        if (humanBodyPosition.current[1] < -0.5) humanBodyPosition.current[1] += 0.001;
    }

    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] > -177 && leftShoulderJoint.rotation[0] <= 0)
            leftShoulderJoint.rotation[0] += STEP * 4;

        if (leftElbowJoint.rotation[2] < 31 && leftShoulderJoint.rotation[0] <= -100 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP * 1.5;

        if (rightShoulderJoint.rotation[0] > -177 && rightShoulderJoint.rotation[0] <= 0)
            rightShoulderJoint.rotation[0] += STEP * 4;

        if (rightElbowJoint.rotation[2] > -31 && rightShoulderJoint.rotation[0] <= -100 && rightElbowJoint.rotation[2] <= 0)
            rightElbowJoint.rotation[2] += STEP * 1.5;

        if (leftHipJoint.rotation[2] > -25 && leftHipJoint.rotation[2] <= 0)
            leftHipJoint.rotation[2] += STEP * 0.7;

        if (rightHipJoint.rotation[2] < 25 && rightHipJoint.rotation[2] >= 0)
            rightHipJoint.rotation[2] -= STEP * 0.7;

        if (humanBodyPosition.current[1] >= humanBodyPosition.init[1])
            humanBodyPosition.current[1] -= 0.001;
    }
}

void updateAnimation(int optAnimation) {

    if (optAnimation != animationId) {
        animationId = optAnimation;
        newAnimation = 1;
    }
}

int checkIfAnimationEnded() {

    return (headNode == NULL);
}

void endAnimation() {

    timer = 0.01;
    animationFinished = 1;
}

/* Animacao inversa */
void inverseKinematics(int optAnimation, int resetFlag, int optUser) {

    switch (headNode->animationId) {

        /* Alongamento pernas */
        case 0:

            /* Alongamento perna esquerda */
            if (timer < 30) {

                leftLegExercise(2);

                if (timer >= 30) {

                    leftShoulderJoint.rotation[0] = 0;
                    leftShoulderJoint.rotation[2] = 0;
                    leftElbowJoint.rotation[0] = 0;
                    leftHipJoint.rotation[0] = 0;
                    leftKneeJoint.rotation[0] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            /* Alongamento perna direita */
            else {

                rightLegExercise(2);

                if (timer >= 61) {

                    rightShoulderJoint.rotation[0] = 0;
                    rightShoulderJoint.rotation[2] = 0;
                    rightElbowJoint.rotation[0] = 0;
                    rightHipJoint.rotation[0] = 0;
                    rightKneeJoint.rotation[0] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }
            break;


        /* Alongamento pescoco */
        case 1:

            /* Alongamento pescoco com braco esquerdo */
            if (timer < 34) {

                neckExercise(2);

                if (timer >= 29) {

                    leftShoulderJoint.rotation[0] = 0;
                    leftShoulderJoint.rotation[2] = 0;
                    leftElbowJoint.rotation[0] = 0;
                    leftElbowJoint.rotation[2] = 0;
                    neckJoint.rotation[0] = 0;
                    neckJoint.rotation[1] = 0;
                    neckJoint.rotation[2] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            /* Alongamento pescoco com braco direito */
            else {

                neckExercise(4);

                if (timer >= 62) {

                    rightShoulderJoint.rotation[0] = 0;
                    rightShoulderJoint.rotation[2] = 0;
                    rightElbowJoint.rotation[0] = 0;
                    rightElbowJoint.rotation[2] = 0;
                    neckJoint.rotation[0] = 0;
                    neckJoint.rotation[1] = 0;
                    neckJoint.rotation[2] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            break;


        /* Flexao lateral tronco */
        case 2:

            if (timer < 28) {

                torsoExercise(2);
                if (timer >= 28) resetTorsoExerciseAnimation(1);
            }
            else {

                torsoExercise(4);
                if (timer >= 62) resetTorsoExerciseAnimation(2);
            }
            break;

        /* Polichinelo */
        case 3:

            if (timer < 14) jumpingJackExercise(2);
            else {

                leftShoulderJoint.rotation[0] = 0;
                leftElbowJoint.rotation[2] = 0;
                rightShoulderJoint.rotation[0] = 0;
                rightElbowJoint.rotation[2] = 0;
                leftHipJoint.rotation[2] = 0;
                rightHipJoint.rotation[2] = 0;
                humanBodyPosition.current[1] = humanBodyPosition.init[1];
                timer += 1;
                kinematics(optAnimation, resetFlag, optUser);
            }
    }
}

/* Animacao corrente */
void kinematics(int optAnimation, int resetFlag, int optUser) {

    if (newAnimation) {
        addNode();
        newAnimation = 0;
    }

    switch (headNode->animationId) {

        /* Alongamento pernas */
        case 0:

            /* Alongamento perna esquerda */
            if (timer < 20) leftLegExercise(1);
            else if (timer >= 20 && timer < 31) inverseKinematics(optAnimation, resetFlag, optUser);

            /* Alongamento perna direita */
            if (timer >= 30 && timer < 51) rightLegExercise(1);
            else if (timer >= 51 && timer < 62) inverseKinematics(optAnimation, resetFlag, optUser);

            if (timer >= 62) endAnimation();
            break;


        /* Alongamento pescoco */
        case 1:

            /* Alongamento pescoco com braco esquerdo */
            if (timer < 20) neckExercise(1);
            else if (timer >= 20 && timer < 30) inverseKinematics(optAnimation, resetFlag, optUser);

            /* Alongamento pescoco com braco direito */
            if (timer >= 30 && timer < 51) neckExercise(3);
            else if (timer >= 51 && timer < 63) inverseKinematics(optAnimation, resetFlag, optUser);

            if (timer >= 63) endAnimation();
            break;


        /* Flexao lateral tronco */
        case 2:

            /* Flexao lateral tronco (esquerda) */
            if (timer < 18) torsoExercise(1);
            else if (timer >= 18 && timer < 29) inverseKinematics(optAnimation, resetFlag, optUser);

            /* Flexao lateral tronco (direita) */
            if (timer >= 29 && timer < 52) torsoExercise(3);
            else if (timer >= 52 && timer < 63) inverseKinematics(optAnimation, resetFlag, optUser);

            if (timer >= 63) endAnimation();
            break;


        /* Polichinelo */
        case 3:

            if (timer < 6) jumpingJackExercise(1);
            else if (timer >= 6 && timer < 15) inverseKinematics(optAnimation, resetFlag, optUser);

            if (timer >= 15) endAnimation();
            break;
    }

    if (animationFinished) {

        if (resetFlag || optUser >= 0) {
            animationId = -1;
            deleteList();
        }
        else {

            deleteFirstNode();
            //printList();
            if (checkIfAnimationEnded()) addNode();
        }
    }

    animationFinished = 0;
}

#endif // ANIMACAO_H_INCLUDED
