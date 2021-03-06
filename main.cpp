#include<iostream>
#include<vector>
#include<map>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cmath>

//konstanta pi za uglove
#define PI 3.14159265

GLfloat camx,camy,camz;
int index = 0; //globalni indeks - koja cev se trenutno obradjuje
//funkcija za crtanje koordinatnog sistema
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
//deklaracija funkcije za pravljenje nove cevi
void make_new_pipe(GLfloat x,GLfloat y,GLfloat z,GLfloat angle);

//klasa pipe:
class Pipe{
	private:
		
		GLfloat momentum = (float)(rand()%35+35)/100+index;				//ubrzanje
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
			//crtanje cevi i strelica
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
				glColor3f(0,.2,.8);
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
			//handle pritiskanja tastera space
			if(abs((int)angle)<angleRange){
				make_new_pipe(xtrans+sin(angle*PI/180),ytrans+abs(cos(angle*PI/180)),0,90-10*index);
				
			}
			else{
				std::cout<< "Igra je zavrsena, vas rezultat: "<<index<<std::endl;
				exit(0);
				
			}
		}
		
};
std::vector<Pipe> pipes;

void make_new_pipe(GLfloat x,GLfloat y,GLfloat z,GLfloat angle){
	
	index++;
	pipes.push_back(Pipe(x,y,z,angle));

}

void rotation(int index){
	camx = pipes[index].getx();
	camy = pipes[index].gety();
	camz = pipes[index].getz();
	GLfloat momentum = pipes[index].getMomentum();
	GLfloat currAngle = pipes[index].getCurrentAngle();
	if(abs((int)(currAngle))>90){
		pipes[index].direction = !pipes[index].direction;
		if (pipes[index].direction)
			pipes[index].setAngle(currAngle+momentum);
		else pipes[index].setAngle(currAngle-momentum);
	}
	else{
		if (pipes[index].direction)
			pipes[index].setAngle(currAngle+momentum);
		else pipes[index].setAngle(currAngle-momentum);
	}
	

	
	glutPostRedisplay();	
}
void keeb(unsigned char key,int x, int y){
	switch(key){
		case 32:
			
				pipes[index].stop();
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
	gluPerspective(50.0, 1.0, 3.0, 100.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = {0.2,0.2,0.2,1};
	GLfloat diffuseLight[] = {0.8,0.8,0.8,1};
	GLfloat specularLight[]= {1,1,1,1};

	GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };
    GLfloat diffuse_coeffs[] = { 0.2, 1, 0.2, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
	GLfloat shininess = 30;

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat lightPos[] = {0,20,8,1};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	

	
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix();
		glBegin(GL_POLYGON);
			glColor3f(.3,.3,.3);
			glVertex3f(-100,0,-100);
			glVertex3f(-100,0,+100);
			glVertex3f(+100,0,+100);
			glVertex3f(+100,0,-100);
		glEnd();
	glPopMatrix();
	glLoadIdentity(); 
	
	gluLookAt(camx,camy,4,camx,camy,0, 0.0, 1.0, 0.0);
	for(auto it: pipes)
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
	pipes.push_back(Pipe(0,0,0,90));
	
	glutMainLoop();
	return 0;
} 
