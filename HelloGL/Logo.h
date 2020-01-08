#pragma once

#include "SceneObject.h"	// Includes SceneObject file to inherit from

class Logo
{
public:
	Logo(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture);
	~Logo(void);

	void Draw();
	void Update();
	bool InPosition();

	void SetPosition();

private:
	Vector3 position;

	Texture2D* _texture;
	TexturedMesh* _tmesh;
};