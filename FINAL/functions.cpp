#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "functions.hpp"

using namespace std;

double Limit_Random() {
    int s = rand()%2;
    double rp = rand()%300;
    double rc = 0.0;
    if (s == 0) {
        rc = rp;
    }
    else {
        rc = -rp;
    }
    return rc;
}

double SquareVar(double v) {
    return v*v;
}

double SquareDist(double x1, double x2, double y1, double y2) {
    return SquareVar(x2-x1)+SquareVar(y2-y1);
}

double Magnitude(double x, double y) {
    return sqrt((x*x)+(y*y));
}

double NormalizeX(double x, double y) {
    return x/Magnitude(x,y);
}

double NormalizeY(double x, double y) {
    return y/Magnitude(x,y);
}

double VRandom() {
    int s = rand()%2;
    double rp = (rand()%20) + 10;
    double rc = 0.0;
    if (s == 0) {
        rc = rp;
    }
    else {
        rc = -rp;
    }
    return rc;
}

double TRandom() {
    double rp = (rand()%4) + 1;
    return rp;
}

double RARandom() {
    double rp = (rand()%360);
    return rp;
}

double RVRandom() {
    int s = rand()%2;
    double rp = (rand()%9) + 1;
    double rc = 0.0;
    if (s == 0) {
        rc = rp;
    }
    else {
        rc = -rp;
    }
    return rc;
}
