#include "FlyingPyramid.h"
#include <iostream>
#include <fstream>

using namespace std;

FlyingPyramid::FlyingPyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{
	_rotation = rand() % 360;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}


FlyingPyramid::~FlyingPyramid()
{

}

void FlyingPyramid::Draw()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);	// Translates shape into View Frustrum
	glRotatef(_rotation, -1.0f, -1.0f, -1.0f);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void FlyingPyramid::Update()
{
	glLoadIdentity();	// Reset Matrix

	_rotation += 1.0f;
	_position.z += 1.0f;

	if (_rotation >= 360.0f)
	{
		_rotation = 0.0f;
	}

	if (_position.z >= 0.0f)
	{
		_position.z = -1000.0f;
	}
}