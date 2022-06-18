#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<GL/glut.h>
using namespace std;
int window_width = 800, window_height = 600;

struct point
{
    int x, y;
    point(){}
    point(int xx, int yy):
            x(xx), y(yy) {}
};
vector<point> vertice; //顶点

float newcolor[3] = { 0, 1, 1 }; //填充颜色
float boundarycolor[3] = { 0, 0, 0 };  //边界颜色

void draw_a_point(int x, int y);
bool is_equal(float* a, float* b);
void BoundaryFill4_Stack(int x, int y);
void mymouse(int button, int state, int x, int y);


//画点函数
void draw_a_point(int x, int y)
{
    glBegin(GL_POINTS);
    glColor3fv(newcolor);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}
//判断函数
bool is_equal(float* a, float* b)
{
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

//用栈实现的 扫描线形式的填充算法
void BoundaryFill4_Stack(int x, int y)
{
    stack <point> q;
    q.push(point(x, y));
    while (!q.empty())
    {
        point now = q.top();
        q.pop();
        int nowx = now.x, nowy = now.y;
        float color[3];
        glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
        if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
        {
            draw_a_point(nowx, nowy);
            q.push(point(nowx, nowy + 1));
            q.push(point(nowx, nowy - 1));
            q.push(point(nowx + 1, nowy));
            q.push(point(nowx - 1, nowy));
        }
    }
    glEnd();
    glFlush();
}

void mymouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        draw_a_point(x, window_height - y);

        point p(x, window_height - y);
        vertice.push_back(p);
        cout << "顶点" << vertice.size() << ": (" << x << ", " << y << ")" << endl;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
        glColor3fv(boundarycolor);

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
        vertice.clear();
    }

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        cout << "中心点: (" << x << ", " << y << ")" << endl;
        //BoundaryFill4(x, window_height - y);
        BoundaryFill4_Stack(x, window_height - y);
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glPointSize(1);
    glBegin(GL_POINTS);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[])
{
    cout << "点击鼠标左键画点；" << endl << "点击鼠标右键结束画点，形成多边形；" << endl << "点击鼠标中键确定区域填充种子点位置。" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(400, 150);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("区域种子填充");
    glMatrixMode(GL_PROJECTION);/*设置为投影类型模式和其他观察参数*/
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();/*设置为投影类型模式和其他观察参数*/
    //gluOrtho2D(0, window_width, window_height, 0);/*设置为投影类型模式和其他观察参数，观察窗口的大小要与画布大小一致，所以直接设置全局变量即可*/
    gluOrtho2D(0, window_width, 0, window_height); //上面的不可以！！！

    glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
    glClear(GL_COLOR_BUFFER_BIT);

    glutMouseFunc(&mymouse);
    glutDisplayFunc(&display);//自己加的，回调函数
    glutMainLoop();
    return 0;
}
