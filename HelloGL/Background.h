#pragma once

#include "SceneObject.h"	// Includes SceneObject file to inherit from

class Background : public SceneObject
{
public:
	Background(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture);
	~Background(void);

	void Draw();
	void Update();

	void SetPosition();
	Vector3 GetPosition();

private:
	Vector3 position;

	Texture2D* _texture;
	TexturedMesh* _tmesh;
};