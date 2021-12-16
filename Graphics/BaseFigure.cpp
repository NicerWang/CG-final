#include "basefigure.h"

float builtinMaterials[3][4] = {
    {0.33,0.22,0.03,1.0},
    {0.78,0.57,0.11,1.0},
    {0.99,0.91,0.81,1.0},
};

float builtinColors[3][4] = {
    {0.33,0.22,0.03},
    {0.78,0.57,0.11},
    {0.99,0.91,0.81},
};


unsigned int loadTexture(BmpLoader* bmpLoader)
{
    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bmpLoader->iWidth, bmpLoader->iHeight, GL_RGB, GL_UNSIGNED_BYTE, bmpLoader->textureData);
    return ID;
}

BuiltInFigure::BuiltInFigure(string type, int size, float colorR, float colorG, float colorB) :
    size(size), type(type) {
    color[0] = colorR;
    color[1] = colorG;
    color[2] = colorB;
}

void BuiltInFigure::show() {
    glColor3fv(this->color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, builtinMaterials[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, builtinMaterials[1]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, builtinMaterials[2]);
    if (this->type == "TEA_PORT")
        glutSolidTeapot(this->size);
    if (this->type == "WIRE_TEA_PORT")
        glutWireTeapot(this->size);
    if (this->type == "CUBE")
        glutSolidCube(this->size);
    if (this->type == "WIRE_CUBE")
        glutWireCube(this->size);
};

void BuiltInFigure::bigger() {
    size *= 1.25;
}

void BuiltInFigure::smaller() {
    size *= 0.8;
}

void OuterFigure::bigger() {
    for (Vertex* vertex : v) {
        vertex->x *= 1.25;
        vertex->y *= 1.25;
        vertex->z *= 1.25;
    }
}

void OuterFigure::smaller() {
    for (Vertex* vertex : v) {
        vertex->x *= 0.8;
        vertex->y *= 0.8;
        vertex->z *= 0.8;
    }
}