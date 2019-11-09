#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

using namespace std;

class EBullet1 {
    double x,y,z;
    double v = 250.0;
public:
    EBullet1(double _x, double _y, double _z);
    double getX();
    double getY();
    double getZ();
    void Draw();
    void Move(double dt);
};
