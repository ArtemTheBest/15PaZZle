#pragma once

#include <vector>

class Board{
public:
	Board(size_t  size);

	void mix();
	bool win()const;

	bool go_up();
	bool go_down();
	bool go_left();
	bool go_right();

	void load_texture();

	void draw_field(int  width, int height)const;
	void draw_stone(int  width, int height)const;

	std::vector<std::vector<int> > get_field()const;
	size_t get_numberOfPassages()const;
private:
	std::vector<std::vector<int> > field;
	size_t size;

	int zeroPositionX;
	int zeroPositionY;

	size_t numberOfPassages;

	unsigned int textures[15];

	std::string int_in_string(int n)const;
	std::string get_texture_name(int numberOfTexture)const;
	void increasePassages();
	bool go(int x, int y);
};