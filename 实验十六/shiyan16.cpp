//#include "stdafx.h"
#include<GL\glut.h>
#include<math.h>


float theta=45,phi=60;
float r=2;
void init(){
    GLfloat light_position[]={1.0,1.0,1.0,0.0};//光源位置
    GLfloat light_ambient[]={0.5,0.5,0.5,1.0};//环境光
    GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};//漫反射光
    GLfloat light_specular[]={1.0,1.0,1.0,1.0};//镜面反射光

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

    glEnable(GL_LIGHTING);//开启光源
    glEnable(GL_LIGHT0);//开启特定光源
    glEnable(GL_DEPTH_TEST);//开启深度测试
}

void light_mat_set()
{
    glClearColor(0.8, 0.8, 0.8, 1.0);//设置窗口背景颜色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清屏
    glMatrixMode(GL_PROJECTION);  //指定当前操作的是投影矩阵
    glLoadIdentity();//初始化，指定当前操作的矩阵堆栈的栈顶元素为单位矩阵
    glOrtho(-5,5,-5, 5,-4, 6);//设置裁剪窗口
//设置视点
    gluLookAt(r*sin(theta*3.14159/180)*sin(phi*3.14159/180),r*cos(theta*3.14159/180),r*sin(theta*3.14159/180)*cos(phi*3.14159/180),0.0,0.0,0.0,0.0,0.0,1.0);
    glMatrixMode(GL_MODELVIEW); // 矩阵模式
    glLoadIdentity();
//清空矩阵堆栈
//材料设置
//圆锥
    GLfloat red_ambient[] ={ 1.0, 0.0, 0.0, 1.0 }; //红色环境光
    GLfloat red_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };//红色漫反射光
    GLfloat red_specular[]={ 0.0, 0.0, 0.0, 1.0 };//红色镜面反射光
    GLfloat red_shininess[]= { 50 };// 高光指数
    glMaterialfv(GL_FRONT, GL_AMBIENT, red_ambient);//为材质加上红色环境光
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, red_shininess);
    glutWireCone(0.8,2.0,30,30);
//球
    GLfloat blue_ambient[]={ 0.0, 0.0, 1.0, 1.0 };//蓝色环境光
    GLfloat blue_diffuse[]={1.0, 0.0, 1.0, 1.0};
    GLfloat blue_specular[]={ 0.0, 0.0, 0.0, 1.0 };
    GLfloat blue_shininess[]= { 100 };//高光指数
    glMaterialfv(GL_FRONT, GL_AMBIENT, blue_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blue_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, blue_shininess);
    glTranslatef(2, 3, -1.5);
    glutSolidSphere(0.8, 50, 50);
//圆环
    GLfloat green_ambient[]={ 0.0, 1.0, 0.0, 1.0 };//绿色环境光
    GLfloat green_diffuse[]={1.0, 0.0, 1.0, 1.0};
    GLfloat green_specular[]={ 0.0, 0.0, 0.0, 1.0 };
    GLfloat green_shininess[]= { 100 };//高光指数
    glMaterialfv(GL_FRONT, GL_AMBIENT, green_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, green_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS,green_shininess);
    glTranslatef(0.5, 0.5, 1.5);
    glutWireTorus(0.5,1,30,30);
    glFlush();
}

void myKeyboard(unsigned char key,int x,int y){//键盘控制函数

    switch(key)
    {
        case'A':
        case'a':
            if(phi-1>-180)
                phi=phi-1;
            break;
        case'D':
        case'd':
            if(phi+1<180)
                phi=phi+1;
            break;
        case'S':
        case's':
            if(theta+1<180)
                theta=theta+1;
            break;
        case'W':
        case'w':
            if(theta-1>0)
                theta=theta-1;
            break;

    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); //初始化GLUT库
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//设置显示模式，缓存颜色类型
    glutInitWindowSize(500, 500);//窗口的大小
    glutInitWindowPosition(150, 100);//窗口出现的位置
    glutCreateWindow("Phong关照模型);
//myInit();
    init();
    glutDisplayFunc(light_mat_set);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
}
