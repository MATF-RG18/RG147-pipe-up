//
// Created by dragon on 12/6/18.
//

#include<GL/glut.h>
#include<stdio.h>

static double size=.1;
static char taster;
static int x,y,val;
static void displej(void);
static void tastatura(const char taster, int x, int y);
static void animacija(int val);
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Pipe Up!");
    glClearColor(.4,.3,1,0);
    glutDisplayFunc(displej);
    glutKeyboardFunc(tastatura);
    glutTimerFunc(0,animacija,0);
    glutMainLoop();




    return 0;
}

static void displej(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glutWireTeapot(size);
    glutSwapBuffers();
    gluLookAt()
}

static void animacija(int xD){

    if(val==1){
        size+=.01;}
    glutPostRedisplay();s
    glutTimerFunc(25,animacija,val);


}

static void tastatura(const char taster, int x, int y){
    switch (taster){
        case 'g':
            val=1;
            break;
        case 's':
            val=0;
            break;
    }


}
