#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "enemy2.hpp"
#include "functions.hpp"
#include "objloader.hpp"

using namespace std;

Enemy2::Enemy2(double _x, double _y, double _z, ObjLoader* _obj) {
    x = _x;
    y = _y;
    z = _z;
    obj = _obj;
}

double Enemy2::getX() {
    return x;
}

double Enemy2::getY() {
    return y;
}

double Enemy2::getZ() {
    return z;
}

double Enemy2::getSX() {
    return x;
}

double Enemy2::getSY() {
    return y;
}

double Enemy2::getRTime() {
    return rtime;
}

void Enemy2::setX(double nX) {
    x = nX;
}

void Enemy2::setY(double nY) {
    y = nY;
}

void Enemy2::setZ(double nZ) {
    z = nZ;
}

void Enemy2::Reset() {
    x = Limit_Random();
    y = 340.0;
    z = 0.0;
}

void Enemy2::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(0.50,0.50,0.50);
    obj->display();
    glPopMatrix();
}

void Enemy2::Move(double dt) {
    y = y - v*dt;
}
