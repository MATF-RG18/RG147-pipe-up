#include<iostream>
#include<vector>
#include<map>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cmath>


#define PI 3.14159265
bool kameraflag=true;
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

void make_new_pipe(GLfloat x,GLfloat y,GLfloat z,GLfloat angle);

class Pipe{
	private:
		GLfloat momentum = (float)(rand()%35+35)/100+index;
		int thisIndex;
		GLUquadric * qobj = gluNewQuadric();
		GLfloat xtrans,ytrans,ztrans,angleRange,angle=0;
		
	public:
		
		bool direction=true;
		Pipe(GLfloat x, GLfloat y, GLfloat z, GLfloat rang){
			xtrans=x;
			ytrans=y;
			ztrans=z;
			angleRange = rang;
			thisIndex=index;
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
		GLfloat getMomentum(){
			return momentum;
		}
		void drawPipe(){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				if(thisIndex==index){
				glPushMatrix();
					glBegin(GL_LINES);
						glColor3f(0,1,0);
						glVertex3f(xtrans,ytrans,ztrans-1);
						glVertex3f(xtrans-sin(angleRange*PI/180),ytrans+1.4,ztrans-1);
						
					glEnd();
					glBegin(GL_LINES);
						glVertex3f(xtrans,ytrans,ztrans-1);
						glVertex3f(xtrans+sin(angleRange*PI/180),ytrans+1.4,ztrans-1);
					glEnd();
				glPopMatrix();
				}
				glColor3f(0,0,1);
				glTranslatef(xtrans,ytrans,ztrans);
				glRotatef(angle,0,0,-1);	
				glRotatef(90,-1,0,0);

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
		
		void stop(){
			if(abs((int)angle)<angleRange){
				make_new_pipe(xtrans+sin(angle*PI/180),ytrans+abs(cos(angle*PI/180)),0,90-10*index);
				
			}
			else{
				std::cout<< "Igra je zavrsena, vas rezultat: "<<index<<std::endl;
				exit(0);
			}
		}
		
};
std::vector<Pipe> gandra;

void make_new_pipe(GLfloat x,GLfloat y,GLfloat z,GLfloat angle){
	
	index++;
	gandra.push_back(Pipe(x,y,z,angle));

}

void rotation(int index){
	GLfloat momentum = gandra[index].getMomentum();
	GLfloat currAngle = gandra[index].getCurrentAngle();
	if(abs((int)(currAngle))>90){
		gandra[index].direction = !gandra[index].direction;
		if (gandra[index].direction)
			gandra[index].setAngle(currAngle+momentum);
		else gandra[index].setAngle(currAngle-momentum);
	}
	else{
		if (gandra[index].direction)
			gandra[index].setAngle(currAngle+momentum);
		else gandra[index].setAngle(currAngle-momentum);
	}
	

	
	glutPostRedisplay();	
}
void keeb(unsigned char key,int x, int y){
	switch(key){
		case 32:
			if(kameraflag)
				gandra[index].stop();
			break;
		case 27:
			exit(0);
			break;
	}

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
	gluLookAt(gandra[index].getx(),gandra[index].gety(),4,gandra[index].getx(),gandra[index].gety(),0, 0.0, 1.0, 0.0);
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
	glutKeyboardFunc(keeb);
	gandra.push_back(Pipe(0,0,0,90));
	
	glutMainLoop();
	return 0;
} 
