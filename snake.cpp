#include "snake.h"


int Snake::getSnakeSpeed() {
    return SnakeSpeed;
}

vector<Pos> Snake::getSnakePos() {
    return posSnake;
}

void Snake::setSnakeSpeed(int Speed) {
    SnakeSpeed = Speed;
}

void Snake::initSnake() {
    posSnake.push_back(Head);
    Pos NextHead;
    NextHead.x = Head.x-1;
    NextHead.y = Head.y;
    posSnake.push_back(NextHead);
}

Pos Snake::getSnakeHead() {
    return Head;
}

int Snake::SnakeMove(int &Direction, int &KeyPress, Pos TopLeft, Pos BotRight, Pos Fruit) {
    if ((KeyPress=getch())) {
        if (KeyPress == KEY_LEFT)
        {
            if (Direction == 2)
                return 1;
            Direction = 1;
        }
        if (KeyPress == KEY_RIGHT)
        {
            if (Direction == 1)
                return 1;
            Direction = 2;
        }
        if (KeyPress == KEY_UP)
        {
            if (Direction == 4)
                return 1;
            Direction = 3;
        }
        if (KeyPress == KEY_DOWN)
        {
            if (Direction == 3)
                return 1;
            Direction = 4;
        }
    }
    Pos Tail = posSnake[posSnake.size()-1];
    for (int i = posSnake.size() - 1; i >= 1; i--) {
        posSnake[i] = posSnake[i-1];
    }
    posSnake[0] = Head;
    if (Direction == 1)
        Head.x -= 1;
    if (Direction == 2)
        Head.x += 1;
    if (Direction == 3)
        Head.y -= 1;
    if (Direction == 4)
        Head.y += 1;
    if (Head.x == Fruit.x && Head.y == Fruit.y)
    {
        posSnake.push_back(Tail);
        return 2;
    }
    attron(A_BOLD);
    mvprintw(Head.y,Head.x,"@");
    for (int i = 0; i < posSnake.size(); i++)
    {
        mvprintw(posSnake[i].y, posSnake[i].x, "o");
    }
    attroff(A_BOLD);
    mvprintw(Tail.y,Tail.x," ");
    if (isHitMyselft() || isHitBoard(TopLeft, BotRight))
    {
        Alive = false;
        mvprintw(Head.y, Head.x, "x");
        refresh();
        napms(100);
        mvprintw(Head.y, Head.x, "X");
        refresh();
        napms(100);
        return 3;
    }
    move(0,0);
    refresh();
    napms(250);
    return 0;
}

bool Snake::isAlive() {
    if (Alive)
        return true;
    return false;
}


bool Snake::isHitMyselft() {
    for (int i = 0; i < posSnake.size(); i++) {
        if (Head.x == posSnake[i].x && Head.y == posSnake[i].y)
            return true;
    }
    return false;
}

bool Snake::isHitBoard(Pos TopLeft, Pos BotRight) {
    if (Head.x == TopLeft.x || Head.y == TopLeft.y || Head.x == BotRight.x || Head.y == BotRight.y)
        return true;
    return false;
}
