#include "HelloGL.h"
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(NULL));

	HelloGL* game = new HelloGL(argc, argv);	// Creates an instance of our game
	
	return 0;									// Assumes a successful exit if our game exits and we make it to this
}