#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "asteroid.hpp"
#include "functions.hpp"
#include "objloader.hpp"

using namespace std;

Asteroid::Asteroid(double _x, double _y, double _z, ObjLoader* _obj) {
    x = _x;
    y = _y;
    z = _z;
    arx = RARandom();
    ary = RARandom();
    arz = RARandom();
    vrx = RVRandom();
    vry = RVRandom();
    vrz = RVRandom();
    obj = _obj;
}

double Asteroid::getX() {
    return x;
}

double Asteroid::getY() {
    return y;
}

double Asteroid::getZ() {
    return z;
}

void Asteroid::setX(double nX) {
    x = nX;
}

void Asteroid::setY(double nY) {
    y = nY;
}

void Asteroid::setZ(double nZ) {
    z = nZ;
}

void Asteroid::Reset() {
    x = Limit_Random();
    y = 340.0;
    z = 0.0;
}

void Asteroid::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(arz,0.0,0.0,1.0);
    glRotated(ary,0.0,1.0,0.0);
    glRotated(arx,1.0,0.0,0.0);
    glScaled(5.0,5.0,5.0);
    obj->display();
    glPopMatrix();
}

void Asteroid::Move(double dt) {
    //Rotation
    arx = arx + vrx*dt;
    ary = ary + vry*dt;
    arz = arz + vrz*dt;
    //Move
    y = y - v*dt;
    if (y < -340) {
        x = Limit_Random();
        y = 340.0;
	}
}

