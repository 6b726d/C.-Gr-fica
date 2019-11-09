#ifndef objloader_HPP
#define objloader_HPP

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

typedef struct //definicion de un vertice
{
    GLfloat x, y, z; //posicion del vertice
} Vertex;

typedef struct //definicion de una coordenada de textura
{
    GLfloat s, t; //oordenadas de textura
} VTexture;

typedef struct //definicion de una coordenada de normal
{
    GLfloat nx, ny, nz; //coordenadas de la normal
} VNormal;

typedef struct //definicion de una cara
{
    GLuint v1, v2, v3; //indices de vertices
    GLuint vt1, vt2, vt3; //indices de coordenadas de textura
    GLuint vn1, vn2, vn3; //indices de coordenadas de normal
} Face;

typedef struct //definicion de un punto
{
    GLfloat s, t; //oordenadas de texturas
    GLfloat nx, ny, nz; //coordenadas de la normal
    GLfloat x, y, z; //posicion del vertice
} Point;

vector<string> separateValues(string input, char label);//separacion por etiqueta

class ObjLoader {
public:
    ObjLoader(string model_name, const char* texture_name, GLenum image_format, GLint internal_format);
    ~ObjLoader();
    void load(string file_name); //carga un archivo de modelo digital de terreno
    void generateModel(); //genera los puntos e indices del modelo
    void display(); //visualizacion del modelo
private:
    GLint texture;
    vector<bool> vec_vused; //vector de vertices usados
    vector<Vertex> vec_vertex; //vector de vertices
    vector<VTexture> vec_vtexture; //vector de coordenadas de textura
    vector<VNormal> vec_vnormal; //vector de coordenadas de normale
    vector<Face> vec_face; //vector de caras
    Point *list_points; //tabla que contiene los puntos del terreno
    GLuint *list_index; //tabla que contiene los indices del terreno
};

#endif

