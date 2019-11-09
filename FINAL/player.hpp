#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>

class ObjLoader;

using namespace std;

class Player {
    double x,y,z;
    int lifes;
    int score;
    int bombs;
    int tshot;
    double rtime = 0.5;//time_to_reload
    bool MUp = false;
    bool MDown = false;
    bool MLeft = false;
    bool MRight = false;
    double v = 100.0;
    double lmov = 0.0;
    ObjLoader* obj;
public:
    Player(double _x, double _y, double _z, int _lifes, int _score, int _bombs, int _tshot, ObjLoader* _obj);
    double getX();
    double getY();
    double getZ();
    double getSX();
    double getSY();
    double getRTime();
    int getLifes();
    int getScore();
    int getBombs();
    int getTShot();
    void setLifes(int nLifes);
    void setScore(int nScore);
    void setBombs(int nBombs);
    void setTShot(int nTShot);
    void Reset();
    void Draw();
    void MoveUp(bool b);
    void MoveDown(bool b);
    void MoveLeft(bool b);
    void MoveRight(bool b);
    void Move(double dt);
};
