#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

using namespace std;

class EBullet2 {
    double x,y,z;
    double tx,ty,tz;
    double vx,vy;
    bool trace = true;
    char mx = '=';//
    char my = '=';//
    double v = 150.0;
public:
    EBullet2(double _x, double _y, double _z, double _tx, double _ty, double _tz);
    double getX();
    double getY();
    double getZ();
    void Draw();
    void Move(double dt);
    //void Move(double dt, double tx, double ty, double tz);
};
