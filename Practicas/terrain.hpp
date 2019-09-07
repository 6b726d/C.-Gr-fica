#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include <GL/glut.h>

using namespace std;

typedef struct //definicion de un punto del terreno
{
    GLfloat s, t; //oordenadas de texturas
    GLfloat nx, ny, nz; //coordenadas de la normal
    GLfloat x, y, z; //posicion del vertice
} TerrainPoint;

typedef struct //definicion de un triangulo
{
    GLint p1, p2, p3; //indices de los puntos
    GLfloat nx, ny, nz; //coordenadas de la normal
} Triangle;

vector<string> separateValues(string input, char label);//separacion por etiqueta

vector<float> DotProduct(float u[3], float v[3]);

float Magnitude(float x, float y, float z);

vector<float> Normalize(float x, float y, float z);

class Terrain {
public:
    Terrain();
    ~Terrain();
    void generateIndex(); //calcula la lista de indices (SE USA EN LOAD)
    void load(string filename); //carga un archivo de modelo digital de terreno
    void display(); //visualizacion del terreno
    void generateTriangles(); //calcula la lista de triangulos
    void computeNormals(); //calcula las normales de cada vertice
private:
    int nb_pt_x = 101, nb_pt_z = 101; //cantidad de puntos en X y Z
    float dist_x = 50.0, dist_z = 50.0;//distancia entre dos puntos segun X y Z

    TerrainPoint *list_points; //tabla que contiene los puntos del terreno
    GLuint *list_index; //tabla que contiene los indices del terreno
    Triangle *list_triangles; //tabla que contiene los triangulos del terreno
};
