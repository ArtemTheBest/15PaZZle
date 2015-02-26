#include <algorithm>
#include <glut.h>
#include <GLAux.h>
#include <math.h>

#include "Board.h"
#include "OpenGl.h"

Board::Board(size_t size){
	this->size = size;
	this->numberOfPassages = 0;
	this->zeroPositionX = this->zeroPositionY = (int)this->size - 1;

	for (size_t i = 0, count = 1; i < this->size; i++){
		this->field.push_back(std::vector<int>());

		for (size_t k = 0; k < this->size; k++, count++)
			this->field[i].push_back(count);
	}

	this->field[this->zeroPositionY][this->zeroPositionX] = 0;
}

void Board::mix(){
	for (int i = 0; i < pow(this->size, (double)5); i++){
		switch (rand() % 4){
		case 0:
			this->go_up();
			break;
		case 1:
			this->go_down();
			break;
		case 2:
			this->go_left();
			break;
		case 3:
			this->go_right();
			break;
		}
	}
}

bool Board::go_up(){
	return go(0, -1);
}

bool Board::go_down(){
	return go(0, 1);
}

bool Board::go_left(){
	return go(-1, 0);
}

bool Board::go_right(){
	return go(1, 0);
}

void Board::increasePassages(){
	this->numberOfPassages++;
}

bool Board::go(int x, int y){
	if (this->zeroPositionX + x >= 0 && this->zeroPositionX + x < (int)this->field.size() &&
		this->zeroPositionY + y >= 0 && this->zeroPositionY + y < (int)this->field.size()){
		std::swap(this->field[this->zeroPositionY][this->zeroPositionX], this->field[this->zeroPositionY + y][this->zeroPositionX + x]);

		increasePassages();

		this->zeroPositionY += y;
		this->zeroPositionX += x;

		return true;
	}

	return false;
}

bool Board::win()const{
	return this->field == (new Board(this->size))->field;
}

std::vector<std::vector<int> > Board::get_field()const{
	return this->field;
}

size_t Board::get_numberOfPassages()const{
	return this->numberOfPassages;
}

void Board::draw_field(int  width, int height)const{
	int SizeOfEdge = min(width, height);
	glLineWidth(3);
	glBegin(GL_LINES);
	for (int i = -(SizeOfEdge / 2); i <= SizeOfEdge / 2; i += SizeOfEdge / this->size){
		glVertex3f(i, -(SizeOfEdge / 2), 0);
		glVertex3f(i, SizeOfEdge / 2, 0);
	}

	for (int i = -(SizeOfEdge / 2); i <= SizeOfEdge / 2; i += SizeOfEdge / this->size){
		glVertex3f(-(SizeOfEdge / 2), i, 0);
		glVertex3f(SizeOfEdge / 2, i, 0);
	}
	glEnd();
	glLineWidth(1);
}

void Board::draw_stone(int  width, int height)const{
	double SizeOfEdge = min(width, height) / this->size;
	double SizeOfHalfField = min(width, height) / 2;
	double factor = SizeOfEdge / 100 * 2.5;



	for (int i = 0; i < (int)this->field.size(); i++){
		for (int k = 0; k < (int)this->field[i].size(); k++){
			if (field[i][k] != 0){
				glBindTexture(GL_TEXTURE_2D, this->textures[this->field[i][k] - 1]);
				glBegin(GL_QUADS);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(SizeOfEdge*k - SizeOfHalfField + factor,
					SizeOfEdge*((this->size) - 1 - i) - SizeOfHalfField + factor, 0);

				glTexCoord2f(1.0, 0.0);
				glVertex3f(SizeOfEdge*k - SizeOfHalfField + SizeOfEdge - factor,
					SizeOfEdge*((this->size) - 1 - i) - SizeOfHalfField + factor, 0);

				glTexCoord2f(1.0, 1.0);
				glVertex3f(SizeOfEdge*k - SizeOfHalfField + SizeOfEdge - factor,
					SizeOfEdge*((this->size) - 1 - i) - SizeOfHalfField + SizeOfEdge - factor, 0);

				glTexCoord2f(0.0, 1.0);
				glVertex3f(SizeOfEdge*k - SizeOfHalfField + factor,
					SizeOfEdge*((this->size) - 1 - i) - SizeOfHalfField + SizeOfEdge - factor, 0);

				glEnd();
			}
		}
	}
}

void Board::load_texture(){
	for (int i = 0; i < 15; i++){
		AUX_RGBImageRec *texture = auxDIBImageLoadA(get_texture_name(i+1).c_str());

		glGenTextures(1, &textures[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	}
}

std::string Board::int_in_string(int n)const{
	return n ? int_in_string(n / 10) + (char)((n % 10) + '0') : std::string();
}

std::string Board::get_texture_name(int numberOfTexture)const{
	return "texture\\TextureFor_" + int_in_string(numberOfTexture) + ".bmp";
}