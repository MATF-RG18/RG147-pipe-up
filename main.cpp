#include<iostream>
#include<vector>
#include<map>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void draw_grids(){
glBegin(GL_LINES);
			glColor3f(1,0,0);
			glVertex3f(-10,0,0);
			glVertex3f(0,0,0);
			glColor3f(0,1,0);
			glVertex3f(0,10,0);
			glVertex3f(0,0,0);
			glColor3f(0,0,1);
			glVertex3f(0,0,-10);
			glVertex3f(0,0,0);
glEnd();	
}

class Pipe{
	private:
		GLUquadric * qobj = gluNewQuadric();
		GLfloat xtrans,ytrans,ztrans;
		
	public:
		Pipe(GLfloat x, GLfloat y, GLfloat z){
			xtrans=x;
			ytrans=y;
			ztrans=z;
		}
		void drawPipe(){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glTranslatef(xtrans,ytrans,ztrans);
				glRotatef(90,-1,0,0);
				gluCylinder(qobj, .3,.3,1, 20,16);
				
			glPopMatrix();
		}
		
};

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Pipe gandra = Pipe(1,0,0);
	draw_grids();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluPerspective(50.0, 1.0, 3.0, 7.0); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0,1,5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			
			
			
	gandra.drawPipe();
	
	
	glutSwapBuffers();
}

int main(int argc, char** argv){
	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	//callbacks
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
} 
