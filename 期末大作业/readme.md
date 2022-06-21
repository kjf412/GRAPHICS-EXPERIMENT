# 一.实验背景与实验内容
## （一）实验背景：
本学期学会使用OpenGl。学会了画线算法、裁剪算法、二维变换、三维变换、曲线与曲面、消音算法、键鼠交互等知识。在此基础上，本实验进行三维图形渲染，进行纹理贴图和光照映射，并加入键鼠交互、平移、旋转等操作。
## （二）实验内容；
利用Visual C++, OpenGL, Java等工具，实现三维图形渲染，自定义三维图形，三维图形不能仅仅是简单的茶壶、球体、圆柱体、圆锥体等图形，渲染过程须加入纹理、色彩、光照、阴影、透明等效果，可采用光线跟踪、光照明模型、纹理贴图、纹理映射等算法。
# 二.开发工具
clion, OpenGL, Java等工具。
# 三.程序设计及实现目的及基本模块介绍
## （一）程序设计
本程序可以分为基本图形绘制、纹理贴图、三维变换三个部分。
## （二）实现目的
基本图形绘制：用于进行茶壶和桌子的绘制。
纹理贴图：进行三维渲染：读取、加载、并贴图的功能。
三维变换：对茶壶和桌子进行旋转、平移等操作。
## （三）基本模块介绍
1. 基本图形绘制：有三个函数：Draw()、Draw_Leg()、drawCube()函数
1. Draw（）函数：实现了绘制茶壶、桌子的场景绘制
2. Draw_Leg（）函数：定义了桌子四条腿的长宽高，实现画桌子腿的功能
3. drawCube（）函数：由于纹理映射需要边界，本函数设定立方体的边界以实现纹理映射。
2. 纹理贴图：有三个函数：texload()、LoadBitmapFile()、generateTex()
1. texload（）函数：函数将已读到的纹理图片进行加载
2. LoadBitmapFile（）函数：通过fopen读取bmp图片
3. generateTex（）函数：生成自定义纹理
3.三维变换：有四个函数：key()、PingYi()、motionROt()、mouseMove()
1.key（）函数：实现切换纹理、三维线框图等功能
2.PingYi（）函数：实现了键盘的上下左右控制平移功能
3.motionROt（）函数：实现鼠标左键摁住时进行旋转的功能。
4.mouseMove（）函数：鼠标功能函数
# 四.关键算法的理论介绍和程序实现步骤
## （一）关键算法的理论介绍
1.	读纹理图片
利用C标准库中的fopen函数，以二进制只读形式加载图像。 filePtr = fopen( filename , "rb" )。将位图看作数据流，它的前几位存储了关于位图的一些信息，如大小、类型、地址、色深、压缩等信息，将这几位信息映射到程序中位图文件头结构体以及信息头结构体中。映射完成后，再把剩下的位图具体数据存储起来，然后交换像素信息保证最后以RGB形式存储。
2.	加载纹理
在读入图片后，用bitmapData指针指向图片信息，开始纹理加载。
首先调用如下函数进行纹理与纹理存储对象的绑定：
glBindTexture(GL_TEXTURE_2D, texture);
接下来指定过滤方式：//指定当前纹理的放大/缩小过滤方式
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
这里使用了两个参数：
GL_TEXTURE_MAG_FILTER和GL_TEXTURE_MIN_FILTER。前者代表了待映射纹理像素少于一个纹理单元的像素时，以怎样的方式映射；后者代表了待映射纹理像素多于一个纹理单元的像素时，以怎样的方式映射。
第三个参数我们使用了GL_NEAREST和GL_LINEAR两种，前者取4个坐标上最接近待映射纹理像素的颜色，后者取坐标上带映射纹理接近像素的平均值。（曼哈顿距离）
3.	纹理贴图
加载好纹理并进行预处理后，将纹理与物体结合，将绘制物体的函数放在开启纹理glEnable与关闭纹理glDisable之间。
实现光照时，使用了两种参数：一个保证纹理和光照混合，一个单纯绘制纹理而不考虑光照。
// 设置纹理受光照影响
glTexEnvf( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE ); 
//设置纹理不受光照影响
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
## （二）程序实现步骤
 ![7](https://user-images.githubusercontent.com/87750093/174807502-e17d2d7f-67e2-47c7-b8cb-a521e3ee59b7.png)
![8](https://user-images.githubusercontent.com/87750093/174807515-f3027d31-7732-4e60-bc5d-4f028f0116b3.png)

 
# 五.实验运行屏幕截图
## （一）实验运行屏幕截图
 ![1](https://user-images.githubusercontent.com/87750093/174807067-2e7d4405-52af-428e-aa8a-cc1a4d54ec01.png)

 ![2](https://user-images.githubusercontent.com/87750093/174807081-6062146d-e679-41c8-9b9b-f1509df4701e.png)

 ![3](https://user-images.githubusercontent.com/87750093/174807125-691e2fde-d646-4309-8412-74291bbbcceb.png)

## （二）运行结果分析
运行结果图中有茶壶和桌子两个部分：茶壶部分纹理贴图的图片是星空图；桌子部分的贴图是木头的纹理图片。
茶壶纹理：
 ![5](https://user-images.githubusercontent.com/87750093/174807177-14711138-dad3-4432-988a-400b447056f5.png)

桌子纹理：
 ![6](https://user-images.githubusercontent.com/87750093/174807236-c2b6d074-ed51-4030-95f2-8d8a25ab95f2.jpg)

其中两者均有光照效果，茶壶的光照效果更为明显。
## （三）存在问题
茶壶的纹理贴图只能是4个相同图片相拼接。目前找不到仅一张图片贴图的方法。
六.实验体会及小结
本实验中运用到了三维渲染、线框图、鼠标和键盘、光照明模型的交互等知识。
在本次实验的实践过程中，我学会了三维渲染的全过程，包括读取、加载、贴图的代码运用。其中遇到了图片文件读取失败，bitmapImage指针是空指针，最终发现不能仅仅将图片后缀名改为bmp文件，而应该在图片编辑中将图片另存为bmp文件格式，否则转为bitmap形式会导致指针为空的问题。
在实验过程中，运用到自己之前很不擅长的三维变换，在尝试、改错，最终得到正确结果的过程中，对三维几何变换的代码运用更加得心应手，并且目前可以熟练的运用键鼠交互，实现更加方便的操作。刚开始着手去做是在借鉴别人学习成果的过程，在通过阅读、搜索材料、实践的过程，学会了运用其中的原理，使自己对图形学的认识更深了一个层次。
# 七.参考文献
[1]张锐. OpenGL三维场景模型的建立与实现[D].华中科技大学,2010.
# 八.附录
代码：
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"

#define BITMAP_ID 0x4D42
#define Height 16
#define Width 16
GLubyte image[Height][Width][3];  // 图像数据

float Xtheta=0,Ytheta=-90;//定义旋转角度、绕x轴旋转、绕y轴旋转
float oldx=0,oldy=0;//记录旧的点

int status = 0;
int status2 = 1;
bool bPersp = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

GLuint texture[3];
void Draw_Leg();

//读纹理图片
unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;    // 文件指针
    BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头
    unsigned char    *bitmapImage;        // bitmap图像数据
    int    imageIdx = 0;        // 图像位置索引
    unsigned char    tempRGB;    // 交换变量

    // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("file not open\n");
        return NULL;
    }
    // 读入bitmap文件图
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    // 读入bitmap信息头
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    // 将文件指针移至bitmap数据
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    // 为装载图像数据创建足够的内存
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    // 验证内存是否创建成功
    if (!bitmapImage) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }

    // 读入bitmap图像数据
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    // 确认读入成功
    if (bitmapImage == NULL) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    // 关闭bitmap图像文件
    fclose(filePtr);
    return bitmapImage;
}

//加载纹理的函数
void texload(int i, const char *filename)
{
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
    unsigned char*   bitmapData;                                       // 纹理数据

    bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    // 指定当前纹理的放大/缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
                 0,         //mipmap层次(通常为，表示最上层)
                 GL_RGB,    //我们希望该纹理有红、绿、蓝数据
                 bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2
                 bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2
                 0, //边框(0=无边框, 1=有边框)
                 GL_RGB,    //bitmap数据的格式
                 GL_UNSIGNED_BYTE, //每个颜色数据的类型
                 bitmapData);    //bitmap数据指针
}
//自定义纹理
void generateTex()
{
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            int x = ((i & 4 ) ^(j & 4 )) * 255;
            image[i][j][0] = 0;
            image[i][j][1] = (GLubyte)x;
            image[i][j][2] = (GLubyte)x;
        }
    }
}
//定义纹理的函数
void init()
{
    glGenTextures(3, texture); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
    texload(0, "xuanran8.BMP");
    texload(1, "xuanran3.BMP");
    //texload(2, "Spot.bmp");
    //下面生成自定义纹理
    generateTex();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大过滤，线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//缩小过滤，线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S方向重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//T方向重复
}
void drawCube()
{
    int i, j;
    const GLfloat x1 = -0.5, x2 = 0.5;
    const GLfloat y1 = -0.5, y2 = 0.5;
    const GLfloat z1 = -0.5, z2 = 0.5;

    //指定六个面的四个顶点，每个顶点用3个坐标值表示
    GLfloat point[6][4][3] = {
            { { x1,y1,z1 },{ x2,y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },
            { { x1,y1,z1 },{ x2,y1,z1 },{ x2,y1,z2 },{ x1,y1,z2 } },
            { { x2,y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,y1,z2 } },
            { { x1,y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,y1,z2 } },
            { { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },
            { { x1,y1,z2 },{ x2,y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }
    };
    int dir[4][2] = { {1,1},{1,0},{0,0},{0,1} };
    //设置正方形绘制模式

    glBegin(GL_QUADS);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            glTexCoord2iv(dir[j]);
            glVertex3fv(point[i][j]);
        }
    }
    glEnd();

}

void Draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[status]);  //选择纹理texture[status]
    glPushMatrix();
    glTranslatef(0, 0, 7+1);
    glRotatef(90, 1, 0, 0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置纹理受光照影响
    glutSolidTeapot(5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);    //关闭纹理texture[status]

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[status2]);  //选择纹理texture[status2]

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置纹理不受光照影响
    glPushMatrix();
    glTranslatef(0, 0, 3);
    glScalef(16, 16, 2);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, 7, -1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 7, -1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, -7, -1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, -7, -1.5);
    Draw_Leg();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D); //关闭纹理texture[status2]
}

void Draw_Leg()
{
    glScalef(2,2, 7);
    drawCube();
}

void updateView(int width, int height)
{
    glViewport(0, 0, width, height);//设置视窗大小

    glMatrixMode(GL_PROJECTION);//设置矩阵模式为投影
    glLoadIdentity();   //初始化矩阵为单位矩阵

    float whRatio = (GLfloat)width / (GLfloat)height;  //设置显示比例
    if (bPersp) {
        gluPerspective(45.0f, whRatio, 0.1f, 100.0f); //透视投影
        //glFrustum(-3, 3, -3, 3, 3,100);
    }
    else {
        glOrtho(-3, 3, -3, 3, -100, 100);  //正投影
    }

    glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型
}

void reshape(int width, int height)
{
    if (height == 0)      //如果高度为0
    {
        height = 1;   //让高度为1（避免出现分母为0的现象）
    }

    wHeight = height;
    wWidth = width;

    updateView(wHeight, wWidth); //更新视角
}

void idle()
{
    glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
        case 'o': {bWire = !bWire; break; }
        case 'c': {
            eye[2] += 0.2f;
            center[2] += 0.2f;
            break;
        }
        case 'r': { //切换茶壶纹理
            if (status == 0)status = 2;
            else if (status == 2)status = 0;
            break;
        }
    }
    updateView(wHeight, wWidth);//更新视角
}
void PingYi(int key,int x,int y)
{
    switch(key){
        case GLUT_KEY_LEFT: {
            eye[0] -= 0.2f;
            center[0] -= 0.2f;
            break;
        }
        case GLUT_KEY_RIGHT: {
            eye[0] += 0.2f;
            center[0] += 0.2f;
            break;
        }
        case GLUT_KEY_UP: {
            eye[1] -= 0.2f;
            center[1] -= 0.2f;
            break;
        }
        case GLUT_KEY_DOWN: {
            eye[1] += 0.2f;
            center[1] += 0.2f;
            break;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓存和深度缓存
    glLoadIdentity();    //初始化矩阵为单位矩阵

    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);                // 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //设置多边形绘制模式：正反面，线型
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //设置多边形绘制模式：正反面，填充
    }

    glEnable(GL_DEPTH_TEST);//开启深度测试
    glEnable(GL_LIGHTING);  //开启光照模式

    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { 5,5,5,1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);//光源位置
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);//定义白色
    glEnable(GL_LIGHT0);//开启第0号光源

    glRotatef(Xtheta,0.0f,1.0f,0.0f);//根据鼠标移动距离旋转物体
    glRotatef(Ytheta,1.0f,0.0f,0.0f);
    glScalef(0.2, 0.2, 0.2);//缩放
    Draw();//绘制场景

    glutSwapBuffers(); //交换缓冲区
}

void motionROt(int x,int y)//实现摁住时，计算旋转量，实现旋转
{
    GLint deltax = x-oldx;
    GLint deltay = y-oldy;
    Xtheta += 360 * (GLfloat)deltax / (GLfloat)600;//根据屏幕上鼠标滑动的距离来设置旋转的角度
    Ytheta += 360 * (GLfloat)deltay / (GLfloat)600;
    oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
    oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
    display();
}
void mouseMove(int button, int state, int x, int y)//实现摁住鼠标移动观察茶壶
{
    oldx = x;//当左键按下时记录鼠标坐标
    oldy = y;
    if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        glutMotionFunc(motionROt);
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);//对glut的初始化
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    //初始化显示模式:RGB颜色模型，深度测试，双缓冲
    glutInitWindowSize(600, 600);//设置窗口大小
    glutCreateWindow("期末三维渲染");//设置窗口标题

    glutDisplayFunc(display); //注册绘制回调函数
    glutReshapeFunc(reshape);   //注册重绘回调函数
    glutMouseFunc(mouseMove);
    glutKeyboardFunc(key); //注册按键回调函数
    glutSpecialFunc(PingYi);
    glutIdleFunc(idle);//注册全局回调函数：空闲时调用
    init(); //初始化纹理
    glutMainLoop();  // glut事件处理循环
    return 0;
}


