#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

using namespace std;

class Bullet {
    double x,y,z;
    int type;
    double r,v;
public:
    Bullet(double _x, double _y, double _z, int _type);
    double getX();
    double getY();
    double getZ();
    double getType();
    double getR();
    void Draw();
    void Move(double dt);
};
