#pragma once

void OpenWindow(int argc, char **argv);
void Initialize();
void Draw();
void Reshape(int _width, int _height);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Timer(int);
void DrawStartWindow();
void DrawWinWindow();