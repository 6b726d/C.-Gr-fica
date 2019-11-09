#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "enemy1.hpp"
#include "functions.hpp"
#include "objloader.hpp"

using namespace std;

Enemy1::Enemy1(double _x, double _y, double _z, ObjLoader* _obj) {
    x = _x;
    y = _y;
    z = _z;
    obj = _obj;
}

double Enemy1::getX() {
    return x;
}

double Enemy1::getY() {
    return y;
}

double Enemy1::getZ() {
    return z;
}

double Enemy1::getSX() {
    return x;
}

double Enemy1::getSY() {
    return y-12.5;
}

double Enemy1::getRTime() {
    return rtime;
}

void Enemy1::setX(double nX) {
    x = nX;
}

void Enemy1::setY(double nY) {
    y = nY;
}

void Enemy1::setZ(double nZ) {
    z = nZ;
}

void Enemy1::Reset() {
    x = Limit_Random();
    y = 340.0;
    z = 0.0;
}

void Enemy1::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(90.0,1.0,0.0,0.0);
    glScaled(1.0,1.0,1.0);
    obj->display();
    glPopMatrix();
}

void Enemy1::Move(double dt) {
    y = y - v*dt;
}
