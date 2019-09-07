#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

#define KEY_ESC 27
#define PI 3.14159265

void Square(double x, double y, double a) {
    //a=arista
    glBegin(GL_LINE_LOOP);
    glColor3d(100,100,100);
    glVertex2d(x-(a/2),y-(a/2));
    glVertex2d(x+(a/2),y-(a/2));
    glVertex2d(x+(a/2),y+(a/2));
    glVertex2d(x-(a/2),y+(a/2));
    glEnd();
}

void Circle(double x, double y, double r) {
    //r=radio
    double angle = 0;
    double px = 0;
    double py = 0;
    glBegin(GL_LINE_LOOP);
    glColor3d(100,100,100);
    for(int i=0; i<=100; i++){
        angle = 2 * PI * i / 100;
        px = r*cos(angle);
        py = r*sin(angle);
        glVertex2d(px+x,py+y);
     }
     glEnd();
}

//P3
void Fun1(double x, double y, double r, int c, double a) {
    //r=radio
    //c=cantidad
    //a=acumulado
    double tx = x;
    double ty = y;
    double tr = r;
    for(int i=0; i<c; i++) {
        Circle(tx,ty,tr);
        tx = tx + a;
        tr = tr + a;
    }
}

//P4
void Fun2(double x, double y, double r, int c, double p) {
    //r=radio
    //c=cantidad
    //p=porcetaje de reduccion
    double tx = x;
    double ty = y;
    double tp = r;//Pre-Radio
    double tr = r;
    for(int i=0; i<c; i++) {
        Circle(tx,ty,tr);
        tp = tr;
        tr = tr - (tr*(p/100));
        tx = tx + tp + tr;
    }
}

//P5
void Fun3(double x, double y, double r, int c, double p, double a) {
    //r=radio
    //c=cantidad
    //p=porcetaje de reduccion
    //a=angulo
    double tx = x;
    double ty = y;
    double tp = r;//Pre-Radio
    double tr = r;
    for(int i=0; i<c; i++) {
        Circle(tx,ty,tr);
        tp = tr;
        tr = tr - (tr*(p/100));
        tx = tx + (tp*cos(a*PI/180)) + (tr*cos(a*PI/180));
        ty = ty + (tp*sin(a*PI/180)) + (tr*sin(a*PI/180));
    }
}

//dibuja un simple gizmo
void displayGizmo()
{
	Square(-25,25,10);
	Circle(-25,25,10);
	Fun1(25,25,5,5,2);
	Fun2(-25,-25,10,5,50);
	Fun3(25,-25,10,5,50,90);
}

//
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
	displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}
