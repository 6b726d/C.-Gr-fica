//Clase del Texto del Juego

#include <string>

using namespace std;

void drawStrokeText(char* str, double scl, double x, double y, double z);

void DrawTextScore(int score);

void DrawTextLifes(int lifes);

void DrawTextBombs(int bombs);

void DrawTextTShot(int tshot);

void SaveMaxScore(string file_name, int max_score);

string LoadMaxScore(string file_name);

void DrawTextMenu();

void DrawTextWin(int score);

void DrawTextLose(int score);
