#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float angle = 0.0f;         // Sudut kemiringan saklar
bool isOn = false;          // Status saklar ON/OFF
float lightIntensity = 0.0f; // Intensitas cahaya

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightPos[] = { 2.0f, 4.0f, 4.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void drawSwitchBase() {
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    glScalef(2.0f, 2.5f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawSwitchLever() {
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.25f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f); // Rotasi untuk ON/OFF
    glColor3f(0.6f, 0.6f, 0.6f);
    glScalef(0.3f, 1.0f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawLightBulb() {
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glColor3f(lightIntensity, lightIntensity, 0.0f);
    glutSolidSphere(0.5, 32, 32);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera dan arah pandang
    gluLookAt(4.0, 4.0, 6.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0);

    // Posisi ulang lampu tiap frame
    GLfloat lightPos[] = { 2.0f, 4.0f, 4.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    drawSwitchBase();
    drawSwitchLever();
    drawLightBulb();

    glutSwapBuffers();
}

void update(int value) {
    float targetAngle = isOn ? -25.0f : 25.0f; // Tuas miring
    if (angle < targetAngle) angle += 1.5f;
    else if (angle > targetAngle) angle -= 1.5f;

    float targetLight = isOn ? 1.0f : 0.2f; // Lampu terang atau redup
    if (lightIntensity < targetLight) lightIntensity += 0.05f;
    else if (lightIntensity > targetLight) lightIntensity -= 0.05f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        isOn = !isOn; // Ganti status ON/OFF
    }
}

void init() {
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    initLighting();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Saklar Lampu - OpenGL");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
