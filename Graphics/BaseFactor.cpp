#include "basefactor.h"

Normal::Normal(double x, double y, double z) :x(x), y(y), z(z) {}

Vertex::Vertex(double x, double y, double z) :x(x), y(y), z(z) {}

Face::Face(int n) :factorCnt(n) {}