#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "ebullet3.hpp"
#include "functions.hpp"

using namespace std;

EBullet3::EBullet3(double _x, double _y, double _z, double _tx, double _ty, double _tz) {
    x = _x;
    y = _y;
    z = _z;
    tx = _tx;
    ty = _ty;
    tz = _tz;
    vx = NormalizeX(tx-x,ty-y);
    vy = NormalizeY(tx-x,ty-y);
}

double EBullet3::getX() {
    return x;
}

double EBullet3::getY() {
    return y;
}

double EBullet3::getZ() {
    return z;
}

double EBullet3::getVX() {
    return vx;
}

double EBullet3::getVY() {
    return vy;
}

void EBullet3::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glutSolidSphere(2.5,36,36);
    glPopMatrix();
}

void EBullet3::Move(double dt) {
    x = x + v*vx*dt;
    y = y + v*vy*dt;
}
