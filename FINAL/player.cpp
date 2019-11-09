#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

#include "player.hpp"
#include "objloader.hpp"

using namespace std;

Player::Player(double _x, double _y, double _z, int _lifes, int _score, int _bombs, int _tshot, ObjLoader* _obj) {
    x = _x;
    y = _y;
    z = _z;
    lifes = _lifes;
    score = _score;
    bombs = _bombs;
    tshot = _tshot;
    obj = _obj;
}

double Player::getX() {
    return x;
}

double Player::getY() {
    return y;
}

double Player::getZ() {
    return z;
}

double Player::getSX() {
    return x;
}

double Player::getSY() {
    return y+25;
}

double Player::getRTime() {
    return rtime;
}

int Player::getLifes() {
    return lifes;
}

int Player::getScore() {
    return score;
}

int Player::getBombs() {
    return bombs;
}

int Player::getTShot() {
    return tshot;
}

void Player::setLifes(int nLifes) {
    lifes = nLifes;
}

void Player::setScore(int nScore) {
    score = nScore;
}

void Player::setBombs(int nBombs) {
    bombs = nBombs;
}

void Player::setTShot(int nTShot) {
    tshot = nTShot;
}

void Player::Reset() {
    lmov = 0.0;
    x = 0.0;
    y = -70.0;
    z = 0.0;
    lifes = 3;
    score = 0;
    bombs = 0;
    tshot = 0;
}

void Player::Draw() {
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(lmov,0.0,1.0,0.0);
    glRotated(90.0,1.0,0.0,0.0);
    glScaled(35.0,35.0,35.0);
    obj->display();
    glPopMatrix();
}

void Player::MoveUp(bool b) {
    MUp = b;
}

void Player::MoveDown(bool b) {
    MDown = b;
}

void Player::MoveLeft(bool b) {
    MLeft = b;
}

void Player::MoveRight(bool b) {
    MRight = b;
}

void Player::Move(double dt) {
    if (MUp==true && y<30) {
        y = y + v*dt;
    }
    else {
        y = y;
    }
    if (MDown==true && y>-340) {
        y = y - v*dt;
    }
    else {
        y = y;
    }
    if (MLeft==true && x>-290) {
        lmov = lmov - 6.0*dt;
        x = x - v*dt;
    }
    else {
        x = x;
    }
    if (MRight==true && x<290) {
        lmov = lmov + 6.0*dt;
        x = x + v*dt;
    }
    else {
        x = x;
    }
}
