/*
 *   UNIFESP SJC
 *
 *   COMPUTACAOO GRAFICA
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

#define MAX_ZOOM_IN 180
#define MAX_ZOOM_OUT 30

#define PI 3.141592

typedef struct {

    float *x, *y, *z;
    float orientation;
    char keyPressed;

} Rotation;

Rotation rotate;

float aspectRatio = 0.0;
int opt = -1;

Joint *currentJoint;

float fieldOfVision = 45.0;
float cameraX, cameraY, cameraZ;
float cameraRadius = 120.0f;
float theta = 0.35f;
float alpha = 0.0f;

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

    initLightning();
    initBodyQuadrics();
    initScenarioQuadrics();
}

/* Define e posiciona a fonte de luz */
void updateLightningPosition() {

    float lightPosition[] = {alpha, theta, cameraZ, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void updateCamera() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fieldOfVision, aspectRatio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraX = sin(alpha) * cos(theta) * cameraRadius;
    cameraY = sin(theta) * cameraRadius;
    cameraZ = cos(alpha) * cos(theta) * cameraRadius;

    float upX = 0.0;
    float upY = 1.0;
    float upZ = 0.0;

    if (theta >= PI / 2.0 && theta < 3.0 * PI / 2.0) upY = -1.0;
    else upY = 1.0;

    //printf("x: %f |  y: %f  |  z: %f  |  THETA: %f  ALPHA: %f\n", cameraX, cameraY, cameraZ, theta, alpha);

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, upX, upY, upZ);
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

void changeBodyJoint() {

    switch (opt) {

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

void changeJointRotation() {

    rotate.x = &currentJoint->x;
    rotate.y = &currentJoint->y;
    rotate.z = &currentJoint->z;
}

void menu(int id) {

    opt = id;

    if (opt < 9) {

        changeBodyJoint();
        changeJointRotation();
    }
}

int checkJointRotation() {

    if (rotate.keyPressed == 'x')
        return (-currentJoint->xMin <= currentJoint->x + rotate.orientation) && (currentJoint->x + rotate.orientation <= currentJoint->xMax);

    if (rotate.keyPressed == 'y')
        return (-currentJoint->yMin <= currentJoint->y + rotate.orientation) && (currentJoint->y + rotate.orientation <= currentJoint->yMax);

    if (rotate.keyPressed == 'z')
        return (-currentJoint->zMin <= currentJoint->z + rotate.orientation) && (currentJoint->z + rotate.orientation <= currentJoint->zMax);
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        /* TECLA ESC */
        case 27:
            exit(0);
            break;

        case 'x':
        case 'X':

            if (opt < 0) return;

            rotate.keyPressed = 'x';
            if (key == 'x') {

                rotate.orientation = 2.0;
                if (checkJointRotation()) *rotate.x += 2.0;
            }
            else {

                rotate.orientation = -2.0;
                if (checkJointRotation()) *rotate.x -= 2.0;
            }
            break;

        case 'y':
        case 'Y':

            if (opt < 0) return;

            rotate.keyPressed = 'y';
            if (key == 'y') {

                rotate.orientation = 2.0;
                if (checkJointRotation()) *rotate.y += 2.0;
            }
            else {

                rotate.orientation = -2.0;
                if (checkJointRotation()) *rotate.y -= 2.0;
            }
            break;

        case 'z':
        case 'Z':

            if (opt < 0) return;

            rotate.keyPressed = 'z';
            if (key == 'z') {

                rotate.orientation = 2.0;
                if (checkJointRotation()) *rotate.z += 2.0;
            }
            else {

                rotate.orientation = -2.0;
                if (checkJointRotation()) *rotate.z -= 2.0;
            }
            break;

        case '+':

            if (cameraRadius > MAX_ZOOM_OUT) cameraRadius -= 2.0;
            break;

        case '-':

            if (cameraRadius < MAX_ZOOM_IN) cameraRadius += 2.0;
            break;
    }
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_LEFT:
            alpha -= 0.05;
            break;

        case GLUT_KEY_RIGHT:
            alpha += 0.05;
            break;

        case GLUT_KEY_UP:
            theta += 0.05;
            break;

        case GLUT_KEY_DOWN:
            theta -= 0.05;
            break;
    }

    /* Limitar os angulos da camera entre 0 e 2PI */
    if (theta > 2 * PI) theta = theta - 2 * PI;
    else if(theta < 0.0) theta = 2 * PI - theta;

    if (alpha > 2 * PI) alpha = alpha - 2 * PI;
    else if(alpha < 0.0) alpha = 2 * PI - alpha;

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

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

    glutCreateMenu(menu);
	glutAddMenuEntry(" Mover Cabeca ", 0);
	glutAddMenuEntry(" Mover Braco Esquerdo ", 1);
	glutAddMenuEntry(" Mover Braco Direito ", 2);
    glutAddMenuEntry(" Mover Antebraco Esquerdo ", 3);
	glutAddMenuEntry(" Mover Antebraco Direito ", 4);
	glutAddMenuEntry(" Mover Perna Esquerda ", 5);
	glutAddMenuEntry(" Mover Perna Direita ", 6);
    glutAddMenuEntry(" Mover Joelho Esquerdo ", 7);
	glutAddMenuEntry(" Mover Joelho Direito ", 8);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
 }
