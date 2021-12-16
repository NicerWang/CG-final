#include "ObjFigure.h"
#include <fstream>
#include <sstream>


ObjFigure::ObjFigure(string filename)
{
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			GLfloat x, y, z;
			istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;
			Vertex* vertex = new Vertex(x,y,z);
			v.push_back(vertex);
		}
		else if (line.substr(0, 2) == "f ")
		{
			string up, vp, wp;
			GLint u, v, w;
			istringstream vtns(line.substr(2));
			vtns >> up; vtns >> vp; vtns >> wp;
			u = stoi(up.substr(0, up.find("/")));
			v = stoi(vp.substr(0, vp.find("/")));
			w = stoi(wp.substr(0, wp.find("/")));
			Face* face = new Face(3);
			face->pointIndexes.push_back(u - 1);
			face->pointIndexes.push_back(v - 1);
			face->pointIndexes.push_back(w - 1);
			f.push_back(face);
		}
	}
	file.close();
}

void ObjFigure::show()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	Vertex *a, *b, *c;

	for (int i = 0; i < f.size(); i++) {
		GLfloat VN[3];

		if (f[i]->factorCnt != 3) 
			cout << "[ERROR]Only support face with 3 vertexes!" << endl;
		else {

			GLint firstVertexIndex = f[i]->pointIndexes[0];
			GLint secondVertexIndex = f[i]->pointIndexes[1];
			GLint thirdVertexIndex = f[i]->pointIndexes[2];

			a = v[firstVertexIndex];
			b = v[secondVertexIndex];
			c = v[thirdVertexIndex];
			

			GLfloat vec1[3], vec2[3], vec3[3];
			vec1[0] = a->x - b->x;
			vec1[1] = a->y - b->y;
			vec1[2] = a->z - b->z;
						
			vec2[0] = a->x - c->x;
			vec2[1] = a->y - c->y;
			vec2[2] = a->z - c->z;

			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glNormal3f(VN[0], VN[1], VN[2]);
			glColor3fv(builtinColors[i % 3]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, builtinColors[i % 3]);
			glMaterialfv(GL_FRONT, GL_AMBIENT, builtinMaterials[0]);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, builtinMaterials[1]);
			glMaterialfv(GL_FRONT, GL_SPECULAR, builtinMaterials[2]);

			glVertex3f(a->x, a->y, a->z);
			glVertex3f(b->x, b->y, b->z);
			glVertex3f(c->x, c->y, c->z);
		}
	}
	glEnd();
}

