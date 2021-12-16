#include "MeshFigure.h"

void MeshFigure::show() {
    glColor3f(1, 1, 1);
    if (textureType == NONE) {
        for (int i = 0; i < faceCnt; i++) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glNormal3f(vn[i]->x, vn[i]->y, vn[i]->z);
            for (int j = 0; j < f[i]->factorCnt; j++) {
                Vertex* factor = this->v[f[i]->pointIndexes[j]];
                glVertex3d(factor->x, factor->y, factor->z);
            }
            glEnd();
        }
    }
    else if (textureType == TEXTURE) {
        for (int i = 0; i < faceCnt; i++) {
            glBindTexture(GL_TEXTURE_2D, f[i]->textureID);
            glEnable(GL_TEXTURE_2D);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glMaterialfv(GL_FRONT, GL_AMBIENT, builtinMaterials[0]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, builtinMaterials[1]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, builtinMaterials[2]);
            glBegin(GL_POLYGON);
            glNormal3f(vn[i]->x, vn[i]->y, vn[i]->z);
            for (int j = 0; j < f[i]->factorCnt; j++) {
                Vertex* factor = this->v[f[i]->pointIndexes[j]];
                glTexCoord2f(f[i]->textureFactor[j].first, f[i]->textureFactor[j].second);
                glVertex3d(factor->x, factor->y, factor->z);
            }
            glEnd();
            glDisable(GL_TEXTURE_2D);
        }
    }
    else if (textureType == COLOR) {
        for (int i = 0; i < faceCnt; i++) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glNormal3f(vn[i]->x, vn[i]->y, vn[i]->z);
            for (int j = 0; j < f[i]->factorCnt; j++) {
                Vertex* factor = this->v[f[i]->pointIndexes[j]];
                glColor3f(factor->R / 255, factor->G / 255, factor->B / 255);
                glVertex3d(factor->x, factor->y, factor->z);
            }
            glEnd();
        }
    }

};