#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

#define PI 3.14159265

//GLOBALS
double angle1 = 0.0;
double xo1 = 0.0;
double max1 = 8.0;
double min1 = -8.0;
bool s1 = true;
double yo1 = 0.0;
double ars = 0.0;
double art = 0.0;
double arl = 0.0;
double arm = 0.0;
double ats = 0.0;
double att = 0.0;
double atl = 0.0;
double atm = 0.0;
double vs = 0.01;


//global
int time=0;
int timebase=0;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,255,255);
	glVertex2d(0,0);
	glVertex2d(50,0);
	glVertex2d(0,0);
	glVertex2d(0,50);
	glEnd();
}
/*
void Fun(float dt) {
    angle1 = angle1 + (PI/30)*dt;
    xo1 = 10*cos(angle1);
    yo1 = 10*sin(angle1);
    glTranslatef(xo1,yo1,0);
}
*/

//P1
void Fun1(float dt) {
    angle1 = angle1 + 6.0*dt;
    glRotatef(angle1,0.0,0.0,1.0);
    glTranslatef(5.0,0.0,0.0);
}
//P2
void Fun2(float dt) {
    glTranslatef(xo1,0.0,0.0);
    if ( s1 == true ) {
        if ( xo1 < max1 ) {
           xo1 = xo1 + 1.0*dt;
        }
        else {
            s1 = false;
        }
    }
    else {
        if ( xo1 > min1 ) {
           xo1 = xo1 - 1.0*dt;
        }
        else {
            s1 = true;
        }
    }
}
//P3
void Fun3T(float dt) {
    angle1 = angle1 + 6.0*3.0*dt;
    glRotatef(angle1,0.0,1.0,0.0);
    glTranslatef(3.0,0.0,0.0);
}
//P3
void Fun3C(float dt) {
    angle1 = angle1 + 6.0*2.0*dt;
    glRotatef(angle1,1.0,0.0,0.0);
    glTranslatef(0.0,2.0,0.0);
}
//Parte1
void P1(float dt) {
    Fun2(dt);
    glColor3d(0,0,255);
	glutSolidSphere(0.5,360,360);
	glPushMatrix();
	Fun1(dt);
	glColor3d(100,100,100);
	glutSolidTeapot(1);
	Fun3T(dt);
	glColor3d(0,255,0);
	glutSolidTorus(0.1,0.5,100,100);
	glPopMatrix();
	Fun3C(dt);
	glColor3d(255,0,0);
	glutSolidCube(1);
}

//P4
void DrawSun() {
    glColor3d(255,255,0);
    glutSolidSphere(4,8,8);
}
void DrawEarth() {
    glColor3d(0,0,255);
    glutSolidSphere(2,8,8);
}
void DrawMoon() {
    glColor3d(100,100,100);
    glutSolidSphere(0.5,8,8);
}
void DrawMars() {
    glColor3d(255,0,0);
    glutSolidSphere(1,8,8);
}
void RSun() {
    ars = ars + vs;
    glRotatef(ars,0.0,1.0,0.0);
}
void REarth() {
    art = art + (vs*3.0);
    glRotatef(art,0.0,1.0,0.0);
}
void TEarth() {
    att = att + (vs*2.0);
    glRotatef(att,0.0,1.0,0.0);
    glTranslatef(10.0,0.0,0.0);
}
void RMoon() {
    arl = arl + (vs*1.5);
    glRotatef(arl,0.0,1.0,0.0);
}
void TMoon() {
    atl = atl + (vs*4.0);
    glRotatef(atl,0.0,1.0,0.0);
    glTranslatef(2.5,0.0,0.0);
}
void RMars() {
    arm = arm + (vs);
    glRotatef(arm,0.0,1.0,0.0);
}
void TMars() {
    atm = atm + (vs*2.0);
    glRotatef(atm,0.0,1.0,0.0);
    glTranslatef(18.0,0.0,0.0);
}
//Parte2 (Sistema Solar)
void P2() {
    glPushMatrix();
	RSun();
	DrawSun();
	glPopMatrix();
	glPushMatrix();
	TEarth();
	REarth();
	DrawEarth();
	TMoon();
	RMoon();
	DrawMoon();
	glPopMatrix();
	glPushMatrix();
	TMars();
	RMars();
	DrawMars();
	glPopMatrix();
}

GLvoid window_display()
{
    //glpaint()
    time = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time -timebase)/1000.0;// delta time
    timebase = time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);


	/*dibujar aqui*/
	//dibuja el gizmo
	displayGizmo();

	P1(dt);
	//P2();

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

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
