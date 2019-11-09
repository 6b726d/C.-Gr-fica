#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

using namespace std;

class Particle {
    double x,y,z;
    double vx,vy,vz;//Velocidad
    double t;//Tiempo de Vida
    double a = 15.0;//arista (QUADS)
    GLint texture;
public:
    Particle(double _x, double _y, double _z);
    double getT();
    void Draw();
    void TMove(double dt);
};
