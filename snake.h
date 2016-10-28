#ifndef SNAKE_H
#define SNAKE_H
#include <ncurses.h>
#include <vector>
#endif // SNAKE_H
//#include "board.h"

using namespace std;

//store coordinate
class Pos {
public:
    int x;
    int y;
};

class Snake {
private:
    //each coordinate of snake body will be stored in a vector
    Pos Head;
    vector<Pos> posSnake;
    bool Alive;  //check the snake alive or not
    int SnakeSpeed;  //speed of snake

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
