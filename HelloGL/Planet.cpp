#include "Planet.h"
#include <iostream>
#include <fstream>

using namespace std;

Planet::Planet(float x, float y, float z, Texture2D* texture)
{
	_material = new Material();
	_texture = texture;
	_quad = gluNewQuadric();

	rotation = rand() % 360;

	position.x = x;
	position.y = y;
	position.z = z;

	_material->Ambient.x = 1.0;
	_material->Ambient.y = 1.0;
	_material->Ambient.z = 1.0;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 0.8;
	_material->Diffuse.y = 0.8;
	_material->Diffuse.z = 0.8;
	_material->Diffuse.w = 1.0;

	_material->Specular.x = 0.7;
	_material->Specular.y = 0.7;
	_material->Specular.z = 0.7;
	_material->Specular.w = 1.7;

	_material->Shininess = 100.0f;
}


Planet::~Planet()
{
	delete _material;
	delete _texture;
	delete _quad;
}

void Planet::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);	// Translates shape into View Frustrum
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation, 0, 0, 1.0);						// Rotates only along Z-axis
	glScalef(50, 50, 50);

	gluQuadricTexture(_quad, 1);
	gluSphere(_quad, 1, 20, 20);						// Draw sphere and wrap texture around it

	glPopMatrix();
}

void Planet::Update()
{
	rotation += 0.05f;

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}
}