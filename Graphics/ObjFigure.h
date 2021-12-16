#pragma once
#include <vector>
#include <iostream>
#include <gl/glut.h>
#include "BaseFactor.h"
#include "BaseFigure.h"

using namespace std;

class ObjFigure : public OuterFigure {
public:
	ObjFigure(string filename);
	void show();
};

