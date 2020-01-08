#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;		// Load the Colour information from file
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;		// Load the Texture Coordinate information from file
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		mesh.Indices = new GLushort[mesh.IndexCount];

		for (int i = 0; i < mesh.IndexCount; i++)
		{
			inFile >> mesh.Indices[i];				// Load the Index information from file
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);		// Load the object values
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}

	TexturedMesh* MeshLoader::LoadTextured(char* path)
	{
		TexturedMesh* mesh = new TexturedMesh();
		mesh->Mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh->Mesh);		// Load the object values
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh->Mesh);
		LoadIndices(inFile, *mesh->Mesh);

		inFile.close();

		return mesh;
	}
}