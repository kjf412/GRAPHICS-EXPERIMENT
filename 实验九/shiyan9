#include <GL/glut.h>
#include <iostream>
#include<vector>
#include<algorithm>

const int window_width = 600, window_height = 600;//设置窗口的宽高
using namespace std;

void display();
void init();
void keyBoard(unsigned char key,int x,int y);

int xb=-1,yb=1,zb=-6;
int angle=0,size=1;
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("3D 几何变换");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyBoard);
    glutMainLoop();

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xb,yb,zb);//opengl利用这个函数进行平移，参数分别朝x，y，z移动
    glColor3f(1, 0, 0);
    glRotatef(angle, 0, 1, 0);//旋转操作
    glutWireCube(size);
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);//设置当前矩阵为投影矩阵
    glLoadIdentity();//矩阵单位
    gluPerspective(45, 1, 0, 100);//设置投影矩阵
}
void keyBoard(unsigned char key,int x,int y){

    printf("请输入您的选择\n1.平移\n2.旋转\n3.缩放\n");
    if(key=='1'){
        printf("\nx正方向平移2个单位");
        xb+=2;
        display();
    }
    if(key=='2'){
        angle++;
        glTranslatef(0,0,-zb);
        glColor3f(0,1,0);
        display();
        glTranslatef(0,0,zb);
    }
    if(key=='3'){
        size++;
        display();
    }
}
