#include <iostream>
#include <vector>
#include "MeshFigure.h"
#include "ObjFigure.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400

#define NEAR_PLANE 0.1
#define FAR_PLANE 100.0
#define VIEW_ANGLE 60.0

#define PI 3.1415

using namespace std;

bool drawBaseLine = true;

vector<float> angleX;
vector<float> angleY;
vector<float> angleZ;
vector<float> transX;
vector<float> transY;
vector<float> transZ;

int figure_count = 1;
double angle_step = 2;
double move_step = 0.2;

vector<Figure*> figures;

BmpLoader* boxLoaders[6];
unsigned int id[6];

int target = 0;
int lightStatus = 0;
int lockTarget = -1;

void init() {
    ifstream in;
    in.open("config");
    int cnt;
    in >> cnt;
    string temp;
    double inNum;
    for (int i = 0; i < cnt; i++) {
        in >> temp >> inNum;
        if (temp == "ANGLE_STEP") 
        {
            angle_step = inNum;
        }
        else if (temp == "MOVE_STEP") 
        {
            move_step = inNum;
        }
    }
    in >> cnt;
    transX.resize(cnt + 1, 0);
    transY.resize(cnt + 1, 0);
    transZ.resize(cnt + 1, 0);
    angleX.resize(cnt + 1, 0);
    angleY.resize(cnt + 1, 0);
    angleZ.resize(cnt + 1, 0);
    figures.push_back(NULL);
    for (int i = 0; i < cnt; i++) {
        in >> temp;
        if (temp == "FILE")
        {
            string meshPath;
            string texturePath;
            in >> meshPath >> texturePath;
            figures.push_back(MeshFigure::readFigure(meshPath, texturePath));
        }
        else if (temp == "OBJ") 
        {
            string objPath;
            in >> objPath;
            figures.push_back(new ObjFigure(objPath));
        }
        else {
            double size;
            double R;
            double G;
            double B;
            in >> size >> R >> G >> B;
            figures.push_back(new BuiltInFigure(temp, size, R, G, B));
        }
    }
}


void initBoxTexture() {
    for (int i = 0; i < 6; i++) {
        boxLoaders[i] = new BmpLoader();
    }
    boxLoaders[0]->load("box/front.bmp");
    boxLoaders[1]->load("box/top.bmp");
    boxLoaders[2]->load("box/left.bmp");
    boxLoaders[3]->load("box/right.bmp");
    boxLoaders[4]->load("box/back.bmp");
    boxLoaders[5]->load("box/bottom.bmp");
    for (int i = 0; i < 6; i++) {
        id[i] = loadTexture(boxLoaders[i]);
        delete boxLoaders[i];
    }
}

void drawBox() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, id[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, id[1]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, id[2]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, id[3]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, id[4]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, id[5]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(50.0f, -50.0f, 50.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotated(angleY[0], 0, 1, 0);
    glRotated(angleX[0], 1, 0, 0);
    glRotated(angleZ[0], 0, 0, 1);
    glTranslated(transX[0], transY[0], transZ[0]);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    
    GLfloat  lightPos[] = { -40.0f, 40.0f, -40.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    if (drawBaseLine) {
        glLineWidth(1);
        glColor3f(0, 0, 255);
        glBegin(GL_LINES);
        for (int i = -100; i <= 100; i++) {
            glVertex3d(i, -1, 100);
            glVertex3d(i, -1, -100);
        }
        for (int i = -100; i <= 100; i++) {
            glVertex3d(100, -1, i);
            glVertex3d(-100, -1, i);
        }
        glEnd();
    }
    
    drawBox();

    for (int i = 0; i < figures.size(); i++)
        glPushMatrix();
    for (int i = 1; i < figures.size(); i++) {
        glPopMatrix();
        glTranslated(transX[i], transY[i], transZ[i]);
        glRotated(angleY[i], 0, 1, 0);
        glRotated(angleX[i], 1, 0, 0);
        glRotated(angleZ[i], 0, 0, 1);
        figures[i]->show();
    }

    glutSwapBuffers();
}

// 禁止改变窗口尺寸
void preventReshape(int x, int y) {
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void myKeyBoardFunc(unsigned char key, int x, int y) {
    // ws 前后 ad 左右 zx上下
    // qe 绕y轴 rt 绕x轴 fg 绕z轴
    switch (key) {
    case 'm': {
        if (lockTarget != -1) {
            printf("[Lock Info]Locked with %d\n", lockTarget);
            lockTarget = -1;
        }
        target = (target + 1) % figures.size();
        printf("[Target Info]Current target: %d\n", target);
        break;
    }
    case 'k': {
        if (lockTarget == -1) {
            if (target != 0) {
                lockTarget = target;
                printf("[Lock]Locked with %d\n", lockTarget);
            }
        }
        else {
            printf("[Lock]unlock with %d\n", lockTarget);
            lockTarget = -1;
        }
        break;
    }
    case 'p': {
        exit(0);
    }
    case 'j': {
        drawBaseLine = !drawBaseLine;
        if (drawBaseLine) printf("[Base Line]Base Line on\n");
        else printf("[Base Line]Base Line off\n");
        break;
    }
    case 'o': {
        // 所有物体复位
        for (int i = 0; i < figures.size(); i++) {
            angleX[i] = 0;
            angleY[i] = 0;
            angleZ[i] = 0;
            transX[i] = 0;
            transY[i] = 0;
            transZ[i] = 0;
        }
        break;
    }
    case 'w': {
        if (target == 0) {
            transZ[target] += move_step * cos(angleY[0] / 180 * PI);
            transX[target] -= move_step * sin(angleY[0] / 180 * PI);
            break;
        }
        transZ[target] += move_step;
        if(lockTarget != -1) transZ[0] -= move_step;
        
        break;
    }
    case 's': {
        if (target == 0) {
            transZ[target] -= move_step * cos(angleY[0] / 180 * PI);
            transX[target] += move_step * sin(angleY[0] / 180 * PI);
            break;
        }
        transZ[target] -= move_step;
        if (lockTarget != -1) transZ[0] += move_step;
        break;
    }
    case 'z': {
        transY[target] -= move_step;
        if (lockTarget != -1) transY[0] += move_step;
        break;
    }
    case 'x': {
        transY[target] += move_step;
        if (lockTarget != -1) transY[0] -= move_step;
        break;
    }
    case 'a': {
        if (target == 0) {
            transZ[target] += move_step * cos((angleY[0] - 90) / 180 * PI);
            transX[target] -= move_step * sin((angleY[0] - 90) / 180 * PI);
            break;
        }
        transX[target] += move_step;
        if (lockTarget != -1) transX[0] -= move_step;
        break;
    }
    case 'd': {
        if (target == 0) {
            transZ[target] -= move_step * cos((angleY[0] - 90) / 180 * PI);
            transX[target] += move_step * sin((angleY[0] - 90) / 180 * PI);
            break;
        }
        transX[target] -= move_step;
        if (lockTarget != -1) transX[0] += move_step;
        break;
    }
    case 'q': {
        angleY[target] -= angle_step;
        break;
    }
    case 'e': {
        angleY[target] += angle_step;
        break;
    }
    case 'r': {
        angleX[target] -= angle_step;
        break;
    }
    case 't': {
        angleX[target] += angle_step;
        break;
    }
    case 'f': {
        angleZ[target] -= angle_step;
        break;
    }
    case 'g': {
        angleZ[target] += angle_step;
        break;
    }
    case 'l': {
        if (lightStatus == 0) {
            lightStatus = 1;
            glEnable(GL_LIGHTING);
            printf("[Light] on\n");
        }
        else {
            lightStatus = 0;
            glDisable(GL_LIGHTING);
            printf("[Light] off\n");
        }
        break;
    }
    case '[': {
        if (target != 0) {
            figures[target]->bigger();
        }
        break;
    }
    case ']': {
        if (target != 0) {
            figures[target]->smaller();
        }
        break;
    }
    }
    myDisplay();
}
void myMenu(int choice) {
    switch (choice) {
        case 2: {
            exit(0);
        }
        case 1: {
            for (int i = 0; i < figures.size(); i++) {
                angleX[i] = 0;
                angleY[i] = 0;
                angleZ[i] = 0;
                transX[i] = 0;
                transY[i] = 0;
                transZ[i] = 0;
            }
        }
    }
    myDisplay();

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("1913134");
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.8, 0.8, 0.8, 0);
    
    glutKeyboardFunc(myKeyBoardFunc);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(preventReshape);

    glEnable(GL_DEPTH_TEST);

    GLfloat  whiteLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat  sourceLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sourceLight);
    glEnable(GL_LIGHT0);

    glutCreateMenu(myMenu);
    glutAddMenuEntry("RESET", 1);
    glutAddMenuEntry("QUIT", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    initBoxTexture();

    init();

    glMatrixMode(GL_PROJECTION);
    gluPerspective(VIEW_ANGLE, (float)WINDOW_WIDTH / WINDOW_HEIGHT, NEAR_PLANE, FAR_PLANE);

    glutMainLoop();
}