#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "ebullet1.hpp"

using namespace std;

EBullet1::EBullet1(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

double EBullet1::getX() {
    return x;
}

double EBullet1::getY() {
    return y;
}

double EBullet1::getZ() {
    return z;
}

void EBullet1::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glutSolidSphere(2.5,36,36);
    glPopMatrix();
}

void EBullet1::Move(double dt) {
    y = y - v*dt;
}
