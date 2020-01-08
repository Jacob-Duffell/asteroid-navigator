#pragma once

#include "Structures.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	bool LoadRAW(char* path, int width, int height);
	int LoadTGA(const char* path);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	GLuint _ID;				// Texture ID
	int _width, _height;	// Height and width values of texture
};

