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
#include <GL/glext.h>

#include "objloader.hpp"
#include "TextureManager.h"

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

ObjLoader::ObjLoader(string model_name, const char* texture_name, GLenum image_format, GLint internal_format) {
    //Texture
    texture = TextureManager::Inst()->LoadTexture(texture_name, image_format, internal_format);
	cout << texture << endl;
	//Model
	load(model_name);
	generateModel();
}

ObjLoader::~ObjLoader(){}

void ObjLoader::load(string file_name) {
    Vertex v;
    VTexture vt;
    VNormal vn;
    Face f;
    vector<string> vline; //valores de la linea
    vector<string> pline;//valores de un punto (Indice(Face))
    string line;
    ifstream myfile (file_name);
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            vline = separateValues(line,' ');
            if (vline[0] == "v") {
                //vertice
                v.x = stof(vline[1]);
                v.y = stof(vline[2]);
                v.z = stof(vline[3]);
                vec_vertex.push_back(v);
                vec_vused.push_back(false);
            }
            else if (vline[0] == "vt") {
                //textura
                vt.s = stof(vline[1]);
                vt.t = stof(vline[2]);
                vec_vtexture.push_back(vt);
            }
            else if (vline[0] == "vn") {
                //normal
                vn.nx = stof(vline[1]);
                vn.ny = stof(vline[2]);
                vn.nz = stof(vline[3]);
                vec_vnormal.push_back(vn);
            }
            else if (vline[0] == "f") {
                //cara
                pline = separateValues(vline[1],'/');
                f.v1 = stoi(pline[0])-1;
                f.vt1 = stoi(pline[1])-1;
                f.vn1 = stoi(pline[2])-1;
                pline = separateValues(vline[2],'/');
                f.v2 = stoi(pline[0])-1;
                f.vt2 = stoi(pline[1])-1;
                f.vn2 = stoi(pline[2])-1;
                pline = separateValues(vline[3],'/');
                f.v3 = stoi(pline[0])-1;
                f.vt3 = stoi(pline[1])-1;
                f.vn3 = stoi(pline[2])-1;
                vec_face.push_back(f);
            }
        }
        myfile.close();
        cout << "the lists were generated correctly" << endl;
    }
    else cout << "unable to open file" << endl;
}

void ObjLoader::generateModel() {
    list_points = new Point[vec_vertex.size()];
    list_index = new GLuint[3*vec_face.size()];
    Point p;
    int ii = 0;
    for(int i=0; i<vec_face.size(); i++) {
        if (vec_vused[vec_face[i].v1] == false) {
            p.s = vec_vtexture[vec_face[i].vt1].s;
            p.t = vec_vtexture[vec_face[i].vt1].t;
            p.nx = vec_vnormal[vec_face[i].vn1].nx;
            p.ny = vec_vnormal[vec_face[i].vn1].ny;
            p.nz = vec_vnormal[vec_face[i].vn1].nz;
            p.x = vec_vertex[vec_face[i].v1].x;
            p.y = vec_vertex[vec_face[i].v1].y;
            p.z = vec_vertex[vec_face[i].v1].z;
            list_points[vec_face[i].v1] = p;
            vec_vused[vec_face[i].v1] = true;
        }
        if (vec_vused[vec_face[i].v2] == false) {
            p.s = vec_vtexture[vec_face[i].vt2].s;
            p.t = vec_vtexture[vec_face[i].vt2].t;
            p.nx = vec_vnormal[vec_face[i].vn2].nx;
            p.ny = vec_vnormal[vec_face[i].vn2].ny;
            p.nz = vec_vnormal[vec_face[i].vn2].nz;
            p.x = vec_vertex[vec_face[i].v2].x;
            p.y = vec_vertex[vec_face[i].v2].y;
            p.z = vec_vertex[vec_face[i].v2].z;
            list_points[vec_face[i].v2] = p;
            vec_vused[vec_face[i].v2] = true;
        }
        if (vec_vused[vec_face[i].v3] == false) {
            p.s = vec_vtexture[vec_face[i].vt3].s;
            p.t = vec_vtexture[vec_face[i].vt3].t;
            p.nx = vec_vnormal[vec_face[i].vn3].nx;
            p.ny = vec_vnormal[vec_face[i].vn3].ny;
            p.nz = vec_vnormal[vec_face[i].vn3].nz;
            p.x = vec_vertex[vec_face[i].v3].x;
            p.y = vec_vertex[vec_face[i].v3].y;
            p.z = vec_vertex[vec_face[i].v3].z;
            list_points[vec_face[i].v3] = p;
            vec_vused[vec_face[i].v3] = true;
        }
        list_index[ii] = vec_face[i].v1;
        list_index[ii+1] = vec_face[i].v2;
        list_index[ii+2] = vec_face[i].v3;
        ii+=3;
    }
}

void ObjLoader::display() {
    int number = 3*vec_face.size();
    glBindTexture(GL_TEXTURE_2D, texture);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(Point), &list_points[0].s);
    glDrawElements(GL_TRIANGLES, number, GL_UNSIGNED_INT, (void*)list_index);
}
