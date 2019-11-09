//Clase que detecta todas las colisiones

class Player;
class Bullet;
class Asteroid;
class Enemy1;
class EBullet1;
class Enemy2;
class EBullet2;
class Enemy3;
class EBullet3;
class Item;

class Collision {
public:
    Collision();
    ~Collision();
    //Game
    bool PlayerItem(Player* p, Item* i);
    bool PlayerAsteroid(Player* p, Asteroid* a);
    bool PlayerEnemy1(Player* p, Enemy1* e1);
    bool PlayerEnemy2(Player* p, Enemy2* e2);
    bool PlayerEnemy3(Player* p, Enemy3* e3);
    bool PlayerEBullet1(Player* p, EBullet1* eb1);
    bool PlayerEBullet2(Player* p, EBullet2* eb2);
    bool PlayerEBullet3(Player* p, EBullet3* eb3);
    bool BulletAsteroid(Bullet* b, Asteroid* a);
    bool BulletEnemy1(Bullet* b, Enemy1* e1);
    bool BulletEnemy2(Bullet* b, Enemy2* e2);
    bool BulletEnemy3(Bullet* b, Enemy3* e3);
    //Extra
    bool Enemy1Asteroid(Enemy1* e1, Asteroid* a);
    bool Enemy1EBullet2(Enemy1* e1, EBullet2* eb2);
    bool Enemy1EBullet3(Enemy1* e1, EBullet3* eb3);
    bool Enemy2Asteroid(Enemy2* e2, Asteroid* a);
    bool Enemy2EBullet1(Enemy2* e2, EBullet1* eb1);
    bool Enemy2EBullet3(Enemy2* e2, EBullet3* eb3);
    bool Enemy3Asteroid(Enemy3* e3, Asteroid* a);
    bool Enemy3EBullet1(Enemy3* e3, EBullet1* eb1);
    bool Enemy3EBullet2(Enemy3* e3, EBullet2* eb2);
    bool AsteroidEBullet1(Asteroid* a, EBullet1* eb1);
    bool AsteroidEBullet2(Asteroid* a, EBullet2* eb2);
    bool AsteroidEBullet3(Asteroid* a, EBullet3* eb3);
    bool Enemy1Enemy2(Enemy1* e1, Enemy2* e2);
    bool Enemy1Enemy3(Enemy1* e1, Enemy3* e3);
    bool Enemy2Enemy3(Enemy2* e2, Enemy3* e3);
};
