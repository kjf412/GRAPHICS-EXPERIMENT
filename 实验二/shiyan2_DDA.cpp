#include <iostream>
#include <cstdio>
#include <cmath>
#include <GL/glut.h>

void init();
void Display(void);
inline int myround(const float a);
void setPixel(GLint x,GLint y);
void lineDDA(int x0, int y0, int xEnd, int yEnd);
using namespace std;
inline int myround(const float a){
    return (int)(a+0.5);
}
void setPixel(GLint x,GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}
void lineDDA(int x0, int y0, int xEnd, int yEnd){
    int dx=xEnd-x0,dy=yEnd-y0,steps,k;
    float xIncrement,yIncrement,x=(float)x0,y=(float)y0;

    if(abs(dx)>abs(dy))//如果斜率小于1 原算法只实现了斜率大于零的情况
    {
        steps=abs(dx);
    }
    else{
        steps=abs(dy);
    }

    xIncrement=(float)(dx)/(float)(steps);
    yIncrement=(float)(dy)/(float)(steps);

    setPixel(myround(x),myround(y));
    for(k=0;k<=steps;k++){
        x+=xIncrement;
        y+=yIncrement;
        setPixel(myround(x),myround(y));
    }
    glEnd();
    glFlush();
}
void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int x,y,xEnd,yEnd;
    cout<<"请输入初始点和末尾点（x,y,xEnd,yEnd）(空格为间隔)"<<endl;
    fflush(stdin);
    cin>>x>>y>>xEnd>>yEnd;

    lineDDA(x,y,xEnd,yEnd);
    glEnd();
    glFlush();
}
int main(int argc, char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA算法");

    init();
    glutDisplayFunc(&Display);
    glutMainLoop();
    return 0;
}

