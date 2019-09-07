#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <GL/glext.h>

#include "TextureManager.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

//Illimination
GLfloat roofDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat roofSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat roofAmbient[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat roofShininess[] = {6.0f};

GLfloat lx = -20.0;
GLfloat ly = 20.0;
GLfloat lz = 20.0;

GLfloat light0Position[] = {lx,ly,lz,0.0};
GLfloat light0Diffuse [] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat light0Specular [] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat light0Ambient [] = {0.3f, 0.3f, 0.3f, 1.0f};

GLint grass;
GLint wall;
GLint roof;
GLint stree;
GLint ctree;

GLUquadricObj *sphere = NULL;
GLUquadricObj *cylinder = NULL;

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


//variables para el gizmo
float delta_x = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)


///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{

	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}


//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 4 : Textures");


	initGL();
	init_scene();

	grass = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/P4/grass.png", GL_RGBA, GL_RGBA);
	cout << grass << endl;
	wall = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/P4/wall.jpg", GL_BGR_EXT, GL_RGB);
	cout << wall << endl;
	roof = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/P4/roof.jpg", GL_RGB, GL_RGB);
	cout << roof << endl;
	stree = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/P4/tree.jpg", GL_RGB, GL_RGB);
	cout << stree << endl;
	ctree = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/P4/bark.jpg", GL_RGB, GL_RGB);
	cout << ctree << endl;


	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);


	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, roofDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, roofSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roofAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, roofShininess);

    glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
    glEnable(GL_CULL_FACE); //no trata las caras escondidas
    glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
    glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Activa la corrección de perspectiva

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

	glClearColor(RED, GREEN, BLUE, ALPHA);

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_TEXTURE);
}

/*
void Gizmo3D(){


	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();


	return;

}
*/

void DrawGround() {
    //glColor3f(0.0,1.0,0.0);//
    glBindTexture(GL_TEXTURE_2D, grass);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-20.0,0.0,-20.0);
    glTexCoord2f(0.0, 10.0);
    glVertex3f(-20.0,0.0,20.0);
    glTexCoord2f(10.0, 10.0);
    glVertex3f(20.0,0.0,20.0);
    glTexCoord2f(10.0, 0.0);
    glVertex3f(20.0,0.0,-20.0);
    glEnd();
}

void DrawHome() {
    //Walls
    //glColor3f(1.0,0.0,0.0);//
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-10.0,0.0,-10.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.0,0.0,-10.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.0,5.0,-10.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-10.0,5.0,-10.0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0,0.0,-10.0);
    glTexCoord2f(0.62, 1.0);
    glVertex3f(0.0,0.0,-15.0);
    glTexCoord2f(0.62, 0.0);
    glVertex3f(0.0,5.0,-15.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0,5.0,-10.0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0,0.0,-15.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-10.0,0.0,-15.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-10.0,5.0,-15.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0,5.0,-15.0);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-10.0,0.0,-15.0);
    glTexCoord2f(0.62, 1.0);
    glVertex3f(-10.0,0.0,-10.0);
    glTexCoord2f(0.62, 0.0);
    glVertex3f(-10.0,5.0,-10.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-10.0,5.0,-15.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0,5.0,-10.0);
    glTexCoord2f(0.62, 1.0);
    glVertex3f(0.0,5.0,-15.0);
    glTexCoord2f(0.31, 0.62);
    glVertex3f(0.0,7.0,-12.5);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-10.0,5.0,-15.0);
    glTexCoord2f(0.62, 1.0);
    glVertex3f(-10.0,5.0,-10.0);
    glTexCoord2f(0.31, 0.62);
    glVertex3f(-10.0,7.0,-12.5);
    glEnd();
    //Roof
    //glColor3f(0.5,0.5,0.5);//
    glBindTexture(GL_TEXTURE_2D, roof);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.780869,0.624695);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-10.0,5.0,-10.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.0,5.0,-10.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.0,7.0,-12.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-10.0,7.0,-12.5);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.780869,-0.624695);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.0,5.0,-15.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-10.0,5.0,-15.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-10.0,7.0,-12.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0,7.0,-12.5);
    glEnd();
}

void DrawTree() {
    //glColor3f(0.5,0.3,0.1);//
    glPushMatrix();
    glTranslatef(10.0,0.0,-12.5);
    glRotatef(-90.0,1.0,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D, ctree);
    cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricTexture(cylinder, TRUE);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder,1.5,1.0,5.0,36,36);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
    //glColor3f(0.0,1.0,0.0);//
    glPushMatrix();
    glTranslatef(10.0,7,-12.5);
    //ofDisableArbTex();
    glBindTexture(GL_TEXTURE_2D, stree);
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere,3.0,36,36);
    gluDeleteQuadric(sphere);
    glPopMatrix();
}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);


	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);


	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);


	//Gizmo3D();
	DrawGround();
	DrawHome();
	DrawTree();



	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;
    case 'w':
        lz = lz - 20;
		light0Position[2] = lz;
		break;
    case 's':
		lz = lz + 20;
		light0Position[2] = lz;
		break;
    case 'a':
		lx = lx - 20;
		light0Position[0] = lx;
		break;
    case 'd':
		lx = lx + 20;
		light0Position[0] = lx;
		break;
	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}
