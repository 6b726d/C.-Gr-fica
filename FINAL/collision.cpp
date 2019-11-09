#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <vector>
#include <list>

#include <GL/glut.h>

#include "collision.hpp"
#include "functions.hpp"

#include "player.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "enemy1.hpp"
#include "ebullet1.hpp"
#include "enemy2.hpp"
#include "ebullet2.hpp"
#include "enemy3.hpp"
#include "ebullet3.hpp"
#include "item.hpp"


using namespace std;

Collision::Collision() {}

Collision::~Collision() {}

bool Collision::PlayerItem(Player* p, Item* i) {
    if ( ( (i->getX() >= p->getX()-50) && (i->getX() <= p->getX()+50) ) &&
         ( (i->getY() >= p->getY()-50) && (i->getY() <= p->getY()+50) ) ) {
        if (SquareDist(i->getX(),p->getX(),i->getY(),p->getY()) < SquareVar(30)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerAsteroid(Player* p, Asteroid* a) {
    if ( ( (a->getX() >= p->getX()-50) && (a->getX() <= p->getX()+50) ) &&
         ( (a->getY() >= p->getY()-50) && (a->getY() <= p->getY()+50) ) ) {
        if (SquareDist(a->getX(),p->getX(),a->getY(),p->getY()) < SquareVar(35)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEnemy1(Player* p, Enemy1* e1) {
    if ( ( (e1->getX() >= p->getX()-50) && (e1->getX() <= p->getX()+50) ) &&
         ( (e1->getY() >= p->getY()-50) && (e1->getY() <= p->getY()+50) ) ) {
        if (SquareDist(e1->getX(),p->getX(),e1->getY(),p->getY()) < SquareVar(37.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEnemy2(Player* p, Enemy2* e2) {
    if ( ( (e2->getX() >= p->getX()-50) && (e2->getX() <= p->getX()+50) ) &&
         ( (e2->getY() >= p->getY()-50) && (e2->getY() <= p->getY()+50) ) ) {
        if (SquareDist(e2->getX(),p->getX(),e2->getY(),p->getY()) < SquareVar(37.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEnemy3(Player* p, Enemy3* e3) {
    if ( ( (e3->getX() >= p->getX()-50) && (e3->getX() <= p->getX()+50) ) &&
         ( (e3->getY() >= p->getY()-50) && (e3->getY() <= p->getY()+50) ) ) {
        if (SquareDist(e3->getX(),p->getX(),e3->getY(),p->getY()) < SquareVar(37.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEBullet1(Player* p, EBullet1* eb1) {
    if ( ( (eb1->getX() >= p->getX()-50) && (eb1->getX() <= p->getX()+50) ) &&
         ( (eb1->getY() >= p->getY()-50) && (eb1->getY() <= p->getY()+50) ) ) {
        if (SquareDist(eb1->getX(),p->getX(),eb1->getY(),p->getY()) < SquareVar(27.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEBullet2(Player* p, EBullet2* eb2) {
    if ( ( (eb2->getX() >= p->getX()-50) && (eb2->getX() <= p->getX()+50) ) &&
         ( (eb2->getY() >= p->getY()-50) && (eb2->getY() <= p->getY()+50) ) ) {
        if (SquareDist(eb2->getX(),p->getX(),eb2->getY(),p->getY()) < SquareVar(27.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::PlayerEBullet3(Player* p, EBullet3* eb3) {
    if ( ( (eb3->getX() >= p->getX()-50) && (eb3->getX() <= p->getX()+50) ) &&
         ( (eb3->getY() >= p->getY()-50) && (eb3->getY() <= p->getY()+50) ) ) {
        if (SquareDist(eb3->getX(),p->getX(),eb3->getY(),p->getY()) < SquareVar(27.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::BulletAsteroid(Bullet* b, Asteroid* a) {
    if ( ( (b->getX() >= a->getX()-20) && (b->getX() <= a->getX()+20) ) &&
         ( (b->getY() >= a->getY()-20) && (b->getY() <= a->getY()+20) ) ) {
        if (SquareDist(b->getX(),a->getX(),b->getY(),a->getY()) < SquareVar(b->getR()+10)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::BulletEnemy1(Bullet* b, Enemy1* e1) {
    if ( ( (b->getX() >= e1->getX()-25) && (b->getX() <= e1->getX()+25) ) &&
         ( (b->getY() >= e1->getY()-25) && (b->getY() <= e1->getY()+25) ) ) {
        if (SquareDist(b->getX(),e1->getX(),b->getY(),e1->getY()) < SquareVar(b->getR()+12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::BulletEnemy2(Bullet* b, Enemy2* e2) {
    if ( ( (b->getX() >= e2->getX()-25) && (b->getX() <= e2->getX()+25) ) &&
         ( (b->getY() >= e2->getY()-25) && (b->getY() <= e2->getY()+25) ) ) {
        if (SquareDist(b->getX(),e2->getX(),b->getY(),e2->getY()) < SquareVar(b->getR()+12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::BulletEnemy3(Bullet* b, Enemy3* e3) {
    if ( ( (b->getX() >= e3->getX()-25) && (b->getX() <= e3->getX()+25) ) &&
         ( (b->getY() >= e3->getY()-25) && (b->getY() <= e3->getY()+25) ) ) {
        if (SquareDist(b->getX(),e3->getX(),b->getY(),e3->getY()) < SquareVar(b->getR()+12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

//Extra
bool Collision::Enemy1Asteroid(Enemy1* e1, Asteroid* a) {
    if ( ( (a->getX() >= e1->getX()-25) && (a->getX() <= e1->getX()+25) ) &&
         ( (a->getY() >= e1->getY()-25) && (a->getY() <= e1->getY()+25) ) ) {
        if (SquareDist(a->getX(),e1->getX(),a->getY(),e1->getY()) < SquareVar(22.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy1EBullet2(Enemy1* e1, EBullet2* eb2) {
    if ( ( (eb2->getX() >= e1->getX()-25) && (eb2->getX() <= e1->getX()+25) ) &&
         ( (eb2->getY() >= e1->getY()-25) && (eb2->getY() <= e1->getY()+25) ) ) {
        if (SquareDist(eb2->getX(),e1->getX(),eb2->getY(),e1->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy1EBullet3(Enemy1* e1, EBullet3* eb3) {
    if ( ( (eb3->getX() >= e1->getX()-25) && (eb3->getX() <= e1->getX()+25) ) &&
         ( (eb3->getY() >= e1->getY()-25) && (eb3->getY() <= e1->getY()+25) ) ) {
        if (SquareDist(eb3->getX(),e1->getX(),eb3->getY(),e1->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy2Asteroid(Enemy2* e2, Asteroid* a) {
    if ( ( (a->getX() >= e2->getX()-25) && (a->getX() <= e2->getX()+25) ) &&
         ( (a->getY() >= e2->getY()-25) && (a->getY() <= e2->getY()+25) ) ) {
        if (SquareDist(a->getX(),e2->getX(),a->getY(),e2->getY()) < SquareVar(22.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy2EBullet1(Enemy2* e2, EBullet1* eb1) {
    if ( ( (eb1->getX() >= e2->getX()-25) && (eb1->getX() <= e2->getX()+25) ) &&
         ( (eb1->getY() >= e2->getY()-25) && (eb1->getY() <= e2->getY()+25) ) ) {
        if (SquareDist(eb1->getX(),e2->getX(),eb1->getY(),e2->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy2EBullet3(Enemy2* e2, EBullet3* eb3) {
    if ( ( (eb3->getX() >= e2->getX()-25) && (eb3->getX() <= e2->getX()+25) ) &&
         ( (eb3->getY() >= e2->getY()-25) && (eb3->getY() <= e2->getY()+25) ) ) {
        if (SquareDist(eb3->getX(),e2->getX(),eb3->getY(),e2->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy3Asteroid(Enemy3* e3, Asteroid* a) {
    if ( ( (a->getX() >= e3->getX()-25) && (a->getX() <= e3->getX()+25) ) &&
         ( (a->getY() >= e3->getY()-25) && (a->getY() <= e3->getY()+25) ) ) {
        if (SquareDist(a->getX(),e3->getX(),a->getY(),e3->getY()) < SquareVar(22.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy3EBullet1(Enemy3* e3, EBullet1* eb1) {
    if ( ( (eb1->getX() >= e3->getX()-25) && (eb1->getX() <= e3->getX()+25) ) &&
         ( (eb1->getY() >= e3->getY()-25) && (eb1->getY() <= e3->getY()+25) ) ) {
        if (SquareDist(eb1->getX(),e3->getX(),eb1->getY(),e3->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy3EBullet2(Enemy3* e3, EBullet2* eb2) {
    if ( ( (eb2->getX() >= e3->getX()-25) && (eb2->getX() <= e3->getX()+25) ) &&
         ( (eb2->getY() >= e3->getY()-25) && (eb2->getY() <= e3->getY()+25) ) ) {
        if (SquareDist(eb2->getX(),e3->getX(),eb2->getY(),e3->getY()) < SquareVar(14.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::AsteroidEBullet1(Asteroid* a, EBullet1* eb1) {
    if ( ( (eb1->getX() >= a->getX()-20) && (eb1->getX() <= a->getX()+20) ) &&
         ( (eb1->getY() >= a->getY()-20) && (eb1->getY() <= a->getY()+20) ) ) {
        if (SquareDist(eb1->getX(),a->getX(),eb1->getY(),a->getY()) < SquareVar(12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::AsteroidEBullet2(Asteroid* a, EBullet2* eb2) {
    if ( ( (eb2->getX() >= a->getX()-20) && (eb2->getX() <= a->getX()+20) ) &&
         ( (eb2->getY() >= a->getY()-20) && (eb2->getY() <= a->getY()+20) ) ) {
        if (SquareDist(eb2->getX(),a->getX(),eb2->getY(),a->getY()) < SquareVar(12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::AsteroidEBullet3(Asteroid* a, EBullet3* eb3) {
    if ( ( (eb3->getX() >= a->getX()-20) && (eb3->getX() <= a->getX()+20) ) &&
         ( (eb3->getY() >= a->getY()-20) && (eb3->getY() <= a->getY()+20) ) ) {
        if (SquareDist(eb3->getX(),a->getX(),eb3->getY(),a->getY()) < SquareVar(12.5)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy1Enemy2(Enemy1* e1, Enemy2* e2) {
    if ( ( (e2->getX() >= e1->getX()-30) && (e2->getX() <= e1->getX()+30) ) &&
         ( (e2->getY() >= e1->getY()-30) && (e2->getY() <= e1->getY()+30) ) ) {
        if (SquareDist(e2->getX(),e1->getX(),e2->getY(),e1->getY()) < SquareVar(25)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy1Enemy3(Enemy1* e1, Enemy3* e3) {
    if ( ( (e3->getX() >= e1->getX()-30) && (e3->getX() <= e1->getX()+30) ) &&
         ( (e3->getY() >= e1->getY()-30) && (e3->getY() <= e1->getY()+30) ) ) {
        if (SquareDist(e3->getX(),e1->getX(),e3->getY(),e1->getY()) < SquareVar(25)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Collision::Enemy2Enemy3(Enemy2* e2, Enemy3* e3) {
    if ( ( (e3->getX() >= e2->getX()-30) && (e3->getX() <= e2->getX()+30) ) &&
         ( (e3->getY() >= e2->getY()-30) && (e3->getY() <= e2->getY()+30) ) ) {
        if (SquareDist(e3->getX(),e2->getX(),e3->getY(),e2->getY()) < SquareVar(25)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
