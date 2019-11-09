#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

using namespace std;

//0(Life), 1(Score), 2(Bomb), 3(Upgrade Shot)
class Item {
    double x,y,z;
    int type;
    double v = 100.0;
    GLint texture;
public:
    Item(double _x, double _y, double _z, int _type);
    double getX();
    double getY();
    double getZ();
    int getType();
    void Draw();
    void Move(double dt);
};
