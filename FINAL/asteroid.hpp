#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

class ObjLoader;

using namespace std;

class Asteroid {
    double x,y,z;
    double arx,ary,arz;
    double vrx,vry,vrz;
    double v = 200.0;
    ObjLoader* obj;
public:
    Asteroid(double _x, double _y, double _z, ObjLoader* _obj);
    double getX();
    double getY();
    double getZ();
    void setX(double nX);
    void setY(double nY);
    void setZ(double nZ);
    void Reset();
    void Draw();
    void Move(double dt);
};

