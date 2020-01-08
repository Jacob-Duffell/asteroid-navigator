#pragma once

#include "Asteroid.h"
#include "Background.h"
#include "GLUTCallbacks.h"
#include "LinkedList.h"
#include "Logo.h"
#include "MeshLoader.h"
#include "Planet.h"
#include "Player.h"
#include "Structures.h"

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

#define REFRESHRATE 16

enum class GameState
{
	START = 0,		// Title screen
	PLAY = 1,		// The game
	PAUSE = 2,		// Pause screen
	GAME_OVER = 3	// Game over screen
};

class HelloGL
{
private:
	static const int NumberOfObjects = 1000;

public:
	Camera* _camera;				// Variables for camera and lighting
	Lighting* _lightData;
	Vector4* _lightPosition;

	TexturedMesh* _cubeMesh;		// Mesh variables

	Texture2D* _asteroidTexture;	// Texture variables
	Texture2D* _backgroundTexture;
	Texture2D* _planetTexture;
	Texture2D* _logoTexture;
	Texture2D* _spaceshipTexture;

	LinkedList* _sceneObjects;		// Linked list variables

	Logo* _logo;					// Various scene object variables
	Planet* _planet;
	Player* _player;

	stringstream gameOverText;		// Variables for the Game Over text
	Vector3 vGameOver;
	Color cGameOver;

	stringstream pauseText;			// Variables for the Pause text
	Vector3 vPause;
	Color cPause;

	int score;						// Variables for the Score text
	stringstream scoreText;
	Vector3 vScore;
	Color cScore;

	stringstream startText;			// Variables for the Start Menu text
	Vector3 vStart;
	Color cStart;

	GameState gameState = GameState::START;		// The game state

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void InitObjects();
	void InitGL();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

	void DrawString(const char* text, const Vector3* position, const Color* color);

	void SetLightPosition();
	void SetLightData();

	bool CalculateCollision(Vector3 s1, Vector3 s2);

	void ResetGame();
};

