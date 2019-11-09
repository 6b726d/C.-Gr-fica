#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "enemy3.hpp"
#include "functions.hpp"
#include "objloader.hpp"

#define PI 3.14159265

using namespace std;

Enemy3::Enemy3(double _x, double _y, double _z, ObjLoader* _obj) {
    x = _x;
    y = _y;
    z = _z;
    obj = _obj;
}

double Enemy3::getX() {
    return x+(r*cos(angle*(PI/180)));
}

double Enemy3::getY() {
    return y+(r*sin(angle*(PI/180)));
}

double Enemy3::getZ() {
    return z;
}

double Enemy3::getSX() {
    return x+((r-20)*cos(angle*(PI/180)));
}

double Enemy3::getSY() {
    return y+((r-20)*sin(angle*(PI/180)));
}

double Enemy3::getRTime() {
    return rtime;
}

bool Enemy3::getShoot() {
    return shoot;
}

void Enemy3::setX(double nX) {
    x = nX;
}

void Enemy3::setY(double nY) {
    y = nY;
}

void Enemy3::setZ(double nZ) {
    z = nZ;
}

void Enemy3::Reset() {
    lmov = 0.0;
    shoot = false;
    angle = 90.0;
    r = 0.0;
    x = Limit_Random();
    y = 340.0;
    z = 0.0;
}

void Enemy3::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(angle,0.0,0.0,1.0);
    glTranslated(r,0.0,0.0);
    glRotated(lmov,1.0,0.0,0.0);
    glRotated(-90.0,0.0,0.0,1.0);
    glScaled(10.0,10.0,10.0);
    obj->display();
    glPopMatrix();
}

void Enemy3::Move(double dt, double tx, double ty, double tz) {
    //Trace Move
    if (fabs(y-ty) >= 100) {
        shoot = false;
        if (x > (tx+0.1)) {
            lmov = -9.0;
            x = x - v*dt;
        }
        else if (x < (tx-0.1)) {
            lmov = 9.0;
            x = x + v*dt;
        }
        else {
            lmov = 0.0;
            x = x;
        }
        y = y - v*dt;
    }
    //Normal Move
    else if (angle >= 630) {
        shoot = false;
        x = x;
        y = y - v*dt;
    }
    //Path Move
    else {
        lmov = 0.0;
        shoot = true;
        angle = angle + v*dt;
        r = 100.0;
        x = tx;
        y = ty;
    }
}

