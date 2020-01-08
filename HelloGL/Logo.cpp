#include "Logo.h"
#include <iostream>
#include <fstream>

using namespace std;

Logo::Logo(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture)
{
	_tmesh = mesh;
	_texture = texture;

	position.x = x;
	position.y = y;
	position.z = z;
}


Logo::~Logo()
{
	delete _tmesh;
	delete _texture;
}

void Logo::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _tmesh->Mesh->Vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _tmesh->TexCoords);
	glNormalPointer(GL_FLOAT, 0, _tmesh->Mesh->Normals);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);	// Translates shape into View Frustrum
	glRotatef(90, 0.0f, 0.0f, -1.0f);
	glScalef(2, 4, 0);
	glDrawElements(GL_TRIANGLES, _tmesh->Mesh->IndexCount, GL_UNSIGNED_SHORT, _tmesh->Mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Logo::Update()
{
	if (position.z <= -25.0f)
	{
		position.z += 3.0f;
	}
}

bool Logo::InPosition()
{
	if (position.z >= -26.0f)		// Returns true if the logo has stopped moving
	{
		return true;
	}

	else return false;
}

void Logo::SetPosition()
{
	position.x = 0.0f;				// Reset position if game is reset
	position.y = 2.0f;
	position.z = -500.0f;
}