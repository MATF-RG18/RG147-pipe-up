#include<iostream>
#include<vector>
#include<map>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cmath>

int index = 0;
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
		GLfloat xtrans,ytrans,ztrans,angleRange,angle;
		
	public:
		
		bool direction=true;
		Pipe(GLfloat x, GLfloat y, GLfloat z, GLfloat rang){
			xtrans=x;
			ytrans=y;
			ztrans=z;
			angleRange = rang;
		}
		void setAngle(GLfloat anglendo){
			angle = anglendo;
		}
		GLfloat getRange(){
			return angleRange;
		}
		GLfloat getCurrentAngle(){
			return angle;
		}
		void drawPipe(){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glRotatef(angle,0,0,1);
				
				glRotatef(90,-1,0,0);
				glTranslatef(xtrans,ytrans,ztrans);
				gluCylinder(qobj, .1,.1,1, 20,16);
				
			glPopMatrix();
		}
		GLfloat getx(){
		    	return xtrans;
		}
		GLfloat gety(){
		    	return ytrans;
		}
		GLfloat getz(){
		    	return ztrans;
		}
		
		
};
std::vector<Pipe> gandra;

void drawTwoLines(GLfloat x, GLfloat y, GLfloat z, GLfloat range){
	glPushMatrix();
		glColor3f(0,1,1);
		glBegin(GL_LINES);
			glVertex3f(x,y,z);
			glVertex3f(x+sin(range),y+cos(range),z);
		glEnd();
	glPopMatrix();
}
void rotation(int index){
	GLfloat rang = gandra[index].getRange();
	GLfloat xcord = gandra[index].getx();
	GLfloat ycord = gandra[index].gety();
	GLfloat zcord = gandra[index].getz();
	drawTwoLines(xcord,ycord,zcord,rang);
	GLfloat currAngle = gandra[index].getCurrentAngle();
	if(abs((int)(currAngle))>90){
		gandra[index].direction = !gandra[index].direction;
		if (gandra[index].direction)
			gandra[index].setAngle(currAngle+2);
		else gandra[index].setAngle(currAngle-2);
	}
	else{
		if (gandra[index].direction)
			gandra[index].setAngle(currAngle+1);
		else gandra[index].setAngle(currAngle-1);
	}
	
	
	glutPostRedisplay();
	
	//glutTimerFunc(100,rotation,index);
	
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glutTimerFunc(10,rotation,index);
	draw_grids();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluPerspective(50.0, 1.0, 3.0, 7.0); 
	
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0,1,5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	for(auto it: gandra)
		it.drawPipe();
	 
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
	gandra.push_back(Pipe(0,0,0,30));
	
	glutMainLoop();
	return 0;
} 
