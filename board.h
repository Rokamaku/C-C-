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
    bool Victory; //win or not
    WINDOW* create_newwin(int height, int width, int starty, int startx); //create a window
    void destroy_win(WINDOW *local_win); //and destroy window
public:
    Board(int width, int height) {
        this->width = width ;
        this->height = height;
        startBoardX = (COLS - width) / 2;
        startBoardY = 0;
        Score = 0;
        Victory = false;
    }
    void drawBoard();
    void GamePlay();
    void initFruit(vector<Pos> , Pos);
    WINDOW* PauseGame();
    void EndGame();
    void WinGame();
};
