#pragma once

#include "SceneObject.h"	// Includes SceneObject file to inherit from

class Asteroid : public SceneObject
{
public:
	Asteroid(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture);
	~Asteroid(void);

	void Draw();
	void Update();

	void SetPosition();
	Vector3 GetPosition();

private:
	GLfloat rotation;
	Vector3 position;

	Texture2D* _texture;
	TexturedMesh* _tmesh;
	Material* _material;
};