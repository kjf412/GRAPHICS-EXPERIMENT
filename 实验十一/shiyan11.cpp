#include <iostream>
#include "GL/glut.h"
#include "math.h"
#define DEG_T0_RAD 0.017453

float thera=30.0;
float length=200.0;
float x=300.0,y=200.0;

void init(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,640.0,0.0,480);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x+length*cos(DEG_T0_RAD*thera),y+length*sin(DEG_T0_RAD*thera));
        glVertex2f(x+length*cos(DEG_T0_RAD*(thera+30)),y+length*sin(DEG_T0_RAD*(thera+30)));
    glEnd();
    glFlush();
}
void idleFunc(){
    thera+=0.1;
    if(thera>360){
        thera-=360;
    }
    glutPostRedisplay();
}
void myMouse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
        thera+=5.0;
    }
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN){
        thera-=5.0;
    }
    if(thera>360) thera-=360;
    if(thera<0) thera+=360;
    glutPostRedisplay();
}
void myKeyboard(unsigned char key,int x,int y){
    if(key=='a'||key=='A'){
        thera+=5.0;
    }
    if(key=='s'||key=='S'){
        thera-=5.0;
    }
    if(key=='c'||key=='C'){
        exit(0);
    }
    if(thera>360) thera-=360;
    if(thera<0) thera+=360;
    glutPostRedisplay();//重新调用绘制函数
}
int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("jiaohukognzji ");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(&myMouse);
    glutMainLoop();
    return 0;
}
