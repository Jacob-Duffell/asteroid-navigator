#include "Background.h"
#include <iostream>
#include <fstream>

using namespace std;

Background::Background(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture) : SceneObject(mesh->Mesh)
{
	_tmesh = mesh;
	_texture = texture;

	position.x = x;
	position.y = y;
	position.z = z;
}


Background::~Background()
{
	delete _tmesh;
	delete _texture;
}

void Background::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _tmesh->TexCoords);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);	// Translates shape into View Frustrum
	glScalef(420, 420, 0);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Background::Update()
{
	// Background remains stationary
}

void Background::SetPosition()
{
	// Background never moves, so it is unnecessary to reset position
}

Vector3 Background::GetPosition()
{
	return position;
}