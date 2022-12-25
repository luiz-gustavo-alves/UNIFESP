/*
 *   UNIFESP SJC
 *
 *   COMPUTACAO GRAFICA
 *   OPENGL - PROJETO FINAL
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "corpoHumano.h"
#include "cenario.h"

/* Tamanho da janela */
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

#define MAX_ZOOM_OUT 180
#define MAX_ZOOM_IN 30
#define PI 3.141592


/* Rotacao da camera */
float cameraX, cameraY, cameraZ;
float aspectRatio       = 0.0;
float vision            = 45.0;
float cameraRadius      = 100.0f;
float theta             = 0.35f;
float alpha             = 0.0f;

/* Opcoes de menu e animacao */
int optUser = -1;
int optAnimation = -1;
int resetFlag = 0;
int animationFlag = 0;

/* Definicao dos eixos de rotacao a serem modificados pelo usuario */
typedef struct {

    float *axis[3];
    float orientation;
    char keyPressed;

} Rotation;

Rotation rotate;

/* Junta atual do corpo humano */
Animation *currentJoint;

void initLightning() {

    /* Definicao dos parametros de luz */
    float lightAmbient[]  = {0.3, 0.3, 0.3, 1.0};
    float lightDiffuse[]  = {0.4, 0.4, 0.4, 1.0};
    float lightSpecular[] = {0.4, 0.4, 0.4, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    /* Definicao dos parametros de luz dos materiais (objetos) */
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    initBodyQuadrics();
    initScenarioQuadrics();
    initLightning();
}

/* Define e posiciona a fonte de luz */
void updateLightningPosition() {

    float lightPosition[] = {alpha, theta, cameraZ, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void updateCamera() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(vision, aspectRatio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraX = sin(alpha) * cos(theta) * cameraRadius;
    cameraY = sin(theta) * cameraRadius;
    cameraZ = cos(alpha) * cos(theta) * cameraRadius;

    //printf("x: %f |  y: %f  |  z: %f  |  THETA: %f  ALPHA: %f\n", cameraX, cameraY, cameraZ, theta, alpha);

    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    updateLightningPosition();
}

void reshape(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (float) w / (float) h;

    if (w >= h) glOrtho(-10.0 * aspectRatio, 10.0 * aspectRatio, -10.0, 10.0, -10.0, 10.0);
    else glOrtho(-10.0, 10.0, -10.0 / aspectRatio, 10.0 / aspectRatio, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCamera();
}

void display() {

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, -15, 15);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateCamera();

    drawHuman();
    drawScenario(alpha, theta);

    glutSwapBuffers();
}

void changeBodyJoint(int id) {

    switch (id) {

        /* Junta do pescoco */
        case 0:
            currentJoint = &neckJoint;
            break;

        /* Junta do ombro esquerdo  */
        case 1:
            currentJoint = &leftShoulderJoint;
            break;

        /* Junta do ombro direito */
        case 2:
            currentJoint = &rightShoulderJoint;
            break;

        /* Junta do cotovelo esquerdo */
        case 3:
            currentJoint = &leftElbowJoint;
            break;

        /* Junta do cotovelo direito */
        case 4:
            currentJoint = &rightElbowJoint;
            break;

        /* Junta do quadril esquerdo */
        case 5:
            currentJoint = &leftHipJoint;
            break;

        /* Junta do quadril direito */
        case 6:
            currentJoint = &rightHipJoint;
            break;

        /* Junta do joelho esquerdo */
        case 7:
            currentJoint = &leftKneeJoint;
            break;

        /* Junta do joelho direito */
        case 8:
            currentJoint = &rightKneeJoint;
            break;
    }
}

/* Altera os eixos de rotacao de uma dada junta do corpo humano */
void changeJointRotation() {

    rotate.axis[0] = &currentJoint->rotation[0];
    rotate.axis[1] = &currentJoint->rotation[1];
    rotate.axis[2] = &currentJoint->rotation[2];
}

void resetMenu(int id) {

    resetFlag = id;
}

void userMenu(int id) {

    optUser = id;
    changeBodyJoint(id);
    changeJointRotation();
}

void animationMenu(int id) {

    animationFlag = 1;
    optAnimation = id;
}

/* Verifica se as juntas do corpo humano ultrapassam os limites especificados da animacao */
int checkJointRotation() {

    char keys[] = {"xyz"};

    int i;
    for (i = 0; i < AXIS; i++) {

        if (rotate.keyPressed == keys[i]) {

            float offSet = currentJoint->rotation[i] + rotate.orientation;
            float minRot = currentJoint->minRotation[i];
            float maxRot = currentJoint->maxRotation[i];

            return (-minRot <= offSet) && (offSet <= maxRot);
        }
    }
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        /* TECLA ESC */
        case 27:
            exit(0);
            break;

        case 'x':
        case 'X':
        case 'y':
        case 'Y':
        case 'z':
        case 'Z':

            if (optUser < 0 || (animationFlag || resetFlag)) return;

            if (key == 'x' || key == 'X') rotate.keyPressed = 'x';
            else if (key == 'y' || key == 'Y') rotate.keyPressed = 'y';
            else rotate.keyPressed = 'z';

            if (key == 'x' || key == 'y' || key == 'z') {

                rotate.orientation = 2.0;

                if (checkJointRotation()) {

                    if (rotate.keyPressed == 'x') *rotate.axis[0] += 2.0;
                    else if (rotate.keyPressed == 'y') *rotate.axis[1] += 2.0;
                    else *rotate.axis[2] += 2.0;
                }
            }
            else {

                rotate.orientation = -2.0;

                if (checkJointRotation()) {

                    if (rotate.keyPressed == 'x') *rotate.axis[0] -= 2.0;
                    else if (rotate.keyPressed == 'y') *rotate.axis[1] -= 2.0;
                    else *rotate.axis[2] -= 2.0;
                }
            }
            printf("x: %f | y: %f | z: %f\n", *rotate.axis[0], *rotate.axis[1], *rotate.axis[2]);
            break;

        case '+':

            if (cameraRadius > MAX_ZOOM_IN) cameraRadius -= 2.0;
            break;

        case '-':

            if (cameraRadius < MAX_ZOOM_OUT) cameraRadius += 2.0;
            break;
    }
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {

    float newTheta = theta;

    switch (key) {

        case GLUT_KEY_LEFT:

            alpha -= 0.05;
            break;

        case GLUT_KEY_RIGHT:

            alpha += 0.05;
            break;

        case GLUT_KEY_UP:

            if (newTheta + 0.05 < 1.5) theta += 0.05;
            break;

        case GLUT_KEY_DOWN:

            if (newTheta - 0.05 > 0) theta -= 0.05;
            break;
    }

    /* Limitar os angulos da camera entre 0 e 2PI */
    if (alpha > 2 * PI) alpha = alpha - 2 * PI;
    else if(alpha < 0.0) alpha = 2 * PI - alpha;

    glutPostRedisplay();
}

/* Verifica se o eixo de rotacao das juntas do corpo humano estao na posicao inicial */
int checkInitialJointRotation() {

    float minRot = -0.1;
    float maxRot = 0.1;

    return (((*rotate.axis[0] - minRot) * (*rotate.axis[0]- maxRot) <= 0) &&
            ((*rotate.axis[1] - minRot) * (*rotate.axis[1] - maxRot) <= 0) &&
            ((*rotate.axis[2] - minRot) * (*rotate.axis[2] - maxRot) <= 0));
}

/* Reseta todos os angulos para posicao inicial */
int resetJointsAngle() {

    int numResetedJoints = 0;

    int i, j;
    for (i = 0; i < NUM_JOINTS; i++) {

        changeBodyJoint(i);
        changeJointRotation();

        if (checkInitialJointRotation()) {
            *rotate.axis[0] = *rotate.axis[1] = *rotate.axis[2] = 0.0;
            numResetedJoints += 1;
            continue;
        }

        for (j = 0; j < AXIS; j++) {

            if (*rotate.axis[j] < 0) *rotate.axis[j] += STEP;
            else if (*rotate.axis[j] > 0) *rotate.axis[j] -= STEP;
        }
    }

    if (numResetedJoints == NUM_JOINTS) {
        resetFlag = 0;
        optUser = -1;
    }
}

void idleFunc() {

    if (resetFlag && (optAnimation < 0 || (endAnimation() && optUser >= 0))) resetJointsAngle();

    if (animationFlag) {

        if (endAnimation() && optUser >= 0) resetFlag = 1;
        else {

            updateAnimation(optAnimation);
            kinematics(optAnimation, resetFlag, optUser);

            if (endAnimation()) {
                animationFlag = 0;
                optAnimation = -1;
            }
        }
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    int subUserMenu, aquecimento, reset;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Projeto Final - Computação Gráfica");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idleFunc);

    subUserMenu = glutCreateMenu(userMenu);

        glutAddMenuEntry(" Mover Cabeca ", 0);
        glutAddMenuEntry(" Mover Braco Esquerdo ", 1);
        glutAddMenuEntry(" Mover Braco Direito ", 2);
        glutAddMenuEntry(" Mover Antebraco Esquerdo ", 3);
        glutAddMenuEntry(" Mover Antebraco Direito ", 4);
        glutAddMenuEntry(" Mover Perna Esquerda ", 5);
        glutAddMenuEntry(" Mover Perna Direita ", 6);
        glutAddMenuEntry(" Mover Joelho Esquerdo ", 7);
        glutAddMenuEntry(" Mover Joelho Direito ", 8);

    aquecimento = glutCreateMenu(animationMenu);

            glutAddMenuEntry(" Alongamento Pernas ", 0);
            glutAddMenuEntry(" Alongamento Pescoco ", 1);
            glutAddMenuEntry(" Agachamento ", 2);
            glutAddMenuEntry(" Polichinelo ", 3);
            glutAddMenuEntry(" Todos ", 4);

    reset = glutCreateMenu(resetMenu);

    glutAddMenuEntry(" Resetar ", 1);
    glutAddSubMenu(" Movimentacao ", subUserMenu);
    glutAddSubMenu(" Aquecimento ", aquecimento);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
 }
