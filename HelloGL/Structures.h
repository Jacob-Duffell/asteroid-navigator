#pragma once

#include <Windows.h>		// Required for OpenGL on Windows
#include <gl/GL.h>			// OpenGL
#include <gl/GLU.h>			// OpenGL Utilities
#include "GL\freeglut.h"	// freeglut library

struct Vector3
{
	float x, y, z;
};

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eye, centre, up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	int VertexCount, NormalCount, IndexCount;
};

struct TexturedMesh
{
	Mesh* Mesh;
	TexCoord* TexCoords;

	int TexCoordCount;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

struct BoundingSphere
{
	Vector3 Position;
	float Radius;
};