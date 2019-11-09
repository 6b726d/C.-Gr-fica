#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "ebullet2.hpp"
#include "functions.hpp"

using namespace std;

EBullet2::EBullet2(double _x, double _y, double _z, double _tx, double _ty, double _tz) {
    x = _x;
    y = _y;
    z = _z;
    tx = _tx;
    ty = _ty;
    tz = _tz;
    vx = NormalizeX(tx-x,ty-y);
    vy = NormalizeY(tx-x,ty-y);
}

double EBullet2::getX() {
    return x;
}

double EBullet2::getY() {
    return y;
}

double EBullet2::getZ() {
    return z;
}

void EBullet2::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glutSolidSphere(2.5,36,36);
    glPopMatrix();
}

void EBullet2::Move(double dt) {
    x = x + v*vx*dt;
    y = y + v*vy*dt;
}
