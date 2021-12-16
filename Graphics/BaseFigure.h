#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#include "BaseFactor.h"
#include "BmpLoader.h"

#define NONE 0
#define TEXTURE 1
#define COLOR 2

using namespace std;

extern float builtinMaterials[3][4];
extern float builtinColors[3][4];
unsigned int loadTexture(BmpLoader* bmpLoader);

class Figure {
public:
    string id;
    virtual void show() {};
    virtual void bigger() {};
    virtual void smaller() {};
};

class BuiltInFigure : public Figure {
public:
    string type;
    double size;
    float color[3];
    BuiltInFigure(string type, int size, float colorR, float colorG, float colorB);
    void show();
    void bigger();
    void smaller();
};


class OuterFigure : public Figure {
public:
    vector<Vertex*> v;
    vector<Normal*> vn;
    vector<Face*> f;
    void bigger();
    void smaller();
};


