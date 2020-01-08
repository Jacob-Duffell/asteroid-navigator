#include "Player.h"
#include <iostream>
#include <fstream>

using namespace std;

Player::Player(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture)
{
	_material = new Material();
	_tmesh = mesh;
	_texture = texture;

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

	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;

	_material->Shininess = 100.0f;
}


Player::~Player()
{
	delete _material;
	delete _tmesh;
	delete _texture;
}

void Player::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _tmesh->Mesh->Vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _tmesh->TexCoords);
	glNormalPointer(GL_FLOAT, 0, _tmesh->Mesh->Normals);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);	// Translates shape into View Frustrum
	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, _tmesh->Mesh->IndexCount, GL_UNSIGNED_SHORT, _tmesh->Mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Player::Update()
{
	rotation += 1.0f;

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}
}

void Player::MoveLeft()
{
	if (position.x > -7)
	{
		position.x -= 0.1f;
	}
}

void Player::MoveRight()
{
	if (position.x < 7)
	{
		position.x += 0.1f;
	}
}

void Player::MoveUp()
{
	if (position.y < 7)
	{
		position.y += 0.1f;
	}
}

void Player::MoveDown()
{
	if (position.y > -7)
	{
		position.y -= 0.1f;
	}
}

void Player::SetPosition()
{
	position.x = 0.0f;				// Reset position if game is reset
	position.y = -4.0f;
	position.z = -20.0f;
}

Vector3 Player::GetPosition()
{
	return position;
}