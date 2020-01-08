#pragma once

#include "SceneObject.h"	// Includes SceneObject file to inherit from
#include "GLUTCallbacks.h"

class Player
{
public:
	Player(TexturedMesh* mesh, float x, float y, float z, Texture2D* texture);
	~Player(void);

	void Draw();
	void Update();

	void SetPosition();
	Vector3 GetPosition();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	GLfloat rotation;
	Vector3 position;

	Texture2D* _texture;
	TexturedMesh* _tmesh;
	Material* _material;
};