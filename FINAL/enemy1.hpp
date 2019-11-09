#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

class ObjLoader;

using namespace std;

class Enemy1 {
    double x,y,z;
    double rtime = 0.5;//time_to_reload
    double v = 50.0;
    ObjLoader* obj;
public:
    Enemy1(double _x, double _y, double _z, ObjLoader* _obj);
    double getX();
    double getY();
    double getZ();
    double getSX();
    double getSY();
    double getRTime();
    void setX(double nX);
    void setY(double nY);
    void setZ(double nZ);
    void Reset();
    void Draw();
    void Move(double dt);
};
