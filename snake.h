#ifndef SNAKE_H
#define SNAKE_H
#include <ncurses.h>
#include <vector>
#endif // SNAKE_H
//#include "board.h"

using namespace std;

class Pos {
public:
    int x;
    int y;
};

class Snake {
private:
    Pos Head;
    vector<Pos> posSnake;
    bool Alive;
    int SnakeSpeed;

public:
    Snake(int PosY, int PosX) {
        Head.x = PosX;
        Head.y = PosY;
        SnakeSpeed = 1;
        Alive = true;
    }
    void initSnake();
    int SnakeMove(int &, int &, Pos , Pos, Pos);
    int getSnakeSpeed();
    vector<Pos> getSnakePos();
    void setSnakeSpeed(int Speed);
    Pos getSnakeHead();
    bool isAlive();
    bool isHitMyselft();
    bool isHitBoard(Pos TopLeft, Pos BotRight);
};
