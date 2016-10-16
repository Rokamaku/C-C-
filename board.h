#ifndef BOARD_H
#define BOARD_H
#include "snake.h"
#include <random>
#endif // BOARD_H


class Board {
    int width;
    int height;
    int startBoardY;
    int startBoardX;
    Pos Fruit;
    int Score;
    WINDOW* create_newwin(int height, int width, int starty, int startx);
public:
    Board(int width, int height) {
        this->width = width ;
        this->height = height;
        startBoardX = (COLS - width) / 2;
        startBoardY = 0;
        Score = 0;
    }
    void drawBoard();
    void GamePlay();
    void initFruit(vector<Pos> , Pos);
    void EndGame();
};
