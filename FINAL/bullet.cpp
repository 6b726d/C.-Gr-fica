#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "bullet.hpp"

using namespace std;

Bullet::Bullet(double _x, double _y, double _z, int _type) {
    x = _x;
    y = _y;
    z = _z;
    type = _type;
    if (type == 0) {
        r = 2.5;
        v = 150;
    }
    else if (type == 1) {
        r = 3.5;
        v = 150;
    }
    else {
        r = 3.5;
        v = 250;
    }
}

double Bullet::getX() {
    return x;
}

double Bullet::getY() {
    return y;
}

double Bullet::getZ() {
    return z;
}

double Bullet::getType() {
    return type;
}

double Bullet::getR() {
    return r;
}

void Bullet::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glutSolidSphere(r,36,36);
    glPopMatrix();
}

void Bullet::Move(double dt) {
    y = y + v*dt;
}
