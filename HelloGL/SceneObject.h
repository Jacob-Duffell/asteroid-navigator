#pragma once

#include <Windows.h>		// Required for OpenGL on Windows
#include "Structures.h"		// Includes Structures header file
#include "Texture2D.h"		// Includes Texture2D header file

class SceneObject
{
	protected:
		Mesh* _mesh;
	
	public:
		SceneObject(Mesh* mesh);
		virtual ~SceneObject(void);

		virtual void Update() = 0;
		virtual void Draw() = 0; 

		virtual void SetPosition() = 0;
		virtual Vector3 GetPosition() = 0;
};