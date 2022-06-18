#include "GL/glut.h"
#include "stdlib.h"
#include "math.h"

GLsizei winWidth=600,winHeight=600;

GLfloat xwcMin=-50.0,xmcMax=50.0;
GLfloat ywcMin=-50.0,ymcMax=50.0;

class wcPt3D{
    public:
        GLfloat x,y,z;
};
void init(){
    glClearColor(1.0,1.0,1.0,0.0);
}
void plotPoint(wcPt3D beCurvePt){
    glBegin(GL_POINTS);
        glVertex2f(beCurvePt.x,beCurvePt.y);
    glEnd();
}
void binomialCoeffs(GLint n,GLint *C){
    GLint k,j;
    for(k=0;k<=n;k++){
        C[k]=1;
        for(j=n;j>=k+1;j--){
            C[k]*=j;
        }
        for(j=n-k;j>=2;j--){
            C[k]/=j;
        }
    }
}
void computerBezPt(GLfloat u,wcPt3D *bezPt,GLint nCtrlPts,wcPt3D *ctrlPts,GLint *C){
    GLint k,n=nCtrlPts-1;
    GLfloat bezBlendFcn;

    bezPt->x=bezPt->y=bezPt->z=0.0;
    for(k=0;k<nCtrlPts;k++){
        bezBlendFcn=C[k]*pow(u,k)*pow(1-u,n-k);
        bezPt->x+=ctrlPts[k].x*bezBlendFcn;
        bezPt->y+=ctrlPts[k].y*bezBlendFcn;
        bezPt->z+=ctrlPts[k].z*bezBlendFcn;
    }
}
void bezier(GLint nCtrlPts,wcPt3D *ctrlPts,GLint nBezCurvePts){
    wcPt3D bezCtrlPts;
    GLfloat u;
    GLint *C,k;

    C=new GLint [nCtrlPts];

    binomialCoeffs(nCtrlPts -1,C);
    for(k=0;k<=nBezCurvePts;k++){
        u=GLfloat(k)/GLfloat(nBezCurvePts);
        computerBezPt(u,&bezCtrlPts,nCtrlPts,ctrlPts,C);
        plotPoint(bezCtrlPts);
    }
    delete []C;
}
void display(){
    GLint nCtrlPts =4,nBezCurvePts=1000;
    wcPt3D ctrlPts [4]={{-40.0,-40.0,0.0},{-10.0,200.0,0.0},
                        {10.0,-200.0,0.0},{40.0,40.0,0.0}};
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    glColor3f(1.0,0.0,0.0);
    bezier(nCtrlPts,ctrlPts,nBezCurvePts);
    glFlush();
}
void winReshapeFcn(GLint newWidth,GLint newHeight){
    glViewport(0,0,newHeight,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin,xmcMax,ywcMin,ymcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Bezier Curve");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
