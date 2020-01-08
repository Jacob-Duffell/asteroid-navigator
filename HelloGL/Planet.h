#pragma once

#include "SceneObject.h"	// Includes SceneObject file to inherit from

class Planet
{
public:
	Planet(float x, float y, float z, Texture2D* texture);
	~Planet(void);

	void Draw();
	void Update();

private:
	GLfloat rotation;
	Vector3 position;

	Texture2D* _texture;
	Material* _material;
	GLUquadric* _quad;
};