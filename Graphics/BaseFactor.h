#pragma once
#include <vector>
#include "BmpLoader.h"

class Normal {
public:
    double x;
    double y;
    double z;
    Normal(double x, double y, double z);
};

class Vertex {
public:
    double x;
    double y;
    double z;
    float R;
    float G;
    float B;
    Vertex(double x, double y, double z);
};


class Face {
public:
    int factorCnt = 0;
    std::vector<int> pointIndexes;
    std::vector<int> normalIndexes;
    BmpLoader* bmpLoader;
    unsigned int textureID;
    std::vector<std::pair<float, float>> textureFactor;
    Face(int n);
};

