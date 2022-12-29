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

/* Flags de controle de fluxo da animacao */
float timer = 0.01;
int animationFinished = 0;
int newAnimation = 0;
int animationId = -1;
int allAnimationFlag = 0;
int waitForAllAnimationFinish = 0;
int hasEquipment = 0;
int hasLeftEquipment = 0;
int hasRightEquipment = 0;
int walkingCycle = 1;
int stopWalkingAnimation = 1;

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

/* Definindo Rotacao do corpo humano e dos halteres que serao utilizados durante o exercicio */
Animation   leftDumbbellRot  = {{0.0, 0.0, 0.0}},
            rightDumbbellRot = {{0.0, 0.0, 0.0}},
            humanBodyRot     = {{0.0, 0.0, 0.0}};


/* Posicao inicial do corpo humano e das estruturas do corpo */
ObjectPosition  humanBodyPosition   = {{0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}},
                waistPosition       = {{0.0, 0.0, 0.0},  {0.0, 0.0, 0.0}},
                leftLegPosition     = {{0.0, 0.0, 0.0},  {0.0, 0.0, 0.0}},
                rightLegPosition    = {{0.0, 0.0, 0.0},  {0.0, 0.0, 0.0}};

/* Posicao inicial e atual dos halteres */
ObjectPosition  leftDumbbellPos  = {{0.0, 0.0, 0.0},  {-40.75, -5.5, -30.0}},
                rightDumbbellPos = {{0.0, 0.0, 0.0},  {-35.75, -1.5, -30.0}};

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

void updateAnimation(int optAnimation) {

    if (optAnimation == 5 && !waitForAllAnimationFinish) {
        allAnimationFlag = 1;
        waitForAllAnimationFinish = 1;
    }

    else if (((optAnimation != animationId) && optAnimation < 7) || ((optAnimation != animationId) && (optAnimation > 6 && hasEquipment))) {
        animationId = optAnimation;
        newAnimation = 1;
    }
}

int checkIfHasEquipment() {

    return hasEquipment;
}

int checkIfAnimationEnded() {

    return (headNode == NULL);
}

void endAnimation() {

    timer = 0.01;
    animationFinished = 1;
}

/* Exercicios - Aquecimento (Alongamento Pernas) */
void leftLegExercise(int animationCycle) {

    timer += 0.01;

    /* Animacao segurando perna */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] < 30) leftShoulderJoint.rotation[0] += STEP * 0.6;
        if (leftShoulderJoint.rotation[2] < 6 && leftShoulderJoint.rotation[0] > 24) leftShoulderJoint.rotation[2] += STEP * 0.2;
        if (leftElbowJoint.rotation[0] > -12 && leftKneeJoint.rotation[0] < 50) leftElbowJoint.rotation[0] -= STEP * 0.3;
        if (leftHipJoint.rotation[0] < 30) leftHipJoint.rotation[0] += STEP;
        if (leftKneeJoint.rotation[0] < 106) leftKneeJoint.rotation[0] += STEP * 1.5;
    }

    /* Resetar animacao segurando perna */
    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] <= 25 && leftShoulderJoint.rotation[2] > 0)
            leftShoulderJoint.rotation[2] -= STEP * 0.2;

        if (leftShoulderJoint.rotation[0] <= 25 && leftElbowJoint.rotation[0] < 0)
            leftElbowJoint.rotation[0] += STEP * 0.3;

        if (leftShoulderJoint.rotation[0] > 0) leftShoulderJoint.rotation[0] -= STEP * 0.6;
        if (leftHipJoint.rotation[0] > 0) leftHipJoint.rotation[0] -= STEP * 0.5;
        if (leftKneeJoint.rotation[0] > 0) leftKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

/* Exercicios - Aquecimento (Alongamento Pernas) */
void rightLegExercise(int animationCycle) {

    timer += 0.01;

    /* Animacao segurando perna */
    if (animationCycle == 1) {

        if (rightShoulderJoint.rotation[0] < 30) rightShoulderJoint.rotation[0] += STEP * 0.6;
        if (rightShoulderJoint.rotation[2] > -6 && rightShoulderJoint.rotation[0] > 24) rightShoulderJoint.rotation[2] -= STEP * 0.2;
        if (rightElbowJoint.rotation[0] < 12 && rightKneeJoint.rotation[0] < 50) rightElbowJoint.rotation[0] += STEP * 0.3;
        if (rightHipJoint.rotation[0] < 30) rightHipJoint.rotation[0] += STEP;
        if (rightKneeJoint.rotation[0] < 106) rightKneeJoint.rotation[0] += STEP * 1.5;
    }

    /* Resetar animacao segurando perna */
    else if (animationCycle == 2) {

        if (rightShoulderJoint.rotation[0] <= 25 && rightShoulderJoint.rotation[2] <= 0)
            rightShoulderJoint.rotation[2] += STEP * 0.2;

        if (rightShoulderJoint.rotation[0] <= 25 && rightElbowJoint.rotation[0] >= 0)
            rightElbowJoint.rotation[0] -= STEP * 0.3;

        if (rightShoulderJoint.rotation[0] > 0) rightShoulderJoint.rotation[0] -= STEP * 0.6;
        if (rightHipJoint.rotation[0] > 0) rightHipJoint.rotation[0] -= STEP * 0.5;
        if (rightKneeJoint.rotation[0] > 0) rightKneeJoint.rotation[0] -= STEP * 1.5;
    }
}

/* Exercicios - Aquecimento (Alongamento Pescoco) */
void neckExercise(int animationCycle) {

    timer += 0.01;

    /* Animacao com braco esquerdo no pescoco */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -172) leftShoulderJoint.rotation[0] -= STEP * 3;
        if (leftShoulderJoint.rotation[2] > -26 && leftShoulderJoint.rotation[0] <= -30) leftShoulderJoint.rotation[2] -= STEP;
        if (leftElbowJoint.rotation[0] > -150 && leftShoulderJoint.rotation[2] <= -10) leftElbowJoint.rotation[0] -= STEP * 2.5;
        if (leftElbowJoint.rotation[2] < 54 && leftShoulderJoint.rotation[2] <= -10) leftElbowJoint.rotation[2] += STEP * 1.5;
        if (neckJoint.rotation[2] < 22 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[2] += STEP * 0.3;
        if (neckJoint.rotation[0] < 16 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[0] += STEP * 0.3;
        if (neckJoint.rotation[1] > -6 && leftShoulderJoint.rotation[0] <= -40) neckJoint.rotation[1] -= STEP * 0.3;
    }

    /* Resetar animacao com braco esquerdo no pescoco */
    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] < 0) leftShoulderJoint.rotation[0] += STEP * 2;
        if (leftShoulderJoint.rotation[2] < 0) leftShoulderJoint.rotation[2] += STEP;
        if (leftElbowJoint.rotation[0] < 0) leftElbowJoint.rotation[0] += STEP * 2.5;
        if (leftElbowJoint.rotation[2] > 0) leftElbowJoint.rotation[2] -= STEP * 1.5;
        if (neckJoint.rotation[2] > 0) neckJoint.rotation[2] -= STEP * 0.3;
        if (neckJoint.rotation[0] > 0) neckJoint.rotation[0] -= STEP * 0.3;
        if (neckJoint.rotation[1] < 0) neckJoint.rotation[1] += STEP * 0.3;
    }

    /* Animacao com braco direito no pescoco */
    else if (animationCycle == 3) {

        if (rightShoulderJoint.rotation[0] > -172) rightShoulderJoint.rotation[0] -= STEP * 3;
        if (rightShoulderJoint.rotation[2] < 26 && rightShoulderJoint.rotation[0] <= -30) rightShoulderJoint.rotation[2] += STEP;
        if (rightElbowJoint.rotation[0] > -150 && rightShoulderJoint.rotation[2] >= 10) rightElbowJoint.rotation[0] -= STEP * 2.5;
        if (rightElbowJoint.rotation[2] > -54 && rightShoulderJoint.rotation[2] >= 10) rightElbowJoint.rotation[2] -= STEP * 1.5;
        if (neckJoint.rotation[2] > -22 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[2] -= STEP * 0.3;
        if (neckJoint.rotation[0] < 16 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[0] += STEP * 0.3;
        if (neckJoint.rotation[1] < 6 && rightShoulderJoint.rotation[0] <= -40) neckJoint.rotation[1] += STEP * 0.3;
    }

    /* Resetar nimacao com braco direito no pescoco */
    else if (animationCycle == 4) {

        if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP * 2;
        if (rightShoulderJoint.rotation[2] > 0) rightShoulderJoint.rotation[2] -= STEP;
        if (rightElbowJoint.rotation[0] < 0) rightElbowJoint.rotation[0] += STEP * 2.5;
        if (rightElbowJoint.rotation[2] < 0) rightElbowJoint.rotation[2] += STEP * 1.5;
        if (neckJoint.rotation[2] < 0) neckJoint.rotation[2] += STEP * 0.3;
        if (neckJoint.rotation[0] > 0) neckJoint.rotation[0] -= STEP * 0.3;
        if (neckJoint.rotation[1] >= 0) neckJoint.rotation[1] -= STEP * 0.3;
    }
}

/* Exercicios - Aquecimento (Flexao Lateral Tronco) */
void torsoExercise(int animationCycle) {

    timer += 0.01;

    /* Animacao de flexao na lateral direita do tronco */
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

    /* Resetar animacao de flexao na lateral direita do tronco */
    else if (animationCycle == 2) {

        if (rightShoulderJoint.rotation[0] <= -121 && rightShoulderJoint.rotation[2] < 0)
            rightShoulderJoint.rotation[2] += STEP;

        if (rightShoulderJoint.rotation[0] <= -81 && rightElbowJoint.rotation[2] < 0)
            rightElbowJoint.rotation[2] += STEP;

        if (leftShoulderJoint.rotation[0] > 0) leftShoulderJoint.rotation[0] -= STEP * 1.5;
        if (leftShoulderJoint.rotation[2] < 0) leftShoulderJoint.rotation[2] += STEP * 1.5;
        if (leftElbowJoint.rotation[0] < 0) leftElbowJoint.rotation[0] += STEP * 2;
        if (leftElbowJoint.rotation[2] > 0) leftElbowJoint.rotation[2] -= STEP * 1.5;
        if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP * 2.5;
        if (neckJoint.rotation[0] < 0) neckJoint.rotation[0] += STEP * 0.2;
        if (neckJoint.rotation[2] > 0) neckJoint.rotation[2] -= STEP * 0.2;
        if (torsoJoint.rotation[2] > 0) torsoJoint.rotation[2] -= STEP * 0.2;
        if (waistJoint.rotation[2] > 0) waistJoint.rotation[2] -= STEP * 0.2;
        if (leftHipJoint.rotation[2] < 0) leftHipJoint.rotation[2] += STEP * 0.2;
        if (rightHipJoint.rotation[2] < 0) rightHipJoint.rotation[2] += STEP * 0.2;
        if (rightLegPosition.current[1] < rightLegPosition.init[1]) rightLegPosition.current[1] = -(waistJoint.rotation[2] * 0.04);
    }

    /* Animacao de flexao na lateral esquerda do tronco */
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

    /* Resetar animacao de flexao na lateral direita do tronco */
    else if (animationCycle == 4) {

        if (leftShoulderJoint.rotation[2] < 15 && leftShoulderJoint.rotation[0] <= -121 && leftShoulderJoint.rotation[2] >= 0)
            leftShoulderJoint.rotation[2] -= STEP;

        if (leftElbowJoint.rotation[2] < 41 && leftShoulderJoint.rotation[0] <= -81 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP;

        if (rightShoulderJoint.rotation[0] > 0) rightShoulderJoint.rotation[0] -= STEP * 1.5;
        if (rightShoulderJoint.rotation[2] > 0) rightShoulderJoint.rotation[2] -= STEP * 1.5;
        if (rightElbowJoint.rotation[0] < 0) rightElbowJoint.rotation[0] += STEP * 2;
        if (rightElbowJoint.rotation[2] < 0) rightElbowJoint.rotation[2] += STEP * 1.5;
        if (leftShoulderJoint.rotation[0] < 0) leftShoulderJoint.rotation[0] += STEP * 2.5;
        if (neckJoint.rotation[0] < 0) neckJoint.rotation[0] += STEP * 0.2;
        if (neckJoint.rotation[2] < 0) neckJoint.rotation[2] += STEP * 0.2;
        if (torsoJoint.rotation[2] < 0) torsoJoint.rotation[2] += STEP * 0.2;
        if (waistJoint.rotation[2] < 0) waistJoint.rotation[2] += STEP * 0.2;
        if (rightHipJoint.rotation[2] > 0) rightHipJoint.rotation[2] -= STEP * 0.2;
        if (leftHipJoint.rotation[2] > 0) leftHipJoint.rotation[2] -= STEP * 0.2;
        if (leftLegPosition.current[1] < leftLegPosition.init[1]) leftLegPosition.current[1] = waistJoint.rotation[2] * 0.04;
    }
}

/* Exercicios - Aquecimento (Agachamento) */
void squat(int animationCycle) {

    timer += 0.01;

    /* Animacao de levantar os bracos */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -90) leftShoulderJoint.rotation[0] -= STEP * 1.5;
        if (rightShoulderJoint.rotation[0] > -90) rightShoulderJoint.rotation[0] -= STEP * 1.5;
    }

    /* Animacao da descida do agachamento */
    else if (animationCycle == 2) {

        if (humanBodyPosition.current[1] > -4.0) humanBodyPosition.current[1] -= 0.005;
        if (leftShoulderJoint.rotation[0] > -100) leftShoulderJoint.rotation[0] -= STEP * 0.2;
        if (rightShoulderJoint.rotation[0] > -100) rightShoulderJoint.rotation[0] -= STEP * 0.2;
        if (leftHipJoint.rotation[0] > -105) leftHipJoint.rotation[0] -= STEP * 2;
        if (leftKneeJoint.rotation[0] < 90) leftKneeJoint.rotation[0] += STEP * 2;
        if (rightHipJoint.rotation[0] > -105) rightHipJoint.rotation[0] -= STEP * 2;
        if (rightKneeJoint.rotation[0] < 90) rightKneeJoint.rotation[0] += STEP * 2;
        if (neckJoint.rotation[0] > 10) neckJoint.rotation[0] += STEP;
        if (torsoJoint.rotation[0] < 18) torsoJoint.rotation[0] += STEP * 0.25;
        if (waistJoint.rotation[0] < 18) waistJoint.rotation[0] += STEP * 0.25;
    }

    /* Animacao da subida do agachamento (resetar) */
    else if (animationCycle == 3) {

        if (humanBodyPosition.current[1] <= humanBodyPosition.init[1])
            humanBodyPosition.current[1] += 0.005;

        if (leftShoulderJoint.rotation[0] > -120 && leftShoulderJoint.rotation[0] <= -90)
            leftShoulderJoint.rotation[0] += STEP * 0.2;

        if (rightShoulderJoint.rotation[0] > -120 && rightShoulderJoint.rotation[0] <= -90)
            rightShoulderJoint.rotation[0] += STEP * 0.2;

        if (leftHipJoint.rotation[0] < 0) leftHipJoint.rotation[0] += STEP * 1.5;
        if (leftKneeJoint.rotation[0] > 0) leftKneeJoint.rotation[0] -= STEP * 1.5;
        if (rightHipJoint.rotation[0] < 0) rightHipJoint.rotation[0] += STEP * 1.5;
        if (rightKneeJoint.rotation[0] > 0) rightKneeJoint.rotation[0] -= STEP * 1.5;
        if (neckJoint.rotation[0] > 0) neckJoint.rotation[0] -= STEP;
        if (torsoJoint.rotation[0] > 0) torsoJoint.rotation[0] -= STEP * 0.25;
        if (waistJoint.rotation[0] > 0) waistJoint.rotation[0] -= STEP * 0.25;
    }

    /* Resetar animacao */
    else if (animationCycle == 4) {

        if (humanBodyPosition.current[1] < humanBodyPosition.init[1]) humanBodyPosition.current[1] += 0.005;
        if (leftShoulderJoint.rotation[0] < 0) leftShoulderJoint.rotation[0] += STEP;
        if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP;
        if (leftHipJoint.rotation[0] < 0) leftHipJoint.rotation[0] += STEP * 0.5;
        if (leftKneeJoint.rotation[0] > 0) leftKneeJoint.rotation[0] -= STEP * 0.5;
        if (rightHipJoint.rotation[0] < 0) rightHipJoint.rotation[0] += STEP * 0.5;
        if (rightKneeJoint.rotation[0] > 0) rightKneeJoint.rotation[0] -= STEP * 0.5;
        if (neckJoint.rotation[0] < 0) neckJoint.rotation[0] -= STEP;
        if (torsoJoint.rotation[0] > 0) torsoJoint.rotation[0] -= STEP * 0.2;
        if (waistJoint.rotation[0] > 0) waistJoint.rotation[0] -= STEP * 0.2;
    }
}

/* Exercicios - Aquecimento (Polichinelo) */
void jumpingJackExercise(int animationCycle) {

    timer += 0.01;

    /* Animacao de subida do polichinelo */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -176) leftShoulderJoint.rotation[0] -= STEP * 4;
        if (leftElbowJoint.rotation[2] < 30 && leftShoulderJoint.rotation[0] <= -100) leftElbowJoint.rotation[2] += STEP * 1.5;
        if (rightShoulderJoint.rotation[0] > -176) rightShoulderJoint.rotation[0] -= STEP * 4;
        if (rightElbowJoint.rotation[2] > -30 && rightShoulderJoint.rotation[0] <= -100) rightElbowJoint.rotation[2] -= STEP * 1.5;
        if (leftHipJoint.rotation[2] > -24) leftHipJoint.rotation[2] -= STEP * 0.7;
        if (rightHipJoint.rotation[2] < 24) rightHipJoint.rotation[2] += STEP * 0.7;
        if (humanBodyPosition.current[1] < -0.5) humanBodyPosition.current[1] += 0.002;
    }

    /* Animacao de descida do polichinelo (resetar) */
    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] <= -100 && leftElbowJoint.rotation[2] >= 0)
            leftElbowJoint.rotation[2] -= STEP * 1.5;

        if (rightShoulderJoint.rotation[0] <= -100 && rightElbowJoint.rotation[2] <= 0)
            rightElbowJoint.rotation[2] += STEP * 1.5;

        if (leftShoulderJoint.rotation[0] < 0) leftShoulderJoint.rotation[0] += STEP * 4;
        if (leftElbowJoint.rotation[2] > 0) leftElbowJoint.rotation[2] -= STEP * 1.5;
        if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP * 4;
        if (leftHipJoint.rotation[2] < 0) leftHipJoint.rotation[2] += STEP * 0.7;
        if (rightHipJoint.rotation[2] > 0) rightHipJoint.rotation[2] -= STEP * 0.7;
        if (humanBodyPosition.current[1] > humanBodyPosition.init[1]) humanBodyPosition.current[1] -= 0.002;
    }
}

void walkingAnimation() {

    if (walkingCycle == 1) {

        if (rightHipJoint.rotation[0] < 30 && leftHipJoint.rotation[0] > -30) {

            leftHipJoint.rotation[0] -= STEP * 0.8;
            rightHipJoint.rotation[0] += STEP * 0.8;

            if (!hasLeftEquipment && !hasRightEquipment) {

                rightShoulderJoint.rotation[0] -= STEP * 0.8;
                leftShoulderJoint.rotation[0] += STEP * 0.8;

                if (leftElbowJoint.rotation[0] < -10) leftElbowJoint.rotation[0] -= STEP * 0.2;
                if (rightElbowJoint.rotation[0] < 0) rightElbowJoint.rotation[0] += STEP * 0.2;
            }
        }
        else walkingCycle = 2;
    }

    else if (walkingCycle == 2) {

        if ((rightHipJoint.rotation[0] < 31 && leftHipJoint.rotation[0] > -31)
            && (rightHipJoint.rotation[0] > -30 && leftHipJoint.rotation[0] < 30)) {

            leftHipJoint.rotation[0] += STEP * 0.8;
            rightHipJoint.rotation[0] -= STEP * 0.8;

            if (!hasLeftEquipment && !hasRightEquipment) {

                rightShoulderJoint.rotation[0] += STEP * 0.8;
                leftShoulderJoint.rotation[0] -= STEP * 0.8;

                if (leftElbowJoint.rotation[0] < 0) leftElbowJoint.rotation[0] += STEP * 0.2;
                if (rightElbowJoint.rotation[0] > -10) rightElbowJoint.rotation[0] -= STEP * 0.2;
            }
        }
        else walkingCycle = 1;
    }
}

/* Exercicios - Halteres (Pegar Equipamento) */
int getEquipment(int animationCycle) {

    /* Andar ate rack dos halteres */
    if (animationCycle == 1 || animationCycle == 2) {

        if (humanBodyPosition.current[0] < 30) humanBodyPosition.current[0] += STEP * 0.05;
        if (humanBodyPosition.current[2] < 29) humanBodyPosition.current[2] += STEP * 0.05;

        if (animationCycle == 1) {

            if (humanBodyRot.rotation[1] < 45) humanBodyRot.rotation[1] += STEP * 0.2;
        }
        else {

            if (humanBodyRot.rotation[1] < 100) humanBodyRot.rotation[1] += STEP * 0.25;
        }
    }

    /* Resetar animacao */
    else if (animationCycle == 3) {

        if (leftHipJoint.rotation[0] < 0) leftHipJoint.rotation[0] += STEP * 0.8;
        if (leftShoulderJoint.rotation[0] > 0) leftShoulderJoint.rotation[0] -= STEP * 0.8;
        if (leftElbowJoint.rotation[0] < 0) leftElbowJoint.rotation[0] += STEP * 0.2;
        if (rightHipJoint.rotation[0] > 0) rightHipJoint.rotation[0] -= STEP * 0.8;
        if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP * 0.8;
        if (rightElbowJoint.rotation[0] > 0) rightElbowJoint.rotation[0] -= STEP * 0.8;

        if ((leftHipJoint.rotation[0] >= 0 && leftShoulderJoint.rotation[0] <= 0 && leftElbowJoint.rotation[0] >= 0) &&
            (rightHipJoint.rotation[0] <= 0 && rightShoulderJoint.rotation[0] >= 0 && rightElbowJoint.rotation[0] <= 0)) {

            leftHipJoint.rotation[0] = leftShoulderJoint.rotation[0] = leftElbowJoint.rotation[0] = 0;
            rightHipJoint.rotation[0] = rightShoulderJoint.rotation[0] = rightElbowJoint.rotation[0] = 0;
            timer += 1;

            return 0;
        }
        else return 1;
    }

    /* Pegar haltere com a mao esquerda */
    else if (animationCycle == 4) {

        if (leftShoulderJoint.rotation[0] > -85 && !hasLeftEquipment) leftShoulderJoint.rotation[0] -= STEP * 0.8;
        if (leftShoulderJoint.rotation[0] <= -85 || hasLeftEquipment) {

            if (leftDumbbellPos.current[1] < 0.2 && !hasLeftEquipment) leftDumbbellPos.current[1] += STEP * 0.01;
            if (leftDumbbellPos.current[1] >= 0.2 || hasLeftEquipment) {

                hasLeftEquipment = 1;

                if (leftShoulderJoint.rotation[0] < 0) leftShoulderJoint.rotation[0] += STEP * 0.8;
                if (leftShoulderJoint.rotation[2] > -16 && leftShoulderJoint.rotation[0] > -40) leftShoulderJoint.rotation[2] -= STEP * 0.2;
                if (leftDumbbellPos.current[0] > -6.5 && leftShoulderJoint.rotation[0] > -70) leftDumbbellPos.current[0] -= STEP * 0.07;
                if (leftDumbbellPos.current[1] > -5.5) leftDumbbellPos.current[1] -= STEP * 0.08;
                if (leftDumbbellPos.current[2] < 3.0) leftDumbbellPos.current[2] += STEP * 0.02;
                if (leftDumbbellPos.current[0] <= -6.5) timer += 1;
            }
        }
    }

    /* Pegar haltere com a mao direita */
    else if (animationCycle == 5) {

        if (rightShoulderJoint.rotation[0] > -60 && !hasRightEquipment) rightShoulderJoint.rotation[0] -= STEP * 0.8;
        if (rightElbowJoint.rotation[2] > -26 && rightShoulderJoint.rotation[0] < -20 && !hasRightEquipment)
            rightElbowJoint.rotation[2] -= STEP * 0.5;

        if (rightShoulderJoint.rotation[0] < -20 && !hasRightEquipment) {

            timer += 0.01;

            if (torsoJoint.rotation[0] < 12) torsoJoint.rotation[0] += STEP * 0.2;
            if (waistJoint.rotation[0] < 12) waistJoint.rotation[0] += STEP * 0.2;
            if (leftHipJoint.rotation[0] > -12) leftHipJoint.minRotation[0] -= STEP * 0.2;
            if (rightHipJoint.rotation[0] > -12) rightHipJoint.rotation[0] -= STEP * 0.2;
            if (humanBodyPosition.current[0] < 31) humanBodyPosition.current[0] += STEP * 0.04;
            if (humanBodyPosition.current[2] < 31) humanBodyPosition.current[2] += STEP * 0.04;
            if (leftDumbbellPos.current[2] < 5.0) leftDumbbellPos.current[2] += STEP * 0.04;
        }

        if (timer >= 72) {

            hasRightEquipment = 1;

            if (torsoJoint.rotation[0] > 0) torsoJoint.rotation[0] -= STEP * 0.2;
            if (waistJoint.rotation[0] > 0) waistJoint.rotation[0] -= STEP * 0.2;
            if (leftHipJoint.rotation[0] < 0) leftHipJoint.rotation[0] += STEP * 0.4;
            if (rightHipJoint.rotation[0] < 0) rightHipJoint.rotation[0] += STEP * 0.4;
            if (rightShoulderJoint.rotation[0] < 0) rightShoulderJoint.rotation[0] += STEP * 0.8;
            if (rightShoulderJoint.rotation[2] < 22) rightShoulderJoint.rotation[2] += STEP * 0.2;
            if (rightElbowJoint.rotation[2] < 0) rightElbowJoint.rotation[2] += STEP * 0.5;
            if (rightDumbbellPos.current[0] > -5.5 && leftShoulderJoint.rotation[0] > -70) rightDumbbellPos.current[0] -= STEP * 0.07;
            if (rightDumbbellPos.current[1] > -1.5) rightDumbbellPos.current[1] -= STEP * 0.08;
            if (rightDumbbellPos.current[2] > -2.5 && leftShoulderJoint.rotation[0] > -40) rightDumbbellPos.current[2] -= STEP * 0.03;
            if (leftDumbbellPos.current[0] < -5.5) leftDumbbellPos.current[0] += STEP * 0.03;

            if (rightDumbbellPos.current[2] <= -2.5) {

                leftHipJoint.rotation[0] = leftShoulderJoint.rotation[0] = leftElbowJoint.rotation[0] = 0;
                rightHipJoint.rotation[0] = rightShoulderJoint.rotation[0] = rightElbowJoint.rotation[0] = 0;
                humanBodyRot.rotation[1] = -90;
                timer += 1;
            }
        }
    }

    /* Atualizar temporizador e animacao de andar */
    if (animationCycle < 3) {
        timer += 0.01;
        walkingAnimation();
    }
}

/* Exercicios - Halteres (Pegar Equipamento) */
void returnEquipment(int animationCycle) {

    /* Voltar para posicao inicial (horizontal) */
    if (animationCycle == 1) {


        if (humanBodyPosition.current[0] >= 0) {

            humanBodyPosition.current[0] -= STEP * 0.07;
            leftDumbbellPos.current[0] -= STEP * 0.07;
            rightDumbbellPos.current[0] -= STEP * 0.07;
        }
        else {

            humanBodyRot.rotation[1] = leftDumbbellRot.rotation[1] = rightDumbbellRot.rotation[1] = -180;
            leftDumbbellPos.current[0] -= 1;
            rightDumbbellPos.current[0] = (leftDumbbellPos.current[0] - 7);
            leftDumbbellPos.current[2] = rightDumbbellPos.current[2] = 1;
            timer += 1;
        }
    }

    /* Voltar para posicao inicial (vertical) */
    else if (animationCycle == 2) {

        if (humanBodyPosition.current[2] >= 0) {

            humanBodyPosition.current[2] -= STEP * 0.07;
            leftDumbbellPos.current[2] -= STEP * 0.07;
            rightDumbbellPos.current[2] -= STEP * 0.07;
        }
        else {

            humanBodyRot.rotation[1] = 0;
            leftDumbbellRot.rotation[1] = rightDumbbellRot.rotation[1] = 90;
            leftDumbbellPos.current[0] = leftDumbbellPos.init[0];
            rightDumbbellPos.current[0] = rightDumbbellPos.init[0];

            timer += 1;
        }
    }

    /* Resetar animacao */
    else if (animationCycle == 3) {

        if (leftHipJoint.rotation[0] > 0) leftHipJoint.rotation[0] -= STEP * 0.8;
        if (rightHipJoint.rotation[0] < 0) rightHipJoint.rotation[0] += STEP * 0.8;
        if (leftShoulderJoint.rotation[0] > -18) leftShoulderJoint.rotation[0] -= STEP;
        if (leftShoulderJoint.rotation[2] < -4) leftShoulderJoint.rotation[2] += STEP;
        if (rightShoulderJoint.rotation[0] > -18) rightShoulderJoint.rotation[0] -= STEP;
        if (rightShoulderJoint.rotation[2] > 4) rightShoulderJoint.rotation[2] -= STEP;

        timer += 0.01;
    }
    if (animationCycle < 3) walkingAnimation();
}

/* Exercicios - Halteres (Rosca Alternada) */
void unilateralCurl(int animationCycle) {

    timer += 0.01;

    /* Subida antebraco esquerdo */
    if (animationCycle == 1) {

        if (leftElbowJoint.rotation[0] > -110) {

            leftElbowJoint.rotation[0] -= STEP * 2;
            leftDumbbellPos.current[1] += STEP * 0.095;
            if (leftDumbbellPos.current[2] < -28) leftDumbbellPos.current[2] += STEP * 0.06;
        }
    }

    /* Descida antebraco esquerdo */
    else if (animationCycle == 2) {

        if (leftElbowJoint.rotation[0] < 0) {

            leftElbowJoint.rotation[0] += STEP * 2;
            leftDumbbellPos.current[1] -= STEP * 0.095;
        }
        if (leftDumbbellPos.current[2] > leftDumbbellPos.init[2] && leftElbowJoint.rotation[0] > -45) leftDumbbellPos.current[2] -= STEP * 0.06;
    }

    /* Subida antebraco direito */
    if (animationCycle == 3) {

        if (rightElbowJoint.rotation[0] > -110) {

            rightElbowJoint.rotation[0] -= STEP * 2;
            rightDumbbellPos.current[1] += STEP * 0.095;
            if (rightDumbbellPos.current[2] < -28) rightDumbbellPos.current[2] += STEP * 0.06;
        }
    }

    /* Descida antebraco direito */
    else if (animationCycle == 4) {

        if (rightElbowJoint.rotation[0] < 0) {

            rightElbowJoint.rotation[0] += STEP * 2;
            rightDumbbellPos.current[1] -= STEP * 0.095;
        }
        if (rightDumbbellPos.current[2] > rightDumbbellPos.init[2] && rightElbowJoint.rotation[0] > -45) rightDumbbellPos.current[2] -= STEP * 0.06;
    }
}

/* Exercicios - Halteres (Rosca Simultanea) */
void bilateralCurl(int animationCycle) {

    timer += 0.01;

    /* Subida antebraco direito e esquerdo */
    if (animationCycle == 1) {

        if (leftElbowJoint.rotation[0] > -110) {

            leftElbowJoint.rotation[0] -= STEP * 2;
            rightElbowJoint.rotation[0] -= STEP * 2;

            leftDumbbellPos.current[1] += STEP * 0.095;
            rightDumbbellPos.current[1] += STEP * 0.095;

            if (leftDumbbellPos.current[2] < -28 && rightDumbbellPos.current[2] < -28) {

                leftDumbbellPos.current[2] += STEP * 0.06;
                rightDumbbellPos.current[2] += STEP * 0.06;
            }
        }
    }

    /* Descida antebraco direito e esquerdo */
    else if (animationCycle == 2) {

        if (leftElbowJoint.rotation[0] < 0) {

            leftElbowJoint.rotation[0] += STEP * 2;
            rightElbowJoint.rotation[0] += STEP * 2;

            leftDumbbellPos.current[1] -= STEP * 0.095;
            rightDumbbellPos.current[1] -= STEP * 0.095;
        }

         if ((leftDumbbellPos.current[2] > leftDumbbellPos.init[2] && rightDumbbellPos.current[2] > rightDumbbellPos.init[2]) &&
             (leftElbowJoint.rotation[0] > -45 && rightElbowJoint.rotation[0] > -45)) {

            leftDumbbellPos.current[2] -= STEP * 0.06;
            rightDumbbellPos.current[2] -= STEP * 0.06;
        }
    }
}

/* Exercicios - Halteres (Elevacao Frontal) */
void frontalRaise(int animationCycle) {

    timer += 0.01;

    /* Subida do peso */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -94 && rightShoulderJoint.rotation[0] > -94) {

            leftShoulderJoint.rotation[0] -= STEP ;
            rightShoulderJoint.rotation[0] -= STEP;

            leftDumbbellPos.current[1] += STEP * 0.095;
            rightDumbbellPos.current[1] += STEP * 0.095;

            if (leftDumbbellPos.current[2] < -25.5 && rightDumbbellPos.current[2] < -25.5) {

                leftDumbbellPos.current[2] += STEP * 0.1;
                rightDumbbellPos.current[2] += STEP * 0.1;
            }
        }
    }

    /* Descida do peso */
    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] < -18 && rightShoulderJoint.rotation[0] < -18) {

            leftShoulderJoint.rotation[0] += STEP;
            rightShoulderJoint.rotation[0] += STEP;

            leftDumbbellPos.current[1] -= STEP * 0.095;
            rightDumbbellPos.current[1] -= STEP * 0.095;

            if ((leftDumbbellPos.current[2] > leftDumbbellPos.init[2] && rightDumbbellPos.current[2] > rightDumbbellPos.init[2]) &&
                (leftShoulderJoint.rotation[0] > -66 && rightShoulderJoint.rotation[0] > -66)) {

                leftDumbbellPos.current[2] -= STEP * 0.1;
                rightDumbbellPos.current[2] -= STEP * 0.1;
            }
        }
    }
}

/* Exercicios - Halteres (Elevacao Lateral) */
void lateralRaise(int animationCycle) {

    timer += 0.01;

    /* Subida do peso */
    if (animationCycle == 1) {

        if (leftShoulderJoint.rotation[0] > -70 && rightShoulderJoint.rotation[0] > -70) {

            leftShoulderJoint.rotation[0] -= STEP;
            leftShoulderJoint.rotation[2] -= STEP;
            rightShoulderJoint.rotation[0] -= STEP;
            rightShoulderJoint.rotation[2] += STEP;

            leftDumbbellPos.current[1] += STEP * 0.1;
            rightDumbbellPos.current[1] += STEP * 0.1;

            if (leftDumbbellPos.current[0] > -46.5 && rightDumbbellPos.current[0] < -29.5) {

                leftDumbbellPos.current[0] -= STEP * 0.1;
                rightDumbbellPos.current[0] += STEP * 0.1;
            }

            if (leftDumbbellPos.current[2] < -28 && rightDumbbellPos.current[2] < -28) {

                leftDumbbellPos.current[2] += STEP * 0.06;
                rightDumbbellPos.current[2] += STEP * 0.06;
            }
        }
    }

    /* Descida do peso */
    else if (animationCycle == 2) {

        if (leftShoulderJoint.rotation[0] < -18 && rightShoulderJoint.rotation[0] < -18) {

            leftShoulderJoint.rotation[0] += STEP;
            leftShoulderJoint.rotation[2] += STEP;
            rightShoulderJoint.rotation[0] += STEP;
            rightShoulderJoint.rotation[2] -= STEP;

            leftDumbbellPos.current[1] -= STEP * 0.1;
            rightDumbbellPos.current[1] -= STEP * 0.1;
        }

        if (leftDumbbellPos.current[0] < leftDumbbellPos.init[0] && rightDumbbellPos.current[0] > rightDumbbellPos.init[0]) {

            leftDumbbellPos.current[0] += STEP * 0.1;
            rightDumbbellPos.current[0] -= STEP * 0.1;
        }

        if ((leftDumbbellPos.current[2] > leftDumbbellPos.init[2] && rightDumbbellPos.current[2] > rightDumbbellPos.init[2]) &&
            (leftShoulderJoint.rotation[0] > -45 && rightShoulderJoint.rotation[0] > -45)) {

            leftDumbbellPos.current[2] -= STEP * 0.06;
            rightDumbbellPos.current[2] -= STEP * 0.06;
        }
    }

}

void resetTorsoExerciseAnimation(int animationCycle) {

    leftShoulderJoint.rotation[0] = leftShoulderJoint.rotation[2] = 0;
    leftElbowJoint.rotation[0] = leftElbowJoint.rotation[2] = 0;
    rightShoulderJoint.rotation[0] = rightShoulderJoint.rotation[2] = 0;
    rightElbowJoint.rotation[0] = rightElbowJoint.rotation[2] = 0;
    neckJoint.rotation[0] = neckJoint.rotation[2] = 0;
    torsoJoint.rotation[2] = waistJoint.rotation[2] = 0;
    leftHipJoint.rotation[2] = rightHipJoint.rotation[2] = 0;

    if (animationCycle == 1) rightLegPosition.current[1] = rightLegPosition.init[1];
    if (animationCycle == 2) leftLegPosition.current[1] = leftLegPosition.init[1];

    timer += 1;
}

void resetDumbellAnimation() {

    leftShoulderJoint.rotation[0] = rightShoulderJoint.rotation[0] = -18;
    leftShoulderJoint.rotation[2] = -4; rightShoulderJoint.rotation[2] = 4;

    leftDumbbellPos.current[0] = leftDumbbellPos.init[0];
    leftDumbbellPos.current[1] = leftDumbbellPos.init[1];
    leftDumbbellPos.current[2] = leftDumbbellPos.init[2];

    rightDumbbellPos.current[0] = rightDumbbellPos.init[0];
    rightDumbbellPos.current[1] = rightDumbbellPos.init[1];
    rightDumbbellPos.current[2] = rightDumbbellPos.init[2];

    timer += 1;
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

                    leftShoulderJoint.rotation[0] = leftShoulderJoint.rotation[2] = 0;
                    leftElbowJoint.rotation[0] = leftHipJoint.rotation[0] = leftKneeJoint.rotation[0] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            /* Alongamento perna direita */
            else {

                rightLegExercise(2);

                if (timer >= 61) {

                    rightShoulderJoint.rotation[0] = rightShoulderJoint.rotation[2] = 0;
                    rightElbowJoint.rotation[0] = rightHipJoint.rotation[0] = rightKneeJoint.rotation[0] = 0;
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

                    leftShoulderJoint.rotation[0] = leftShoulderJoint.rotation[2] = 0;
                    leftElbowJoint.rotation[0] = leftElbowJoint.rotation[2] = 0;
                    neckJoint.rotation[0] = neckJoint.rotation[1] = neckJoint.rotation[2] = 0;
                    timer += 1;
                    kinematics(optAnimation, resetFlag, optUser);
                }
            }

            /* Alongamento pescoco com braco direito */
            else {

                neckExercise(4);

                if (timer >= 62) {

                    rightShoulderJoint.rotation[0] = rightShoulderJoint.rotation[2] = 0;
                    rightElbowJoint.rotation[0] = rightElbowJoint.rotation[2] = 0;
                    neckJoint.rotation[0] = neckJoint.rotation[1] = neckJoint.rotation[2] = 0;
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


        /* Agachamento */
        case 3:

            if (timer < 79) squat(4);
            else {

                leftShoulderJoint.rotation[0] = leftHipJoint.rotation[0] = leftKneeJoint.rotation[0] = 0;
                rightShoulderJoint.rotation[0] = rightHipJoint.rotation[0] = rightKneeJoint.rotation[0] = 0;
                neckJoint.rotation[0] = torsoJoint.rotation[0] = waistJoint.rotation[0] = 0;
                humanBodyPosition.current[1] = humanBodyPosition.init[1];
                timer += 0.01;
            }
            break;

        /* Polichinelo */
        case 4:

            if (timer >= 30) {

                leftShoulderJoint.rotation[0] = leftElbowJoint.rotation[2] = leftHipJoint.rotation[2] = 0;
                rightShoulderJoint.rotation[0] = rightElbowJoint.rotation[2] = rightHipJoint.rotation[2] = 0;
                humanBodyPosition.current[1] = humanBodyPosition.init[1];
                timer += 1;
                kinematics(optAnimation, resetFlag, optUser);
            }

            if ((timer >= 5 && timer < 10) || (timer >= 15 && timer < 20) || (timer >= 25 && timer < 30)) jumpingJackExercise(2);
            else kinematics(optAnimation, resetFlag, optUser);

            break;


        /* Retornar com equipamento */
        case 6:

            /* Retornar para posicao inicial (horizontal e vertical) */
            if (timer < 74) returnEquipment(1);
            else if (timer < 75) returnEquipment(2);

            /* Resetar animacao */
            else if (timer >= 75 && timer < 78) returnEquipment(3);
            else {

                leftHipJoint.rotation[0] = rightHipJoint.rotation[0] = 0;
                leftShoulderJoint.rotation[0] = rightShoulderJoint.rotation[0] = -18;
                leftShoulderJoint.rotation[2] = -4; rightShoulderJoint.rotation[2] = 4;
                timer += 1;
            }
            break;


        /* Animacoes com halteres */
        case 7:
        case 8:
        case 9:
        case 10:

            resetDumbellAnimation();
            break;
    }
}

/* Animacao corrente */
void kinematics(int optAnimation, int resetFlag, int optUser) {

    int i;
    if (newAnimation) {

        addNode();
        newAnimation = 0;
    }

    if (allAnimationFlag) {

        for (i = 0; i <= 5; i++) {
            animationId = i;
            addNode();
        }
        allAnimationFlag = 0;
    }

    /* Exercicios de aquecimento (sem equipamento) */
    if (!hasEquipment && headNode != NULL) {

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


            /* Agachamento */
            case 3:

                /* Estica os bracos */
                if (timer < 8) squat(1);

                /* Descida e subida do agachamento */
                if ((timer >= 8 && timer < 18) || (timer >= 28 && timer < 38) || (timer >= 48 && timer < 58)) squat(2);
                else if ((timer >= 18 && timer < 28) || (timer >= 38 && timer < 48) || (timer >= 58 && timer < 68)) squat(3);

                if (timer >= 68 && timer < 80) inverseKinematics(optAnimation, resetFlag, optUser);
                if (timer >= 80) endAnimation();

                break;


            /* Polichinelo */
            case 4:

                if (timer >= 30)  {
                    endAnimation();
                    break;
                }

                /* Subida e descida do polichinelo */
                if ((timer < 5) || (timer >= 10 && timer < 15) || (timer >= 20 && timer < 25)) jumpingJackExercise(1);
                else inverseKinematics(optAnimation, resetFlag, optUser);

                break;


            /* Todas animacoes de aquecimento */
            case 5:

                endAnimation();
                waitForAllAnimationFinish = 0;
                break;


            /* Pegar equipamento */
            case 6:

                /* Andar ate rack dos halteres */
                if (timer < 45) getEquipment(1);
                else if (timer >= 45 && timer < 63) getEquipment(2);

                /* Resetar animacao */
                else if (timer >= 63 && stopWalkingAnimation) stopWalkingAnimation = getEquipment(3);

                /* Pegar haltere com a mao esquerda */
                if (timer >= 64 && timer < 65) getEquipment(4);

                /* Pegar haltere com a mao direita */
                else if (timer >= 65 && timer < 73) getEquipment(5);

                if (timer >= 73 && timer < 79) inverseKinematics(optAnimation, resetFlag, optUser);
                else if (timer >= 79) {

                    endAnimation();
                    hasLeftEquipment = hasRightEquipment = 0;
                    hasEquipment = 1;
                }
                break;
        }
    }

    /* Exercicios com halteres */
    if (hasEquipment && headNode != NULL) {

        switch (headNode->animationId) {

            /* Rosca alternada */
            case 7:

                /* Serie com o antebraco esquerdo */
                if ((timer < 10) || (timer >= 40 && timer < 50))  unilateralCurl(1);
                else if ((timer >= 10 && timer < 20) || (timer >= 50 && timer < 60)) unilateralCurl(2);


                /* Serie com o antebraco direito */
                if ((timer >= 20 && timer < 30) || (timer >= 60 && timer < 70)) unilateralCurl(3);
                else if ((timer >= 30 && timer < 40) || (timer >= 70 && timer < 80)) unilateralCurl(4);

                if (timer >= 80 && timer < 83) inverseKinematics(optAnimation, resetFlag, optUser);
                else if (timer >= 83) endAnimation();

                break;


            /* Rosca simultanea */
            case 8:

                /* Serie com o antebraco esquerdo e direito */
                if ((timer < 10) || (timer >= 20 && timer < 30) || (timer >= 40 && timer < 50)) bilateralCurl(1);
                else if ((timer >= 10 && timer < 20) || (timer >= 30 && timer < 40) || (timer >= 50 && timer < 60)) bilateralCurl(2);

                if (timer >= 60 && timer < 63) inverseKinematics(optAnimation, resetFlag, optUser);
                else if (timer >= 63) endAnimation();

                break;


            /* Elevacao frontal */
            case 9:

                /* Levanta e abaixa os pesos (vertical) */
                if ((timer < 12) || (timer >= 24 && timer < 36))  frontalRaise(1);
                else if ((timer >= 12 && timer < 24) || (timer >= 36 && timer < 48)) frontalRaise(2);

                if (timer >= 48 && timer < 52) inverseKinematics(optAnimation, resetFlag, optUser);
                else if (timer >= 52) endAnimation();

                break;


            /* Elevacao lateral */
            case 10:

                /* Levante e abaixa os pesos (horizontal) */

                if ((timer < 15) || (timer >= 30 && timer < 45)) lateralRaise(1);
                else if ((timer >= 15 && timer < 30) || (timer >= 45 && timer < 60)) lateralRaise(2);

                if (timer >= 60 && timer < 63) inverseKinematics(optAnimation, resetFlag, optUser);
                else if (timer >= 63) endAnimation();

                break;

        }
    }

    if (animationFinished) {

        if (resetFlag || optUser >= 0 || headNode->animationId == 5 || headNode->animationId == 6) {

            animationId = -1;
            waitForAllAnimationFinish = 0;
            deleteList();
        }
        else {

            //printList();
            deleteFirstNode();
            if (checkIfAnimationEnded()) addNode();
        }
    }

    animationFinished = 0;
}

#endif // ANIMACAO_H_INCLUDED
