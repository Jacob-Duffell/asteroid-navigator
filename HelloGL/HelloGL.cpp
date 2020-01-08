#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	glutInit(&argc, argv);
	InitGL();
	InitObjects();
	glutMainLoop();
}

HelloGL::~HelloGL()
{
	delete _camera;
	delete _lightPosition;
	delete _lightData;

	delete _cubeMesh;

	delete _asteroidTexture;
	delete _planetTexture;
	delete _backgroundTexture;
	delete _spaceshipTexture;
	delete _logoTexture;

	delete _sceneObjects;

	delete _planet;
	delete _player;
	delete _logo;
}

void HelloGL::InitObjects()
{
	gameOverText <<  "                    Game Over" <<
				  "\n                Your score is " << score <<
				  "\n      Press -SPACE- to try again" <<
				  "\nPress -ESC- to return to title screen";			// Initialise all strings
	vGameOver = { -0.4f, 0.0f, -5.0f };
	cGameOver = { 1.0f, 0.0f, 0.0f };

	pauseText << "PAUSED";
	vPause = { -0.12f, 0.0f, -5.0f };
	cPause = { 0.0f, 1.0f, 0.0f };

	score = 0;
	scoreText << "Score: " << score;
	vScore = { -4.0f, 3.75f, -10.0f };
	cScore = { 0.0f, 1.0f, 0.0f };

	startText << "Press -SPACE- to start" <<
				"\n   Press -ESC- to exit";
	vStart = { -0.3f, -0.5f, -5.0f };
	cStart = { 0.0f, 1.0f, 0.0f };

	_camera = new Camera();					// Initialise camera

	_camera->eye.x = 0.0f;
	_camera->eye.y = 0.0f;
	_camera->eye.z = 0.0f;

	_camera->centre.x = 0.0f;
	_camera->centre.y = 0.0f;
	_camera->centre.z = 0.0f;

	_camera->up.x = 0.0f;
	_camera->up.y = 1.0f;
	_camera->up.z = 0.0f;

	_asteroidTexture = new Texture2D();		// Initialise all textures
	_planetTexture = new Texture2D();
	_backgroundTexture = new Texture2D();
	_spaceshipTexture = new Texture2D();
	_logoTexture = new Texture2D();

	_cubeMesh = MeshLoader::LoadTextured("cube.txt");		// Initialise meshes

	_asteroidTexture->LoadTGA("AsteroidTexture.tga");		// Load all textures
	_planetTexture->LoadTGA("PlanetTexture.tga");
	_backgroundTexture->LoadTGA("BackgroundTexture.tga");
	_spaceshipTexture->LoadTGA("SpaceshipTexture.tga");
	_logoTexture->LoadTGA("Logo.tga");

	// Initialise scene objects and linked list

	SceneObject* _object = new Asteroid(_cubeMesh, (rand() % 100) - 50, (rand() % 100) - 50, -(rand() % 1000), _asteroidTexture);

	_sceneObjects = new LinkedList(_object);

	for (int i = 0; i < NumberOfObjects - 1; i++)
	{
		_sceneObjects->AddToFront(new Asteroid(_cubeMesh, (rand() % 100) - 30, (rand() % 100) - 50, -(rand() % 1000), _asteroidTexture));
	}

	_sceneObjects->AddToFront(new Background(_cubeMesh, 0, 0, -990, _backgroundTexture));

	_player = new Player(_cubeMesh, 0, -4, -20, _spaceshipTexture);		// These scene objects are not part of the linked list
	_planet = new Planet(-80, 0, -175, _planetTexture);
	_logo = new Logo(_cubeMesh, 0, 2, -500, _logoTexture);
}

void HelloGL::InitGL()
{
	GLUTCallbacks::Init(this);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Asteroid Navigator");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	SetLightPosition();
	SetLightData();

	glCullFace(GL_BACK);
	glMatrixMode(GL_PROJECTION);		// Use the Projection Matrix
	glLoadIdentity();					// Reset Matrix
	glViewport(0, 0, 800, 800);			// Set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 1000);	// Set the correct perspective
	glMatrixMode(GL_MODELVIEW);			// Get back to the Modelview
}

void HelloGL::SetLightPosition()
{
	_lightPosition = new Vector4();		// Initialise light position

	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = -20.0;
	_lightPosition->w = 1.0;
}

void HelloGL::SetLightData()
{
	_lightData = new Lighting();		// Initialise light data

	_lightData->Ambient.x = 0.5;
	_lightData->Ambient.y = 0.5;
	_lightData->Ambient.z = 0.5;
	_lightData->Ambient.w = 1.0;

	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;

	_lightData->Specular.x = 0.5;
	_lightData->Specular.y = 0.5;
	_lightData->Specular.z = 0.5;
	_lightData->Specular.w = 1.0;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// This clears the scene so we start fresh each time

	switch (gameState)
	{
		case GameState::START:
		{
			_logo->Draw();

			if (_logo->InPosition())
			{
				DrawString(startText.str().c_str(), &vStart, &cStart);
			}
			break;
		}
		case GameState::PLAY:
		{
			for (int i = 0; i < NumberOfObjects; i++)
			{
				auto node = _sceneObjects->GetNode(i);

				if (node != nullptr)
				{
					node->Draw();
				}
			}

			_planet->Draw();
			_player->Draw();

			DrawString(scoreText.str().c_str(), &vScore, &cScore);
			break;
		}
		case GameState::PAUSE:
		{
			DrawString(pauseText.str().c_str(), &vPause, &cPause);
			break;
		}
		case GameState::GAME_OVER:
		{
			DrawString(gameOverText.str().c_str(), &vGameOver, &cGameOver);
			break;
		}
	}

	glFlush();												// Flushes the scene we just drew to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{	
	glLoadIdentity();	// Reset Matrix
	gluLookAt(_camera->eye.x, _camera->eye.y, _camera->eye.z, 
			  _camera->centre.x, _camera->centre.y, _camera->centre.z, 
			  _camera->up.x, _camera->up.y, _camera->up.z);

	switch (gameState)
	{
		case GameState::START:
		{
			glLoadIdentity();	// Reset Matrix
			_logo->Update();
			break;
		}
		case GameState::PLAY:
		{
			glLoadIdentity();	// Reset Matrix

			for (int i = 0; i < NumberOfObjects; i++)
			{
				auto node = _sceneObjects->GetNode(i);

				if (node != nullptr)
				{
					node->Update();
				}

				if (CalculateCollision(_player->GetPosition(), node->GetPosition()))		// If collision detected, game over
				{
					gameState = GameState::GAME_OVER;
				}
			}

			_planet->Update();
			_player->Update();

			score++;							// Increment score and update string for displaying score
			scoreText.str("");
			scoreText << "Score: " << score;

			gameOverText.str("");
			gameOverText << "                    Game Over" <<
				"\n                Your score is " << score <<
				"\n      Press -SPACE- to try again" <<
				"\nPress -ESC- to return to title screen";			
			break;
		}
		case GameState::PAUSE:
		{
			glLoadIdentity();	// Reset Matrix
			break;
		}
		case GameState::GAME_OVER:
		{
			glLoadIdentity();	// Reset Matrix
			break;
		}
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	switch (gameState)
	{
		case GameState::START:
		{
			if (key == ' ')		// Space key
			{
				gameState = GameState::PLAY;
			}
			if (key == 27)		// Escape key
			{
				exit(0);
			}
			break;
		}
		case GameState::PLAY:
		{
			if (key == 'd')
			{
				_player->MoveRight();
			}

			else if (key == 'a')
			{
				_player->MoveLeft();
			}

			if (key == 'w')
			{
				_player->MoveUp();
			}

			else if (key == 's')
			{
				_player->MoveDown();
			}

			if (key == 'p')
			{
				gameState = GameState::PAUSE;
			}
			break;
		}
		case GameState::PAUSE:
		{
			if (key == 'p')
			{
				gameState = GameState::PLAY;
			}
			break;
		}
		case GameState::GAME_OVER:
		{
			if (key == ' ')		// Space key
			{
				ResetGame();
				gameState = GameState::PLAY;
			}
			if (key == 27)		// Escape key
			{
				ResetGame();
				gameState = GameState::START;
			}
			break;
		}
	}
}

void HelloGL::DrawString(const char* text, const Vector3* position, const Color* color)
{

	glPushMatrix();

	glDisable(GL_TEXTURE);
	glDisable(GL_LIGHTING);

	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);

	glRasterPos2f(0.0f, 0.0f);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);

	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE);

	glPopMatrix();

}

bool HelloGL::CalculateCollision(Vector3 s1, Vector3 s2)
{
	float s1MinX = s1.x - 1.0f;		// Create a collision radius for the Player Object
	float s1MaxX = s1.x + 1.0f;
	float s1MinY = s1.y - 1.0f;
	float s1MaxY = s1.y + 1.0f;
	float s1MinZ = s1.z - 1.0f;
	float s1MaxZ = s1.z + 1.0f;

	float s2MinX = s2.x - 1.0f;		// Create a collision radius for the Ateroid Object(s)
	float s2MaxX = s2.x + 1.0f;
	float s2MinY = s2.y - 1.0f;
	float s2MaxY = s2.y + 1.0f;
	float s2MinZ = s2.z - 1.0f;
	float s2MaxZ = s2.z + 1.0f;

	if (s1MinZ < s2MaxZ)
	{
		if (s1MinX < s2MaxX && s1MaxX > s2MinX)
		{
			if (s1MinY < s2MaxY && s1MaxY > s2MinY)
			{
				return true;
			}
		}
	}

	return false;
}

void HelloGL::ResetGame()
{
	for (int i = 0; i < NumberOfObjects; i++)		// Reset the positions of any objects that move
	{
		auto node = _sceneObjects->GetNode(i);

		if (node != nullptr)
		{
			node->SetPosition();
		}
	}

	_player->SetPosition();
	_logo->SetPosition();

	score = 0;
}