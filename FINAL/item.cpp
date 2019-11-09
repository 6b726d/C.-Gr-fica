#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "item.hpp"

GLUquadricObj *sphere = NULL;

using namespace std;

Item::Item(double _x, double _y, double _z, int _type) {
    x = _x;
    y = _y;
    z = _z;
    type = _type;
}

double Item::getX() {
    return x;
}

double Item::getY() {
    return y;
}

double Item::getZ() {
    return z;
}

int Item::getType() {
    return type;
}

void Item::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    if (type == 0) {
        texture = 1;
    }
    else if (type == 1) {
        texture = 2;
    }
    else if (type == 2) {
        texture = 3;
    }
    else if (type == 3) {
        texture = 4;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere,5.0,36,36);
    gluDeleteQuadric(sphere);
    glPopMatrix();
}

void Item::Move(double dt) {
    y = y - v*dt;
}

