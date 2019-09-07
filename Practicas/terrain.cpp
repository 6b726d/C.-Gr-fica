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

#include "terrain.hpp"

using namespace std;

vector<string> separateValues(string input, char label) {
	stringstream inputstream(input);
	string word;
	vector<string> words;
	while (getline(inputstream, word, label)) {
		words.push_back(word);
    }
    return words;
}

vector<float> DotProduct(float u[3], float v[3]) {
    vector<float> dp;
    float c = 0.0;
    c = (u[1]*v[2]) - (v[1]*u[2]);
    dp.push_back(c);
    c = -((u[0]*v[2]) - (v[0]*u[2]));
    dp.push_back(c);
    c = (u[0]*v[1]) - (v[0]*u[1]);
    dp.push_back(c);
    return dp;
}

float Magnitude(float x, float y, float z) {
    return sqrt((x*x)+(y*y)+(z*z));
}

vector<float> Normalize(float x, float y, float z) {
    vector<float> nv;
    float m = Magnitude(x,y,z);
    nv.push_back(x/m);
    nv.push_back(y/m);
    nv.push_back(z/m);
    return nv;
}

Terrain::Terrain(){}

Terrain::~Terrain(){}

void Terrain::generateIndex() {
    list_index = new GLuint[(((nb_pt_x-1)*(nb_pt_z-1)*2)*3)];
    int sl = (nb_pt_x*(nb_pt_z-1))-1;//cantidad de elementos
    int nl = (nb_pt_x*nb_pt_z)-1;
    int sx = nb_pt_x;
    int di = 0;
    for (int i=0; i<sl; i++) {
        if ( (((i+1)%sx)!=0) || (i==0) ) {
            list_index[di] = i+1;
            list_index[di+1] = i;
            list_index[di+2] = i+sx;
            di+=3;
        }
    }
    int ui = di;
    for (int i=nl; i>sx; i--) {
        if ((i%sx)!=0) {
            list_index[ui] = i-1;
            list_index[ui+1] = i;
            list_index[ui+2] = i-sx;
            ui+=3;
        }
    }
}

void Terrain::load(string filename) {
    list_points = new TerrainPoint[nb_pt_x*nb_pt_z];
    vector<string> vline; //valores de la linea
    int ti = 0;
    int li = 0;
    TerrainPoint tp;
    string line;
    ifstream myfile (filename);
    if(myfile.is_open()) {
        getline(myfile,line);
        while(getline(myfile,line)) {
            vline = separateValues(line,' ');
            tp.z = ti*dist_z;
            tp.t = ti*(1.0/(nb_pt_z-1.0));
            for (int tj=0; tj<nb_pt_x; tj++) {
                tp.x = tj*dist_x;
                tp.y = stof(vline[tj]);//
                tp.s = tj*(1.0/(nb_pt_x-1.0));
                list_points[li] = tp;
                li+=1;
            }
            ti+=1;
        }
        myfile.close();
        generateIndex();
        cout << "the lists were generated correctly";
    }
    else cout << "unable to open file";
}

void Terrain::display() {
    int number = (((nb_pt_x-1)*(nb_pt_z-1)*2)*3);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(TerrainPoint), &list_points[0].s);
    glDrawElements(GL_TRIANGLES, number, GL_UNSIGNED_INT, (void*)list_index);
}

void Terrain::generateTriangles() {
    int si = (((nb_pt_x-1)*(nb_pt_z-1)*2)*3); //cantidad de indices
    int st = ((nb_pt_x-1)*(nb_pt_z-1)*2); //cantidad de triangulos
    list_triangles = new Triangle[st];
    Triangle t;
    float u[3]; //vector u
    float v[3]; //vector v
    vector<float> p; //dot product
    vector<float> n; //normal
    for (int i=0; i<si; i+=3) {
        t.p1 = list_index[i];
        t.p2 = list_index[i+1];
        t.p3 = list_index[i+2];
        u[0] = list_points[t.p3].x - list_points[t.p2].x;
        u[1] = list_points[t.p3].y - list_points[t.p2].y;
        u[2] = list_points[t.p3].z - list_points[t.p2].z;
        v[0] = list_points[t.p1].x - list_points[t.p2].x;
        v[1] = list_points[t.p1].y - list_points[t.p2].y;
        v[2] = list_points[t.p1].z - list_points[t.p2].z;
        p = DotProduct(u,v);
        n = Normalize(p[0],p[1],p[2]);
        t.nx = n[0];
        t.ny = n[1];
        t.nz = n[2];
        list_triangles[i/3] = t;
    }
}

void Terrain::computeNormals() {
    int ct = 0; //contador de triangulos
    float sumx = 0; //suma de nx
    float sumy = 0; //suma de ny
    float sumz = 0; //suma de nz
    int sp = nb_pt_x*nb_pt_z; //cantidad de puntos
    int st = ((nb_pt_x-1)*(nb_pt_z-1)*2); //cantidad de triangulos
    for (int pi=0; pi<sp; pi++) {
        for (int ti=0; ti<st; ti++) {
            if ( (pi == list_triangles[ti].p1) ||
                 (pi == list_triangles[ti].p2) ||
                 (pi == list_triangles[ti].p3) ) {
                    ct+=1;
                    sumx+=list_triangles[ti].nx;
                    sumy+=list_triangles[ti].ny;
                    sumz+=list_triangles[ti].nz;
            }
        }
        list_points[pi].nx = sumx/ct;
        list_points[pi].ny = sumy/ct;
        list_points[pi].nz = sumz/ct;
        ct = 0;
        sumx = 0;
        sumy = 0;
        sumz = 0;
    }
}
