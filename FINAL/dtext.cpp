#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <list>

#include <GL/glut.h>

#include "dtext.hpp"

using namespace std;

void drawStrokeText(char* str, double scl, double x, double y, double z) {
    char *c;
    glPushMatrix();
    glTranslated(x, y, z);
    glScaled(scl, scl, z);
    for (c = str; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

//TextPlayer Begin
void DrawTextScore(int score) {
    char textScore[20];
    strcpy(textScore,"Score: ");
    const char* valScore = to_string(score).c_str();
    strcat(textScore,valScore);
    drawStrokeText(textScore,0.1,-100,350,0);
}

void DrawTextLifes(int lifes) {
    char textLifes[20];
    strcpy(textLifes,"Lifes: ");
    const char* valLifes = to_string(lifes).c_str();
    strcat(textLifes,valLifes);
    drawStrokeText(textLifes,0.1,30,350,0);
}

void DrawTextBombs(int bombs) {
    char textBombs[20];
    strcpy(textBombs,"Bombs: ");
    const char* valBombs = to_string(bombs).c_str();
    strcat(textBombs,valBombs);
    drawStrokeText(textBombs,0.1,150,350,0);
}

void DrawTextTShot(int tshot) {
    char textTShot[20];
    strcpy(textTShot,"TShot: ");
    const char* valTShot = to_string(tshot).c_str();
    strcat(textTShot,valTShot);
    drawStrokeText(textTShot,0.1,240,350,0);
}
//TextPlayer End

void SaveMaxScore(string file_name, int max_score) {
    //p1
    int pre_score = 0;
    string line = "";
    ifstream myfile1 (file_name);
    if(myfile1.is_open()) {
        while(getline(myfile1,line)) {
            pre_score = stoi(line);
        }
        myfile1.close();
    }
    else cout << "unable to open file s1" << endl;
    //p2
    if (pre_score > max_score) {
        max_score = pre_score;
    }
    string t_max_score = "";
    ofstream myfile2 (file_name);
    if(myfile2.is_open()) {
        t_max_score = to_string(max_score);
        myfile2<<t_max_score;
        myfile2.close();
    }
    else cout << "unable to open file s2" << endl;
}

string LoadMaxScore(string file_name) {
    string line = "";
    ifstream myfile (file_name);
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            //
        }
        myfile.close();
        return line;
    }
    else return line;
}

void DrawTextMenu() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3d(255.0,255.0,255.0);
    drawStrokeText("SHOOT’EM UP",0.5,-210,240,0);
    char textMaxScore[20];
    strcpy(textMaxScore,"Max Score: ");
    const char* valMaxScore = LoadMaxScore("C:/UCSP/Computacion Grafica/FINAL/Final/score.txt").c_str();//
    strcat(textMaxScore,valMaxScore);//
    drawStrokeText(textMaxScore,0.2,-200,120,0);
    drawStrokeText("Controls:",0.2,-200,60,0);
    drawStrokeText("Move: Arrows",0.2,-180,0,0);
    drawStrokeText("Shoot: Z",0.2,-180,-60,0);
    drawStrokeText("Bomb: X",0.2,-180,-120,0);
    drawStrokeText("Start: Press C",0.3,-200,-240,0);
    drawStrokeText("Exit: Press Esc",0.3,-200,-300,0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void DrawTextWin(int score) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3d(255.0,255.0,255.0);
    drawStrokeText("SHOOT’EM UP",0.5,-210,240,0);
    char textCurrentScore[20];
    strcpy(textCurrentScore,"Score: ");
    const char* valCurrentScore = to_string(score).c_str();
    strcat(textCurrentScore,valCurrentScore);
    drawStrokeText(textCurrentScore,0.2,-200,120,0);
    drawStrokeText("You Win!!!",0.2,-200,60,0);
    drawStrokeText("Menu: Press V",0.3,-200,-240,0);
    drawStrokeText("Start: Press C",0.3,-200,-300,0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void DrawTextLose(int score) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3d(255.0,255.0,255.0);
    drawStrokeText("SHOOT’EM UP",0.5,-210,240,0);
    char textCurrentScore[20];
    strcpy(textCurrentScore,"Score: ");
    const char* valCurrentScore = to_string(score).c_str();
    strcat(textCurrentScore,valCurrentScore);
    drawStrokeText(textCurrentScore,0.2,-200,120,0);
    drawStrokeText("You Lose",0.2,-200,60,0);
    drawStrokeText("Menu: Press V",0.3,-200,-240,0);
    drawStrokeText("Start: Press C",0.3,-200,-300,0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
//Text END
