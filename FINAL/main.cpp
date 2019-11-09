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
#include <GL/glext.h>

#include <irrKlang.h>

#include "player.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"
#include "enemy1.hpp"
#include "enemy2.hpp"
#include "enemy3.hpp"
#include "ebullet1.hpp"
#include "ebullet2.hpp"
#include "ebullet3.hpp"
#include "item.hpp"
#include "particle.hpp"
#include "functions.hpp"
#include "dtext.hpp"
#include "collision.hpp"

#include "TextureManager.h"
#include "objloader.hpp"

using namespace std;

using namespace irrklang;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

//Illimination
GLfloat gameDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat gameSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gameAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat gameShininess[] = {9.0f};

GLfloat light0Position[] = {0.0,375.0,325.0,0.0};
GLfloat light0Diffuse [] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat light0Specular [] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light0Ambient [] = {0.3f, 0.3f, 0.3f, 1.0f};

//Sounds
ISoundEngine* engine = createIrrKlangDevice();
ISoundSource* music = engine->addSoundSourceFromFile("C:/UCSP/Computacion Grafica/FINAL/Sounds/MF-W-90.XM");
ISoundSource* itemSound = engine->addSoundSourceFromFile("C:/UCSP/Computacion Grafica/FINAL/Sounds/item.wav");
ISoundSource* bulletSound = engine->addSoundSourceFromFile("C:/UCSP/Computacion Grafica/FINAL/Sounds/laser.wav");
ISoundSource* explosionSound = engine->addSoundSourceFromFile("C:/UCSP/Computacion Grafica/FINAL/Sounds/explosion.wav");
ISoundSource* collisionSound = engine->addSoundSourceFromFile("C:/UCSP/Computacion Grafica/FINAL/Sounds/collision.wav");
ISoundSource* ebulletSound = engine->addSoundSourceAlias(bulletSound,"ebulletS");
ISoundSource* cexplosionSound = engine->addSoundSourceAlias(explosionSound,"cexplosionS");


//Textures (Item)
GLint t_lifes;
GLint t_score;
GLint t_bombs;
GLint t_tshot;
//Background
GLint t_background;
//Textures (Particle)
GLint t_particle1;
GLint t_particle2;
GLint t_particle3;
GLint t_particle4;
GLint t_particle5;
//Models
ObjLoader* obj_player;
ObjLoader* obj_asteroid;
ObjLoader* obj_enemy1;
ObjLoader* obj_enemy2;
ObjLoader* obj_enemy3;

Collision* c;

//Globals BEGIN
bool game = false;
char rgame = 'n';//n(null),w(win),l(lose)
int MaxScore = 0.0;
double seconds = 121.0;
int ebomb = 0.0;//enemys destroyed
//Player BEGIN
Player* p;
list<Bullet*> bullets;
double BTime = 0.0;
list<Item*> items;
double ITime = 0.0;
double IRTime = 12.0;//time of aparition
//Player END
//Asteroids BEGIN
list<Asteroid*> asteroids;
double ATime = 0.0;
double ARTime = 7.0;//time of aparition
//Asteroids END
//Enemys BEGIN
double ERTime = 0.5;
//E1
list<Enemy1*> enemys1;
double E1Time = 0.0;
double E1RTime = 10.0;//time of aparition
list<EBullet1*> ebullets1;
double EBTime1 = 0.0;
//E2
list<Enemy2*> enemys2;
double E2Time = 0.0;
double E2RTime = 13.0;//time of aparition
list<EBullet2*> ebullets2;
double EBTime2 = 0.0;
//E3
list<Enemy3*> enemys3;
double E3Time = 0.0;
double E3RTime = 16.0;//time of aparition
list<EBullet3*> ebullets3;
double EBTime3 = 0.0;
//Enemys END
//Particles
list<Particle*> particles;
//Globals END

//global time
int time=0;
int timebase=0;

#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

//MovePlayer BEGIN
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveUp(true);
		break;

	case GLUT_KEY_DOWN:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveDown(true);
		break;

	case GLUT_KEY_LEFT:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveLeft(true);
		break;

	case GLUT_KEY_RIGHT:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveRight(true);
		break;
	}
}

GLvoid callback_special_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveUp(false);
		break;

	case GLUT_KEY_DOWN:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveDown(false);
		break;

	case GLUT_KEY_LEFT:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveLeft(false);
		break;

	case GLUT_KEY_RIGHT:
		glutPostRedisplay();			// et on demande le réaffichage.
		p->MoveRight(false);
		break;
	}
}
//MovePlayer END

int main(int argc, char **argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(650, 750);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Shoot’em up");


	initGL();
	init_scene();


	//Begin Sounds
	//Music
	music->setDefaultVolume(0.1f);
	engine->play2D(music,true);
	//Source
	itemSound->setDefaultVolume(0.5f);
	bulletSound->setDefaultVolume(0.1f);
	explosionSound->setDefaultVolume(1.5f);
	collisionSound->setDefaultVolume(0.5f);
	ebulletSound->setDefaultVolume(0.01f);
	cexplosionSound->setDefaultVolume(0.5f);

	//Textures
	t_lifes = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Red.jpg", GL_BGR_EXT, GL_RGB);
	t_score = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Fuchsia.jpg", GL_BGR_EXT, GL_RGB);
	t_bombs = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Cyan.jpg", GL_BGR_EXT, GL_RGB);
	t_tshot = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Yellow.jpg", GL_BGR_EXT, GL_RGB);
	t_background = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Background.jpg", GL_BGR_EXT, GL_RGB);
	t_particle1 = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Explosion1.png", GL_BGRA_EXT, GL_RGBA);
	t_particle2 = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Explosion2.png", GL_BGRA_EXT, GL_RGBA);
	t_particle3 = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Explosion3.png", GL_BGRA_EXT, GL_RGBA);
	t_particle4 = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Explosion4.png", GL_BGRA_EXT, GL_RGBA);
	t_particle5 = TextureManager::Inst()->LoadTexture("C:/UCSP/Computacion Grafica/FINAL/Models/Explosion5.png", GL_BGRA_EXT, GL_RGBA);


	//Begin Objects
	obj_player = new ObjLoader("C:/UCSP/Computacion Grafica/FINAL/Models/Player.obj",
                               "C:/UCSP/Computacion Grafica/FINAL/Models/Texture_Player.tga",GL_RGB,GL_RGB);
    obj_enemy1 = new ObjLoader("C:/UCSP/Computacion Grafica/FINAL/Models/Enemy1.obj",
                               "C:/UCSP/Computacion Grafica/FINAL/Models/Texture_E1.jpg",GL_RGB,GL_RGB);
    obj_enemy2 = new ObjLoader("C:/UCSP/Computacion Grafica/FINAL/Models/Enemy2.obj",
                               "C:/UCSP/Computacion Grafica/FINAL/Models/Texture_E2.tga",GL_RGBA,GL_RGBA);
    obj_enemy3 = new ObjLoader("C:/UCSP/Computacion Grafica/FINAL/Models/Enemy3.obj",
                               "C:/UCSP/Computacion Grafica/FINAL/Models/Texture_E3.jpg",GL_RGB,GL_RGB);
    obj_asteroid = new ObjLoader("C:/UCSP/Computacion Grafica/FINAL/Models/Asteroid.obj",
                               "C:/UCSP/Computacion Grafica/FINAL/Models/Texture_A.jpg",GL_RGB,GL_RGB);

	p = new Player(0.0,-70.0,0.0,3,0,0,0,obj_player);//
	c = new Collision();


	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	glutSpecialFunc(&callback_special);//

	glutSpecialUpFunc(&callback_special_up);//

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	//End Sound
	engine->drop();

	return 1;
}



GLvoid initGL()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gameDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gameSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gameAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, gameShininess);

    glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
    glEnable(GL_CULL_FACE); //no trata las caras escondidas
    glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
    glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Activa la corrección de perspectiva

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

	glClearColor(RED, GREEN, BLUE, ALPHA);

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_TEXTURE);
}

//Functions BEGIN
void DrawBackGround() {
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D,t_background);
    glBegin(GL_QUADS);
    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0.0,0.0);
    glVertex3d(-330,-380,-10.0);
    glTexCoord2d(1.0,0.0);
    glVertex3d(330,-380,-10.0);
    glTexCoord2d(1.0,1.0);
    glVertex3d(330,380,-10.0);
    glTexCoord2d(0.0,1.0);
    glVertex3d(-330,380,-10.0);
    glEnd();
    glDisable(GL_LIGHTING);
}

void DrawPlayerArea() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3d(255,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3d(-320,70,0);
    glVertex3d(320,70,0);
    glVertex3d(320,-370,0);
    glVertex3d(-320,-370,0);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void GeneratePlayer(double dt) {
    glEnable(GL_LIGHTING);
    p->Draw();
    glDisable(GL_LIGHTING);
	p->Move(dt);
}

void GenerateBullets(double dt) {
    list<Bullet*>::iterator itB;
	for (itB = bullets.begin(); itB != bullets.end(); itB++) {
	    if ((*itB)->getY() < 340) {
	        glEnable(GL_LIGHTING);
	        glDisable(GL_TEXTURE_2D);
            (*itB)->Draw();
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            (*itB)->Move(dt);
	    }
	    else {
	        delete(*itB);
	        itB = bullets.erase(itB);
	    }
    }
}

void AddItems() {
    if (ITime > IRTime) {
        items.push_back(new Item(Limit_Random(),340.0,0.0,rand()%4));
        ITime = 0;
    }
}

void GenerateItems(double dt) {
    list<Item*>::iterator itI;
	for (itI = items.begin(); itI != items.end(); itI++) {
	    if ((*itI)->getY() > -360) {
	        glEnable(GL_LIGHTING);
            (*itI)->Draw();
            glDisable(GL_LIGHTING);
            (*itI)->Move(dt);
	    }
	    else {
	        delete(*itI);
	        itI = items.erase(itI);
	    }
    }
}

void AddAsteroids() {
    if (ATime > ARTime) {
        asteroids.push_back(new Asteroid(Limit_Random(),340.0,0.0,obj_asteroid));
        ATime = 0;
    }
}

void GenerateAsteroids(double dt) {
    list<Asteroid*>::iterator itA;
	for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
	    if ((*itA)->getY() > -360) {
	        glEnable(GL_LIGHTING);
            (*itA)->Draw();
            glDisable(GL_LIGHTING);
            (*itA)->Move(dt);
	    }
	    else {
	        delete(*itA);
	        itA = asteroids.erase(itA);
	    }
    }
}

void AddEnemys1() {
    if (E1Time > E1RTime) {
        enemys1.push_back(new Enemy1(Limit_Random(),340.0,0.0,obj_enemy1));
        E1Time = 0;
    }
}

void GenerateEnemys1(double dt) {
    list<Enemy1*>::iterator itE1;
	for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
	    if ((*itE1)->getY() > -360) {
	        glEnable(GL_LIGHTING);
            (*itE1)->Draw();
            glDisable(GL_LIGHTING);
            (*itE1)->Move(dt);
	    }
	    else {
	        delete(*itE1);
	        itE1 = enemys1.erase(itE1);
	    }
    }
}

void AddEnemys2() {
    if (E2Time > E2RTime) {
        enemys2.push_back(new Enemy2(Limit_Random(),340.0,0.0,obj_enemy2));
        E2Time = 0;
    }
}

void GenerateEnemys2(double dt) {
    list<Enemy2*>::iterator itE2;
	for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
	    if ((*itE2)->getY() > -360) {
	        glEnable(GL_LIGHTING);
            (*itE2)->Draw();
            glDisable(GL_LIGHTING);
            (*itE2)->Move(dt);
	    }
	    else {
	        delete(*itE2);
	        itE2 = enemys2.erase(itE2);
	    }
    }
}

void AddEnemys3() {
    if (E3Time > E3RTime) {
        enemys3.push_back(new Enemy3(Limit_Random(),340.0,0.0,obj_enemy3));
        E3Time = 0;
    }
}

void GenerateEnemys3(double dt) {
    list<Enemy3*>::iterator itE3;
	for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
	    if ((*itE3)->getY() > -400) {
	        glEnable(GL_LIGHTING);
            (*itE3)->Draw();
            glDisable(GL_LIGHTING);
            (*itE3)->Move(dt,p->getX(),p->getY(),p->getZ());
	    }
	    else {
	        delete(*itE3);
	        itE3 = enemys3.erase(itE3);
	    }
    }
}

void AddEBullets1() {
    if (EBTime1 > ERTime) {
        list<Enemy1*>::iterator itE1;
        for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
            engine->play2D(ebulletSound);
            ebullets1.push_back(new EBullet1((*itE1)->getSX(),(*itE1)->getSY(),0.0));
        }
        EBTime1 = 0;
    }
}

void AddEBullets2() {
    if (EBTime2 > ERTime) {
        list<Enemy2*>::iterator itE2;
        for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
            engine->play2D(ebulletSound);
            ebullets2.push_back(new EBullet2((*itE2)->getSX(),(*itE2)->getSY(),0.0,p->getX(),p->getY(),p->getZ()));
        }
        EBTime2 = 0;
    }
}

void AddEBullets3() {
    if (EBTime3 > ERTime) {
        list<Enemy3*>::iterator itE3;
        for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
            if ((*itE3)->getShoot()) {
                engine->play2D(ebulletSound);
                ebullets3.push_back(new EBullet3((*itE3)->getSX(),(*itE3)->getSY(),0.0,p->getX(),p->getY(),p->getZ()));
            }
        }
        EBTime3 = 0;
    }
}

void GenerateEBullets1(double dt) {
    list<EBullet1*>::iterator itEB1;
	for (itEB1 = ebullets1.begin(); itEB1 != ebullets1.end(); itEB1++) {
	    if ((*itEB1)->getY() > -360) {
	        glEnable(GL_LIGHTING);
	        glDisable(GL_TEXTURE_2D);
            (*itEB1)->Draw();
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            (*itEB1)->Move(dt);
	    }
	    else {
	        delete(*itEB1);
	        itEB1 = ebullets1.erase(itEB1);
	    }
    }
}

void GenerateEBullets2(double dt) {
    list<EBullet2*>::iterator itEB2;
	for (itEB2 = ebullets2.begin(); itEB2 != ebullets2.end(); itEB2++) {
	    if ((*itEB2)->getY() > -360) {
	        glEnable(GL_LIGHTING);
	        glDisable(GL_TEXTURE_2D);
            (*itEB2)->Draw();
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            (*itEB2)->Move(dt);
	    }
	    else {
	        delete(*itEB2);
	        itEB2 = ebullets2.erase(itEB2);
	    }
    }
}

void GenerateEBullets3(double dt) {
    list<EBullet3*>::iterator itEB3;
	for (itEB3 = ebullets3.begin(); itEB3 != ebullets3.end(); itEB3++) {
	    if ((*itEB3)->getY() > -360) {
	        glEnable(GL_LIGHTING);
	        glDisable(GL_TEXTURE_2D);
            (*itEB3)->Draw();
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            (*itEB3)->Move(dt);
	    }
	    else {
	        delete(*itEB3);
	        itEB3 = ebullets3.erase(itEB3);
	    }
    }
}

void CollisionsPlayerAsteroid() {
    list<Asteroid*>::iterator itA;
	for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
        if (c->PlayerAsteroid(p,*itA)) {
            engine->play2D(cexplosionSound);
            p->setLifes(0);//Game Over
            //Eliminar el Asteroide
            delete(*itA);
            itA = asteroids.erase(itA);
            //Destroy Enemys
            enemys1.clear();
            enemys2.clear();
            enemys3.clear();
        }
	}
}

void CollisionsPlayerEnemy1() {
    list<Enemy1*>::iterator itE1;
	for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        if (c->PlayerEnemy1(p,*itE1)) {
            engine->play2D(cexplosionSound);
            p->setLifes(0);//Game Over
            //Destroy Enemys
            enemys1.clear();
            enemys2.clear();
            enemys3.clear();
        }
    }
}

void CollisionsPlayerEnemy2() {
    list<Enemy2*>::iterator itE2;
	for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        if (c->PlayerEnemy2(p,*itE2)) {
            engine->play2D(cexplosionSound);
            p->setLifes(0);//Game Over
            //Destroy Enemys
            enemys1.clear();
            enemys2.clear();
            enemys3.clear();
        }
    }
}

void CollisionsPlayerEnemy3() {
    list<Enemy3*>::iterator itE3;
	for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        if (c->PlayerEnemy3(p,*itE3)) {
            engine->play2D(cexplosionSound);
            p->setLifes(0);//Game Over
            //Destroy Enemys
            enemys1.clear();
            enemys2.clear();
            enemys3.clear();
        }
    }
}

void CollisionsBulletAsteroid() {
    list<Asteroid*>::iterator itA;
    list<Bullet*>::iterator itB;
    for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
        for (itB = bullets.begin(); itB != bullets.end(); itB++) {
            if (c->BulletAsteroid(*itB,*itA)) {
                engine->play2D(cexplosionSound);
                p->setScore(p->getScore()+1);
                //Eliminar la Bala
                delete(*itB);
                itB = bullets.erase(itB);
                //Particles
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Asteroide
                (*itA)->setY(-400);
            }
        }
    }
}

void CollisionsBulletEnemy1() {
    list<Enemy1*>::iterator itE1;
    list<Bullet*>::iterator itB;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itB = bullets.begin(); itB != bullets.end(); itB++) {
            if (c->BulletEnemy1(*itB,*itE1)) {
                engine->play2D(cexplosionSound);
                p->setScore(p->getScore()+1);
                //Eliminar la Bala
                delete(*itB);
                itB = bullets.erase(itB);
                //Particles
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar Enemy
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsBulletEnemy2() {
    list<Enemy2*>::iterator itE2;
    list<Bullet*>::iterator itB;
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        for (itB = bullets.begin(); itB != bullets.end(); itB++) {
            if (c->BulletEnemy2(*itB,*itE2)) {
                engine->play2D(cexplosionSound);
                p->setScore(p->getScore()+1);
                //Eliminar la Bala
                delete(*itB);
                itB = bullets.erase(itB);
                //Particles
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar Enemy
                (*itE2)->setY(-400);
            }
        }
    }
}

void CollisionsBulletEnemy3() {
    list<Enemy3*>::iterator itE3;
    list<Bullet*>::iterator itB;
    for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        for (itB = bullets.begin(); itB != bullets.end(); itB++) {
            if (c->BulletEnemy3(*itB,*itE3)) {
                engine->play2D(cexplosionSound);
                p->setScore(p->getScore()+1);
                //Eliminar la Bala
                delete(*itB);
                itB = bullets.erase(itB);
                //Particles
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar Enemy
                (*itE3)->setY(-400);
            }
        }
    }
}

void CollisionsEBullet1Player() {
    list<EBullet1*>::iterator itEB1;
    for (itEB1 = ebullets1.begin(); itEB1 != ebullets1.end(); itEB1++) {
        if (c->PlayerEBullet1(p,*itEB1)) {
            engine->play2D(collisionSound);
            p->setLifes(p->getLifes()-1);
            //Eliminar la Bala
            delete(*itEB1);
            itEB1 = ebullets1.erase(itEB1);
        }
    }
}

void CollisionsEBullet2Player() {
    list<EBullet2*>::iterator itEB2;
    for (itEB2 = ebullets2.begin(); itEB2 != ebullets2.end(); itEB2++) {
        if (c->PlayerEBullet2(p,*itEB2)) {
            engine->play2D(collisionSound);
            p->setLifes(p->getLifes()-1);
            //Eliminar la Bala
            delete(*itEB2);
            itEB2 = ebullets2.erase(itEB2);
        }
    }
}

void CollisionsEBullet3Player() {
    list<EBullet3*>::iterator itEB3;
    for (itEB3 = ebullets3.begin(); itEB3 != ebullets3.end(); itEB3++) {
        if (c->PlayerEBullet3(p,*itEB3)) {
            engine->play2D(collisionSound);
            p->setLifes(p->getLifes()-1);
            //Eliminar la Bala
            delete(*itEB3);
            itEB3 = ebullets3.erase(itEB3);
        }
    }
}

void CollisionsItemPlayer() {
    list<Item*>::iterator itI;
    for (itI = items.begin(); itI != items.end(); itI++) {
        if (c->PlayerItem(p,*itI)) {
            engine->play2D(itemSound);
            if ((*itI)->getType()==0) {
                p->setLifes(p->getLifes()+1);
            }
            else if ((*itI)->getType()==1) {
                p->setScore(p->getScore()+1);
            }
            else if ((*itI)->getType()==2) {
                p->setBombs(p->getBombs()+1);
            }
            else if ((*itI)->getType()==3) {
                if (p->getTShot()<2) {
                    p->setTShot(p->getTShot()+1);
                }
            }
            //Eliminar el Item
            delete(*itI);
            itI = items.erase(itI);
        }
    }
}

//EXTRA Collision BEGIN
void CollisionsEnemy1Asteroid() {
    list<Enemy1*>::iterator itE1;
    list<Asteroid*>::iterator itA;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
            if (c->Enemy1Asteroid(*itE1,*itA)) {
                engine->play2D(explosionSound);
                //Particles Asteroid
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Asteroide
                delete(*itA);
                itA = asteroids.erase(itA);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy1EBullet2() {
    list<Enemy1*>::iterator itE1;
    list<EBullet2*>::iterator itEB2;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itEB2 = ebullets2.begin(); itEB2 != ebullets2.end(); itEB2++) {
            if (c->Enemy1EBullet2(*itE1,*itEB2)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB2);
                itEB2 = ebullets2.erase(itEB2);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy1EBullet3() {
    list<Enemy1*>::iterator itE1;
    list<EBullet3*>::iterator itEB3;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itEB3 = ebullets3.begin(); itEB3 != ebullets3.end(); itEB3++) {
            if (c->Enemy1EBullet3(*itE1,*itEB3)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB3);
                itEB3 = ebullets3.erase(itEB3);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy2Asteroid() {
    list<Enemy2*>::iterator itE2;
    list<Asteroid*>::iterator itA;
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
            if (c->Enemy2Asteroid(*itE2,*itA)) {
                engine->play2D(explosionSound);
                //Particles Asteroid
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Asteroide
                delete(*itA);
                itA = asteroids.erase(itA);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE2)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy2EBullet1() {
    list<Enemy2*>::iterator itE2;
    list<EBullet1*>::iterator itEB1;
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        for (itEB1 = ebullets1.begin(); itEB1 != ebullets1.end(); itEB1++) {
            if (c->Enemy2EBullet1(*itE2,*itEB1)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB1);
                itEB1 = ebullets1.erase(itEB1);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE2)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy2EBullet3() {
    list<Enemy2*>::iterator itE2;
    list<EBullet3*>::iterator itEB3;
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        for (itEB3 = ebullets3.begin(); itEB3 != ebullets3.end(); itEB3++) {
            if (c->Enemy2EBullet3(*itE2,*itEB3)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB3);
                itEB3 = ebullets3.erase(itEB3);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE2)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy3Asteroid() {
    list<Enemy3*>::iterator itE3;
    list<Asteroid*>::iterator itA;
    for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
            if (c->Enemy3Asteroid(*itE3,*itA)) {
                engine->play2D(explosionSound);
                //Particles Asteroid
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Asteroide
                delete(*itA);
                itA = asteroids.erase(itA);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE3)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy3EBullet1() {
    list<Enemy3*>::iterator itE3;
    list<EBullet1*>::iterator itEB1;
    for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        for (itEB1 = ebullets1.begin(); itEB1 != ebullets1.end(); itEB1++) {
            if (c->Enemy3EBullet1(*itE3,*itEB1)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB1);
                itEB1 = ebullets1.erase(itEB1);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE3)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy3EBullet2() {
    list<Enemy3*>::iterator itE3;
    list<EBullet2*>::iterator itEB2;
    for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        for (itEB2 = ebullets2.begin(); itEB2 != ebullets2.end(); itEB2++) {
            if (c->Enemy3EBullet2(*itE3,*itEB2)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB2);
                itEB2 = ebullets2.erase(itEB2);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar el Enemigo
                (*itE3)->setY(-400);
            }
        }
    }
}

void CollisionsAsteroidEBullet1() {
    list<Asteroid*>::iterator itA;
    list<EBullet1*>::iterator itEB1;
    for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
        for (itEB1 = ebullets1.begin(); itEB1 != ebullets1.end(); itEB1++) {
            if (c->AsteroidEBullet1(*itA,*itEB1)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB1);
                itEB1 = ebullets1.erase(itEB1);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Enemigo
                (*itA)->setY(-400);
            }
        }
    }
}

void CollisionsAsteroidEBullet2() {
    list<Asteroid*>::iterator itA;
    list<EBullet2*>::iterator itEB2;
    for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
        for (itEB2 = ebullets2.begin(); itEB2 != ebullets2.end(); itEB2++) {
            if (c->AsteroidEBullet2(*itA,*itEB2)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB2);
                itEB2 = ebullets2.erase(itEB2);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Enemigo
                (*itA)->setY(-400);
            }
        }
    }
}

void CollisionsAsteroidEBullet3() {
    list<Asteroid*>::iterator itA;
    list<EBullet3*>::iterator itEB3;
    for (itA = asteroids.begin(); itA != asteroids.end(); itA++) {
        for (itEB3 = ebullets3.begin(); itEB3 != ebullets3.end(); itEB3++) {
            if (c->AsteroidEBullet3(*itA,*itEB3)) {
                engine->play2D(cexplosionSound);
                //Eliminar la Bala
                delete(*itEB3);
                itEB3 = ebullets3.erase(itEB3);
                //Particles Enemy
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itA)->getX(),(*itA)->getY(),(*itA)->getZ()));
                }
                //Eliminar el Enemigo
                (*itA)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy1Enemy2() {
    list<Enemy1*>::iterator itE1;
    list<Enemy2*>::iterator itE2;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
            if (c->Enemy1Enemy2(*itE1,*itE2)) {
                engine->play2D(explosionSound);
                //Particles Enemy2
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar el Enemigo2
                delete(*itE2);
                itE2 = enemys2.erase(itE2);
                //Particles Enemy1
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar el Enemigo1
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy1Enemy3() {
    list<Enemy1*>::iterator itE1;
    list<Enemy3*>::iterator itE3;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
            if (c->Enemy1Enemy3(*itE1,*itE3)) {
                engine->play2D(explosionSound);
                //Particles Enemy3
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar el Enemigo3
                delete(*itE3);
                itE3 = enemys3.erase(itE3);
                //Particles Enemy1
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
                }
                //Eliminar el Enemigo1
                (*itE1)->setY(-400);
            }
        }
    }
}

void CollisionsEnemy2Enemy3() {
    list<Enemy2*>::iterator itE2;
    list<Enemy3*>::iterator itE3;
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
            if (c->Enemy2Enemy3(*itE2,*itE3)) {
                engine->play2D(explosionSound);
                //Particles Enemy3
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
                }
                //Eliminar el Enemigo3
                delete(*itE3);
                itE3 = enemys3.erase(itE3);
                //Particles Enemy2
                for (int i=0; i<20; i++) {
                    particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
                }
                //Eliminar el Enemigo1
                (*itE2)->setY(-400);
            }
        }
    }
}
//EXTRA Collision END

void GenerateParticles(double dt) {
    list<Particle*>::iterator itP;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
	for (itP = particles.begin(); itP != particles.end(); itP++) {
	    if ((*itP)->getT() > 0.0) {
	        glEnable(GL_LIGHTING);
            (*itP)->Draw();
            glDisable(GL_LIGHTING);
            (*itP)->TMove(dt);
	    }
	    else {
	        delete(*itP);
	        itP = particles.erase(itP);
	    }
    }
    glDisable(GL_BLEND);
}

void ActiveBomb() {
    list<Enemy1*>::iterator itE1;
    list<Enemy2*>::iterator itE2;
    list<Enemy3*>::iterator itE3;
    for (itE1 = enemys1.begin(); itE1 != enemys1.end(); itE1++) {
        //Particles
        for (int i=0; i<20; i++) {
            particles.push_back(new Particle((*itE1)->getX(),(*itE1)->getY(),(*itE1)->getZ()));
        }
    }
    for (itE2 = enemys2.begin(); itE2 != enemys2.end(); itE2++) {
        //Particles
        for (int i=0; i<20; i++) {
            particles.push_back(new Particle((*itE2)->getX(),(*itE2)->getY(),(*itE2)->getZ()));
        }
    }
    for (itE3 = enemys3.begin(); itE3 != enemys3.end(); itE3++) {
        //Particles
        for (int i=0; i<20; i++) {
            particles.push_back(new Particle((*itE3)->getX(),(*itE3)->getY(),(*itE3)->getZ()));
        }
    }
}
//Functions END

void DrawTextTime(double dt) {
    char textTime[20];
    strcpy(textTime,"Time: ");
    int isecs = floor(seconds);
    const char* valTime = to_string(isecs).c_str();
    strcat(textTime,valTime);
    strcat(textTime,"s");
    drawStrokeText(textTime,0.1,-300,350,0);
    seconds = seconds - dt;
    if (isecs < 0) {
        game = false;
        rgame = 'w';
    }
}

//Special
void GameOver() {
    if (p->getLifes() <= 0) {
        SaveMaxScore("C:/UCSP/Computacion Grafica/FINAL/Final/score.txt",p->getScore());
        game = false;
        rgame = 'l';
	}
}

void GenerateGame(double dt) {
    BTime+=dt;
    ATime+=dt;
    E1Time+=dt;
    E2Time+=dt;
    E3Time+=dt;
	EBTime1+=dt;
	EBTime2+=dt;
	EBTime3+=dt;
	ITime+=dt;
	GeneratePlayer(dt);
	GenerateBullets(dt);
	AddAsteroids();
	GenerateAsteroids(dt);
	AddEnemys1();
	GenerateEnemys1(dt);
	AddEnemys2();
	GenerateEnemys2(dt);
	AddEnemys3();
	GenerateEnemys3(dt);
	AddEBullets1();
	GenerateEBullets1(dt);
	AddEBullets2();
	GenerateEBullets2(dt);
	AddEBullets3();
	GenerateEBullets3(dt);
	AddItems();
	GenerateItems(dt);
	CollisionsPlayerAsteroid();
	CollisionsPlayerEnemy1();
	CollisionsPlayerEnemy2();
	CollisionsPlayerEnemy3();
	CollisionsBulletAsteroid();
	CollisionsBulletEnemy1();
	CollisionsBulletEnemy2();
	CollisionsBulletEnemy3();
	CollisionsEBullet1Player();
	CollisionsEBullet2Player();
	CollisionsEBullet3Player();
	CollisionsItemPlayer();
	CollisionsEnemy1Asteroid();
	CollisionsEnemy1EBullet2();
	CollisionsEnemy1EBullet3();
	CollisionsEnemy2Asteroid();
	CollisionsEnemy2EBullet1();
	CollisionsEnemy2EBullet3();
	CollisionsEnemy3Asteroid();
	CollisionsEnemy3EBullet1();
	CollisionsEnemy3EBullet2();
	CollisionsAsteroidEBullet1();
	CollisionsAsteroidEBullet2();
	CollisionsAsteroidEBullet3();
	CollisionsEnemy1Enemy2();
	CollisionsEnemy1Enemy3();
	CollisionsEnemy2Enemy3();
	GenerateParticles(dt);
}

void DrawTextGame(double dt) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3d(1.0,1.0,1.0);
    DrawTextTime(dt);
	DrawTextScore(p->getScore());
	DrawTextLifes(p->getLifes());
	DrawTextBombs(p->getBombs());
	DrawTextTShot(p->getTShot());
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void RestartGame() {
    seconds = 121.0;
    BTime = 0;
    E1Time = 0;
    E2Time = 0;
    E3Time = 0;
	EBTime1 = 0;
	EBTime2 = 0;
	EBTime3 = 0;
	ITime = 0;
	bullets.clear();
	ebullets1.clear();
	ebullets2.clear();
	ebullets3.clear();
	items.clear();
	asteroids.clear();
	enemys1.clear();
	enemys2.clear();
	enemys3.clear();
	particles.clear();
	p->Reset();
}

GLvoid window_display()
{
    //Time dt
    time = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time-timebase)/1000.0;// delta time
    timebase = time;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);


	/*dibujar aqui*/
	if (game == false) {
        if (rgame == 'w') {
            glLoadIdentity();
            glViewport(0,0,650,750);
            glOrtho(-325.0f, 325.0f, -375.0f, 375.0f, -325.0f, 325.0f);
            DrawTextWin(p->getScore());
        }
        else if (rgame == 'l') {
            glLoadIdentity();
            glViewport(0,0,650,750);
            glOrtho(-325.0f, 325.0f, -375.0f, 375.0f, -325.0f, 325.0f);
            DrawTextLose(p->getScore());
        }
        else {
            glLoadIdentity();
            glViewport(0,0,650,750);
            glOrtho(-325.0f, 325.0f, -375.0f, 375.0f, -325.0f, 325.0f);
            DrawTextMenu();
        }
	}
	else {
        glLoadIdentity();
        glViewport(0,0,650,750);
        glOrtho(-325.0f, 325.0f, -375.0f, 375.0f, -325.0f, 325.0f);
        DrawPlayerArea();
	    glLoadIdentity();
	    glViewport(0,0,650,750);
        gluPerspective(45.0,0.867,0.1,975.0);//
        glTranslated(0.0,0.0,-925.0);
        DrawBackGround();
        GenerateGame(dt);
        glLoadIdentity();
        glViewport(0,700,650,50);
        glOrtho(-325.0f, 325.0f, 325.0f, 375.0f, -325.0f, 325.0f);
        DrawTextGame(dt);
        GameOver();
	}


	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-325.0f, 325.0f, -375.0f, 375.0f, -325.0f, 325.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;
    case 'z':
        if (BTime > p->getRTime()) {
            engine->play2D(bulletSound);
            if (p->getTShot() == 0) {
                bullets.push_back(new Bullet(p->getSX(),p->getSY(),0.0,p->getTShot()));
            }
            else if (p->getTShot() == 1) {
                bullets.push_back(new Bullet(p->getSX()+15,p->getSY(),0.0,p->getTShot()));
                bullets.push_back(new Bullet(p->getSX()-15,p->getSY(),0.0,p->getTShot()));
            }
            else {
                bullets.push_back(new Bullet(p->getSX(),p->getSY(),0.0,p->getTShot()));
                bullets.push_back(new Bullet(p->getSX()+15,p->getSY(),0.0,p->getTShot()));
                bullets.push_back(new Bullet(p->getSX()-15,p->getSY(),0.0,p->getTShot()));
            }
            BTime = 0;
        }
        break;
    case 'x':
        if (p->getBombs() > 0) {
            ebomb = enemys1.size() + enemys2.size() + enemys3.size();
            engine->play2D(explosionSound);
            ActiveBomb();
            p->setScore(p->getScore()+ebomb);
            enemys1.clear();
            enemys2.clear();
            enemys3.clear();
            p->setBombs(p->getBombs()-1);
        }
        break;
    case 'c':
        if (game == false) {
            game = true;
            RestartGame();
        }
        else {
            game = false;
            rgame = 'n';
        }
        break;
    case 'v':
        if ( (game == false) && ( (rgame == 'w') || (rgame == 'l') ) ) {
            rgame = 'n';
        }
        //else {}
        break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}
