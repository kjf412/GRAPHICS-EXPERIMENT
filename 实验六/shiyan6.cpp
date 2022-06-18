#include <iostream>
#include "stdlib.h"
#include "math.h"
#include "GL/glut.h"
#include<vector>
#include<algorithm>

const int window_width = 600, window_height = 600;//设置窗口的宽高
using namespace std;
typedef GLfloat M[1][3];
typedef GLfloat MB[3][3];//变换矩阵
struct point
{
    float x, y;
    point(){}
    point(float xx, float yy):
            x(xx), y(yy) {}
};
vector<point> vertice; //顶点

void ErWeiBianHuan();
void PingYi(GLint tx,GLint ty);
void myMouse(int button, int state, int x, int y);
void display();
void draw_a_line();
void XuanZhuan(int o);
void BiLi(int n);
void DuiChen_x();

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glPointSize(1);
    glBegin(GL_LINES);
    //PolyScan();
    draw_a_line();
    glEnd();
    glFlush();
}
void draw_a_point(float x, float y)
{
    glBegin(GL_POINTS);
    glColor3f(0, 1, 1);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}
void draw_a_line(){
    glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
    glColor3f(0, 1, 1);
    glBegin(GL_LINES);
    for (int i = 0; i < vertice.size(); i++)
    {
        if (i == vertice.size() - 1)//画完最后一个点，使其闭合
        {
            glVertex2f(vertice[0].x, vertice[0].y);
            glVertex2f(vertice[i].x, vertice[i].y);
        }
        else
        {
            glVertex2f(vertice[i].x, vertice[i].y);
            glVertex2f(vertice[i + 1].x, vertice[i + 1].y);
        }
    }
    glEnd();
    glFlush();
}
void myMouse(int button, int state, int x, int y)
{
    //左键
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        draw_a_point(x-300,300-y);

        point p(x-300,300-y);
        vertice.push_back(p);
        cout << "顶点" << vertice.size() << ": (" << x-300 << ", " << 300 - y << ")" << endl;
    }
    //右键
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
        glColor3f(0, 1, 1);

        //绘制多边形
        glBegin(GL_LINES);
        for (int i = 0; i < vertice.size(); i++)
        {
            if (i == vertice.size() - 1)//画完最后一个点，使其闭合
            {
                glVertex2f(vertice[0].x, vertice[0].y);
                glVertex2f(vertice[i].x, vertice[i].y);
            }
            else
            {
                glVertex2f(vertice[i].x, vertice[i].y);
                glVertex2f(vertice[i + 1].x, vertice[i + 1].y);
            }
        }
        glEnd();
        glFlush();
    }

    //鼠标中间
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        //cout << "center: (" << x << ", " << y << ")" << endl;
        //BoundaryFill4(x, window_height - y);
        //BoundaryFill4_Stack(x, window_height - y);

        cout << "多边形顶点个数为" << vertice.size() << "。 " << "请选择二维几何类型。" << endl;
        //PolyScan();
        ErWeiBianHuan();
    }
}
//矩阵乘法
void JuZhen(M m1,MB m2){
    M temp;
    for(int row=0;row<1;row++){
        for(int col=0;col<3;col++){
            temp[row][col]=m1[row][0]*m2[0][col]+m1[row][1]*m2[1][col]+m1[row][2]*m2[2][col];
        }
    }
    for(int col=0;col<3;col++){
        m1[0][col]=temp[0][col];
    }
}
void ErWeiBianHuan(){
    int choose;
    cout<<"请输入您的选择:\n0.退出\n1.平移变换\n2.旋转变换\n3.比例变换\n4.关于x对称\n";
    cin>>choose;
    if(choose==1){
        PingYi(100,100);
        draw_a_line();
    }else if(choose==2){
        XuanZhuan(90);
        draw_a_line();
    }else if(choose==3){
        BiLi(2);
        draw_a_line();
    }else if(choose==4){
        DuiChen_x();
        draw_a_line();
    }
}
void PingYi(GLint tx,GLint ty){
    GLint k;
    cout<<"x轴平移"<<tx<<"，y轴平移"<<ty;
    for(k=0;k<vertice.size();k++){
        M m1={vertice[k].x,vertice[k].y,1};
        MB m2={{1, 0, 0}, {0, 1, 0}, {(GLfloat)tx, (GLfloat)ty, 1}};
        JuZhen(m1,m2);
        vertice[k].x=m1[0][0];
        vertice[k].y=m1[0][1];
        draw_a_point(vertice[k].x,vertice[k].y);
    }

}
void XuanZhuan(int o){
    GLint k;
    cout<<"旋转"<<o<<"度\n";
    for(k=0;k<vertice.size();k++){
        M m1={vertice[k].x,vertice[k].y,1};
        MB m2={{(GLfloat)cos(o), (GLfloat)sin(o), 0}, {(GLfloat)-sin(o), (GLfloat)cos(o), 0}, {0, 0, 1}};
        JuZhen(m1,m2);
        vertice[k].x=m1[0][0];
        vertice[k].y=m1[0][1];
        draw_a_point(vertice[k].x,vertice[k].y);
    }
}
void BiLi(int n){
    GLint k;
    cout<<"比例变换"<<n<<"倍\n";
    for(k=0;k<vertice.size();k++){
        M m1={vertice[k].x,vertice[k].y,1};
        MB m2={{(GLfloat)n, 0, 0}, {0, (GLfloat)n, 0}, {0, 0, 1}};
        JuZhen(m1,m2);
        vertice[k].x=m1[0][0];
        vertice[k].y=m1[0][1];
        draw_a_point(vertice[k].x,vertice[k].y);
    }
}
void DuiChen_x(){
    GLint k;
    cout<<"关于x轴对称\n";
    for(k=0;k<vertice.size();k++){
        M m1={vertice[k].x,vertice[k].y,1};
        MB m2={{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
        JuZhen(m1,m2);
        vertice[k].x=m1[0][0];
        vertice[k].y=m1[0][1];
        draw_a_point(vertice[k].x,vertice[k].y);
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 50);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("二维几何变换");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300,-300, 300);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glutMouseFunc(&myMouse);
    glutDisplayFunc(&display);

    glutMainLoop();
    return 0;
}
