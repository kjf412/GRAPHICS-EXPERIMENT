#include <iostream>
#include <cstdio>
#include <cmath>
#include <GL/glut.h>

void init();
void Display();
void setPixel(GLint x,GLint y);
void Bresenham(int x0, int y0, int xEnd, int yEnd);
using namespace std;

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
void Bresenham(int x0, int y0, int xEnd, int yEnd){
    float dx=float(xEnd-x0),dy=float(yEnd-y0),k=dy/dx,x=float(x0),y=float(y0);
    if(fabs(dy/dx)<=1){
        float d=0;
        setPixel(x0,y0);
        while(y<float(yEnd)&&x<float(xEnd)){
            if(d<float(0.5)){
                x+=1;
                y=y;
                setPixel(x,y);
            }else{
                x+=1;
                y=y+1;
                d=d-1;//!!一旦y方向上走了一步，d才减一
                setPixel(x,y);
            }
            d=d+k;
        }
    }else{
        float d=0;
        while(y<float(yEnd)&&x<float(xEnd)){
            if(d<float(0.5)){
                x=x;
                y+=1;
                setPixel(x,y);
            }else{
                x=x+1;
                y=y+1;
                d=d-1;//!!一旦x方向上走了一步，d才减一
                setPixel(x,y);
            }
            d=d+1/k;
        }
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

    Bresenham(x,y,xEnd,yEnd);
    glEnd();
    glFlush();
}
int main(int argc, char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham算法");

    init();
    glutDisplayFunc(&Display);
    glutMainLoop();
    return 0;
}
