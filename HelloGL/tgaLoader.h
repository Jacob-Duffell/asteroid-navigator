#pragma once

#include "Structures.h"

class tgaLoader
{
public:
	tgaLoader();
	~tgaLoader();

	int Load(const char* path);

	GLuint* GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	GLuint* _ID;
	int _width, _height;	// Height and width values of texture
};

