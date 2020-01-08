#include "Asteroid.h"
#include <iostream>
#include <fstream>

using namespace std;

Asteroid::Asteroid(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture) : SceneObject(mesh->Mesh)
{
	_material = new Material();
	_tmesh = mesh;
	_texture = texture;

	rotation = rand() % 360;		// Randomise speed of rotation

	position.x = x;					// Positions of object iare also randomised
	position.y = y;
	position.z = z;

	 _material->Ambient.x = 0.2;	// Asteroids are darker than other objects
	 _material->Ambient.y = 0.2;
	 _material->Ambient.z = 0.2;
	 _material->Ambient.w = 1.0;

	 _material->Diffuse.x = 0.8;
	 _material->Diffuse.y = 0.8;
	 _material->Diffuse.z = 0.8;
	 _material->Diffuse.w = 1.0;

	 _material->Specular.x = 0.2;
	 _material->Specular.y = 0.2;
	 _material->Specular.z = 0.2;
	 _material->Specular.w = 1.0;

	 _material->Shininess = 100.0f;
}


Asteroid::~Asteroid()
{
	delete _material;
	delete _texture;
	delete _tmesh;
}

void Asteroid::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _tmesh->TexCoords);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);	// Translates shape into View Frustrum
		glRotatef(rotation, 1.0f, 1.0f, -1.0f);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Asteroid::Update()
{
	rotation += 1.0f;
	position.z += 1.0f;

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}

	if (position.z >= 0.0f)
	{
		position.z = -1000.0f;		// Move object to far end of scene
	}
}

void Asteroid::SetPosition()
{
	position.x = (rand() % 100) - 30;		// Re-randomise position of object
	position.y = (rand() % 100) - 50;
	position.z = -(rand() % 1000);
}

Vector3 Asteroid::GetPosition()
{
	return position;
}