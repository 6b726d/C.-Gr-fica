#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "particle.hpp"
#include "functions.hpp"

using namespace std;

Particle::Particle(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
    vx = VRandom();
    vy = VRandom();
    vz = VRandom();
    t = TRandom();
    texture = rand()%5 + 6;//
}

double Particle::getT() {
    return t;
}

void Particle::Draw() {
    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUADS);
    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0.0,1.0);
    glVertex3d(x-(a/2),y-(a/2),0.0);
    glTexCoord2d(1.0,1.0);
    glVertex3d(x+(a/2),y-(a/2),0.0);
    glTexCoord2d(1.0,0.0);
    glVertex3d(x+(a/2),y+(a/2),0.0);
    glTexCoord2d(0.0,0.0);
    glVertex3d(x-(a/2),y+(a/2),0.0);
    glEnd();
}

void Particle::TMove(double dt) {
    //Time
    t = t - 2.0*dt;
    //Move
    x = x + vx*dt;
    y = y + vy*dt;
    z = z + vz*dt;
}
