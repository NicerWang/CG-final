#pragma once
#include "BaseFigure.h"

class MeshFigure : public OuterFigure {
public:
    int vertexCnt = 0;
    int normalCnt = 0;
    int faceCnt = 0;
    int textureType;
    void show();
    static MeshFigure* readFigure(string meshPath, string texturePath = ".") {
        MeshFigure* figure = new MeshFigure();
        ifstream in;
        in.open(meshPath);
        in >> figure->vertexCnt >> figure->normalCnt >> figure->faceCnt;
        double x, y, z;
        for (int i = 0; i < figure->vertexCnt; i++) {
            in >> x >> y >> z;
            figure->v.push_back(new Vertex(x, y, z));
        }
        for (int i = 0; i < figure->normalCnt; i++) {
            in >> x >> y >> z;
            figure->vn.push_back(new Normal(x, y, z));
        }
        for (int i = 0; i < figure->faceCnt; i++) {
            int cnt;
            in >> cnt;
            Face* face = new Face(cnt);
            for (int j = 0; j < face->factorCnt; j++) {
                in >> x;
                face->pointIndexes.push_back(x);
            }
            for (int j = 0; j < face->factorCnt; j++) {
                in >> x;
                face->normalIndexes.push_back(x);
            }
            figure->f.push_back(face);
        }
        in.close();
        if (texturePath == ".") {
            figure->textureType = NONE;
            return figure;
        }
        in.open(texturePath);
        char type;
        in >> type;
        if (type == 'T') {
            figure->textureType = TEXTURE;
            string fileName;
            float factorX;
            float factorY;
            for (int i = 0; i < figure->f.size(); i++) {
                in >> fileName;
                figure->f[i]->bmpLoader = new BmpLoader();
                figure->f[i]->bmpLoader->load(fileName.c_str());
                figure->f[i]->textureID = loadTexture(figure->f[i]->bmpLoader);
                for (int j = 0; j < figure->f[i]->factorCnt; j++) {
                    in >> factorX >> factorY;
                    figure->f[i]->textureFactor.push_back(pair<float, float>(factorX, factorY));
                }
            }
        }
        else if (type == 'C') {
            figure->textureType = COLOR;
            for (int i = 0; i < figure->v.size(); i++) {
                in >> figure->v[i]->R >> figure->v[i]->G >> figure->v[i]->B;
            }
        }
        in.close();
        return figure;
    }
};



