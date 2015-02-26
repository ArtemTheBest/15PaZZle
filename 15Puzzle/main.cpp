#include <iostream>
#include <time.h>
#include <glut.h>

#include "Board.h"
#include "OpenGl.h"


int main(int argc, char **argv){
	srand((unsigned)time(NULL));

	OpenWindow(argc, argv);
	
	return 0;
}