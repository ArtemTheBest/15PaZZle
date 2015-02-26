#include <glut.h>
#include <GLAux.h>
#include <Windows.h>

#include "OpenGl.h"
#include "Board.h"

unsigned int spcTextures[2];
int width = 800;
int height = 800;

bool game = false;

Board brd(4);

void LoadSpcTextures(){
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("texture\\TextureForStartWindow.bmp"),
		*texture2 = auxDIBImageLoadA("texture\\TextureForWinWindow.bmp");
	glGenTextures(2, &spcTextures[0]);

	glBindTexture(GL_TEXTURE_2D, spcTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, spcTextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
}

void DrawStartWindow(){
	int quadsPoint = min(width, height) / 4;

	glBindTexture(GL_TEXTURE_2D, spcTextures[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-quadsPoint, -quadsPoint, 0);
	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(quadsPoint, -quadsPoint, 0);	

	glTexCoord2f(1.0, 1.0);
	glVertex3f(quadsPoint, quadsPoint, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-quadsPoint, quadsPoint, 0);
	

	glEnd();
}

void DrawWinWindow(){
	int quadsPoint = min(width, height) / 4;

	glBindTexture(GL_TEXTURE_2D, spcTextures[1]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-quadsPoint, -quadsPoint, 0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(quadsPoint, -quadsPoint, 0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(quadsPoint, quadsPoint, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-quadsPoint, quadsPoint, 0);


	glEnd();
}

void OpenWindow(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("15 Pazzle");

	Initialize();
	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(30, Timer, 0);
	glutMainLoop();
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	if (game){
		if (!brd.win()){
			glColor3f(0, 0, 0);
			brd.draw_field(width, height);

			glColor3f(1, 1, 1);
			brd.draw_stone(width, height);
		}
		else{
			DrawWinWindow();
		}
	}
	else{
		DrawStartWindow();
	}

	glutSwapBuffers();
}

void Initialize(){
	LoadSpcTextures();
	brd.load_texture();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.819, 0.819, 0.929, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Reshape(int _width, int _height){
	width = _width;
	height = _height;

	glViewport(0, 0, _width, _height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'r':
		brd.mix();
		break;
	case 13:
		game = game ? false : true;

		brd.mix();
		break;
	}
}

void SpecialKeyboard(int key, int x, int y){
	switch (key){
	case GLUT_KEY_RIGHT:
		brd.go_right();
		break;
	case GLUT_KEY_LEFT:
		brd.go_left();
		break;
	case GLUT_KEY_UP:
		brd.go_up();
		break;
	case GLUT_KEY_DOWN:
		brd.go_down();
		break;
	}
}

void Timer(int = 0){
	brd.win();
	Draw();
	glutTimerFunc(30, Timer, 0);
}
