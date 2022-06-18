#include <gl\glut.h>

float the_theta=0.0,Xtheta=0,Ytheta=0;//定义旋转角度、绕x轴旋转、绕y轴旋转
float oldx=0,oldy=0;//记录旧的点

void motionROt(int x,int y);

static GLdouble viewer[] = { 0, 0, 5 };
static GLdouble theta[]  = { 0, 0, 0 };
GLfloat vertices[][3] =
        { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },{ 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
          { -1.0, -1.0, 1.0 },{ 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };
void Cube(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glNormal3fv(vertices[a]);
    glVertex3fv(vertices[a]);
    glNormal3fv(vertices[b]);
    glVertex3fv(vertices[b]);
    glNormal3fv(vertices[c]);
    glVertex3fv(vertices[c]);
    glNormal3fv(vertices[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}
void drawCube()
{
    glColor3f(0, 0, 1);
    Cube(0, 3, 2, 1);
    glColor3f(0, 1, 0);
    Cube(2, 3, 7, 6);
    glColor3f(1, 0, 0);
    Cube(0, 4, 7, 3);
    glColor3f(1, 0, 0);
    Cube(1, 2, 6, 5);
    glColor3f(1, 1, 0);
    Cube(4, 5, 6, 7);
    glColor3f(1, 0, 1);
    Cube(0, 1, 5, 4);
}
void myReshap(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height)
        glFrustum(-2, 2, -2 * (GLfloat)height / (GLfloat)width, 2 * (GLfloat)height / (GLfloat)width, 2, 10);
    else
        glFrustum(-2 * (GLfloat)width / (GLfloat)height, 2 * (GLfloat)width / (GLfloat)height, -2, 2, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);//键盘平移
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glRotatef(Xtheta,0.0f,1.0f,0.0f);//根据鼠标移动距离旋转物体
    glRotatef(Ytheta,1.0f,0.0f,0.0f);
    //绘制正?体
    drawCube();
    glFlush();
    glutSwapBuffers();
}

void MouseFunc(int button, int state, int x, int y)
{
    oldx = x;//当左键按下时记录鼠标坐标
    oldy = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutMotionFunc(motionROt);
    }
}


void motionROt(int x,int y)//实现摁住时，计算旋转量，实现旋转
{
    GLint deltax = x-oldx;
    GLint deltay = y-oldy;
    Xtheta += 360 * (GLfloat)deltax / (GLfloat)600;//根据屏幕上鼠标滑动的距离来设置旋转的角度
    Ytheta += 360 * (GLfloat)deltay / (GLfloat)600;
    oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
    oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
    myDisplay();
}
void KeyboardFunc(int key,int x,int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            theta[2]++;
            break;
        case GLUT_KEY_RIGHT:
            theta[2]--;
            break;
        case GLUT_KEY_UP:
            theta[0]--;
            break;
        case GLUT_KEY_DOWN:
            theta[0]++;
        default:
            break;
    }
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Computer Graphics-3D观察");
    //根据坐标远近?动隐藏被遮住部分
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(myReshap);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(MouseFunc);
    glutSpecialFunc(KeyboardFunc);
    glutMainLoop();
}

