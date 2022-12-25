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

AnimationLst *headNode = NULL;

/* Juntas (articulacoes) do corpo humano */
Animation   neckJoint =           {{0.0, 0.0, 0.0}, {20.0, 20.0, 20.0}, {20.0, 20.0, 20.0}},  /*  Juntas do pescoco            */
            leftShoulderJoint =   {{0.0, 0.0, 0.0}, {200.0, 0.0, 90.0}, {60.0, 0.0, 10.0}},   /*  Juntas do ombro esquerdo     */
            rightShoulderJoint =  {{0.0, 0.0, 0.0}, {200.0, 0.0, 10.0}, {60.0, 0.0, 90.0}},   /*  Juntas do ombro direito      */
            leftElbowJoint =      {{0.0, 0.0, 0.0}, {140.0, 0.0, 0.0},  {0.0, 0.0, 60.0}},    /*  Juntas do cotovelo esquerdo  */
            rightElbowJoint =     {{0.0, 0.0, 0.0}, {140.0, 0.0, 60.0}, {0.0, 0.0, 0.0}},     /*  Juntas do cotovelo direito   */
            leftHipJoint =        {{0.0, 0.0, 0.0}, {70.0, 0.0, 40.0},  {50.0, 0.0, 40.0}},   /*  Juntas do quadril esquerdo   */
            rightHipJoint =       {{0.0, 0.0, 0.0}, {70.0, 0.0, 40.0},  {50.0, 0.0, 40.0}},   /*  Juntas do quadril direito    */
            leftKneeJoint =       {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},    {140.0, 0.0, 0.0}},   /*  Juntas do joelho esquerdo    */
            rightKneeJoint =      {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},    {140.0, 0.0, 0.0}};   /*  Juntas do joelho direito     */

/* Definindo Rotacao e Posicao (inicial) dos halteres que serao utilizados durante o exercicio */
Animation   leftDumbbellRot  = {{0.0, 0.0, 0.0}},
            rightDumbbellRot = {{0.0, 0.0, 0.0}};

/* Posicao inicial e atual do corpo humano */
ObjectPosition humanBody = {{0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}};


/* Posicao inicial e atual dos halteres */
ObjectPosition  leftDumbbellPos  = {{-2.0, 5.0, -1.0}, {-2.0, 5.0, -1.0}},
                rightDumbbellPos = {{-2.0, 1.0, -1.0}, {-2.0, 1.0, -1.0}};

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
    while (temp != NULL) {
        printf("%d -> ", temp->animationId);
        temp = temp->next;
    }
    printf("\n");
}

void leftLegExercise(int animationCycle) {

    if (animationCycle == 1) {

        timer += 0.01;

        if (leftShoulderJoint.rotation[0] < 30) leftShoulderJoint.rotation[0] += STEP * 0.6;
        if (leftShoulderJoint.rotation[2] < 6 && leftShoulderJoint.rotation[0] > 24) leftShoulderJoint.rotation[2] += STEP * 0.2;
        if (leftElbowJoint.rotation[0] > -12 && leftKneeJoint.rotation[0] < 50) leftElbowJoint.rotation[0] -= STEP * 0.3;
        if (leftHipJoint.rotation[0] < 30) leftHipJoint.rotation[0] += STEP;
        if (leftKneeJoint.rotation[0] < 106) leftKneeJoint.rotation[0] += STEP * 1.5;
    }

    else if (animationCycle == 2) {

        timer += 0.01;

        if (leftShoulderJoint.rotation[0] <= 31 && leftShoulderJoint.rotation[0] >= 0)
            leftShoulderJoint.rotation[0] -= STEP * 0.6;

        if (leftShoulderJoint.rotation[2] <= 7 && leftShoulderJoint.rotation[0] <= 25 && leftShoulderJoint.rotation[2] >= 0)
            leftShoulderJoint.rotation[2] -= STEP * 0.2;

        if (leftElbowJoint.rotation[0] >= -13 && leftShoulderJoint.rotation[0] <= 25 && leftElbowJoint.rotation[0] <= 0)
            leftElbowJoint.rotation[0] += STEP * 0.3;

        if (leftHipJoint.rotation[0] <= 31 && leftHipJoint.rotation[0] >= 0)
            leftHipJoint.rotation[0] -= STEP * 0.5;

        if (leftKneeJoint.rotation[0] <= 107 && leftKneeJoint.rotation[0] >= 0)
            leftKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

void rightLegExercise(int animationCycle) {

    if (animationCycle == 1) {

        timer += 0.01;

        if (rightShoulderJoint.rotation[0] < 30) rightShoulderJoint.rotation[0] += STEP * 0.6;
        if (rightShoulderJoint.rotation[2] > -6 && rightShoulderJoint.rotation[0] > 24) rightShoulderJoint.rotation[2] -= STEP * 0.2;
        if (rightElbowJoint.rotation[0] < 12 && rightKneeJoint.rotation[0] < 50) rightElbowJoint.rotation[0] += STEP * 0.3;
        if (rightHipJoint.rotation[0] < 30) rightHipJoint.rotation[0] += STEP;
        if (rightKneeJoint.rotation[0] < 106) rightKneeJoint.rotation[0] += STEP * 1.5;
    }

    else if (animationCycle == 2) {

        timer += 0.01;

        if (rightShoulderJoint.rotation[0] <= 31 && rightShoulderJoint.rotation[0] >= 0)
            rightShoulderJoint.rotation[0] -= STEP * 0.6;

        if (rightShoulderJoint.rotation[2] >= -7 && rightShoulderJoint.rotation[0] <= 25 && rightShoulderJoint.rotation[2] <= 0)
            rightShoulderJoint.rotation[2] += STEP * 0.2;

        if (rightElbowJoint.rotation[0] <= 13 && rightShoulderJoint.rotation[0] <= 25 && rightElbowJoint.rotation[0] >= 0)
            rightElbowJoint.rotation[0] -= STEP * 0.3;

        if (rightHipJoint.rotation[0] <= 31 && rightHipJoint.rotation[0] >= 0)
            rightHipJoint.rotation[0] -= STEP * 0.5;

        if (rightKneeJoint.rotation[0] <= 107 && rightKneeJoint.rotation[0] >= 0)
            rightKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

void neckExercise(int animationCycle) {

    if (animationCycle == 1) {

        timer += 0.01;

        if (neckJoint.rotation[2] < 16) neckJoint.rotation[2] += STEP * 0.2;
        if (neckJoint.rotation[0] > -16) neckJoint.rotation[0] -= STEP * 0.2;
        if (neckJoint.rotation[1] > -6) neckJoint.rotation[1] -= STEP * 0.2;
        if (leftShoulderJoint.rotation[0] > -178) leftShoulderJoint.rotation[0] -= STEP * 2.5;
        if (leftShoulderJoint.rotation[2] < 40 && leftShoulderJoint.rotation[0] <= -150) leftShoulderJoint.rotation[2] += STEP;
    }
}

void updateAnimation(int optAnimation) {

    if (optAnimation != animationId) {
        animationId = optAnimation;
        newAnimation = 1;
    }
    else newAnimation = 0;
}

int endAnimation() {

    return (headNode == NULL);
}

/* Animacao inversa */
void inverseKinematics(int optAnimation, int resetFlag, int optUser) {

    switch (headNode->animationId) {

        /* Alongamento pernas */
        case 0:

            /* Alongamento perna esquerda */
            if (timer >= 12 && timer < 20) {

                leftLegExercise(2);

                if (timer >= 20) {

                    leftShoulderJoint.rotation[0] = 0;
                    leftShoulderJoint.rotation[2] = 0;
                    leftElbowJoint.rotation[0] = 0;
                    leftHipJoint.rotation[0] = 0;
                    leftKneeJoint.rotation[0] = 0;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            /* Alongamento perna direita */
            else {

                rightLegExercise(2);

                if (timer >= 40) {

                    rightShoulderJoint.rotation[0] = 0;
                    rightShoulderJoint.rotation[2] = 0;
                    rightElbowJoint.rotation[0] = 0;
                    rightHipJoint.rotation[0] = 0;
                    rightKneeJoint.rotation[0] = 0;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }
            break;
    }
}

/* Animacao corrente */
void kinematics(int optAnimation, int resetFlag, int optUser) {

    if (newAnimation) {
        addNode();
        newAnimation = 0;
        printList();
    }

    switch (headNode->animationId) {

        /* Alongamento pernas */
        case 0:

            /* Alongamento perna esquerda */
            if (timer < 12) leftLegExercise(1);
            else if (timer >= 12 && timer < 20) inverseKinematics(optAnimation, resetFlag, optUser);

            /* Alongamento perna direita */
            if (timer >= 20 && timer < 32) rightLegExercise(1);
            else if (timer >= 32 && timer < 40) inverseKinematics(optAnimation, resetFlag, optUser);

            if (timer >= 40) {
                timer = 0.01;
                animationFinished = 1;
            }
            break;

        /* Alongamento pescoco */
        case 1:

            if (timer < 8) {

                neckExercise(1);

            }
            break;
    }

    if (animationFinished) {

        if (resetFlag || optUser >= 0) {
            animationId = -1;
            deleteList();
        }
        else {
            deleteFirstNode();
            if (!newAnimation) addNode();
        }
    }

    animationFinished = 0;
}

#endif // ANIMACAO_H_INCLUDED
