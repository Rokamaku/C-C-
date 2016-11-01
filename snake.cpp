#include "snake.h"


//get snake speed
int Snake::getSnakeSpeed() {
    return SnakeSpeed;
}

//get coordinate of snake body
vector<Pos> Snake::getSnakePos() {
    return posSnake;
}
//set value for snake speed
void Snake::setSnakeSpeed(int Speed) {
    SnakeSpeed = Speed;
}

// initliaze the snake length = 2, head in the center of the board
// and the body in the left of head
void Snake::initSnake() {
    posSnake.push_back(Head);
    Pos NextHead;
    NextHead.x = Head.x-1;
    NextHead.y = Head.y;
    posSnake.push_back(NextHead);
}
//get coordinate of snake head
Pos Snake::getSnakeHead() {
    return Head;
}

//manage snake move include arrow button and another event which can affect in snake such as
//hit itself or hit the bound
//return the value to inform the board which event happen
// 0 - snake move normally
// 1 - player input the direction in the opposite of its current direction
// 2 - snake eat the fruit
// 3 - snake hit itself or the bound
int Snake::SnakeMove(int &Direction, int &KeyPress, Pos TopLeft, Pos BotRight, Pos Fruit) {
    if ((KeyPress=getch())) {
        if (KeyPress == KEY_LEFT) //case: input = left
        {
            if (Direction == 2) //if direction = right  => ignore
                return 1;
            Direction = 1;       //else direction = left
        }
        if (KeyPress == KEY_RIGHT)  //case: input = right
        {
            if (Direction == 1) //if direction = left => ignore
                return 1;
            Direction = 2;      //else direction = right
        }
        if (KeyPress == KEY_UP) //case: input = up
        {
            if (Direction == 4) //if direction = down -> ignore
                return 1;
            Direction = 3;       //else direction = up
        }
        if (KeyPress == KEY_DOWN) //case: input = down
        {
            if (Direction == 3)  //if direction = up => ignore
                return 1;
            Direction = 4;        // else direction = down
        }
    }
    //save tail postion in order to delete this postion in screen
    //or in case of snake it fruit snake will grow one more length so push it to vector of snake body
    Pos Tail = posSnake[posSnake.size()-1];
    //update new position of snake
    //each element will be assigned with its previous element
    for (int i = posSnake.size() - 1; i >= 1; i--) {
        posSnake[i] = posSnake[i-1];
    }
    posSnake[0] = Head;
    if (Direction == 1) //if direction = left
        Head.x -= 1;
    if (Direction == 2) //if direction = right
        Head.x += 1;
    if (Direction == 3) //if direction = down
        Head.y -= 1;
    if (Direction == 4) //if direction = up
        Head.y += 1;

    attron(A_BOLD);
    mvprintw(Head.y,Head.x,"@"); //print new position of snake head
    //print the body of snake
    for (int i = 0; i < posSnake.size(); i++)
    {
        mvprintw(posSnake[i].y, posSnake[i].x, "o");
    }
    attroff(A_BOLD);
    // in case of new position of head match fruit postion => return 2
    if (Head.x == Fruit.x && Head.y == Fruit.y)
    {
        posSnake.push_back(Tail); //add tail to vector
        return 2;
    }
    //delete tail
    mvprintw(Tail.y,Tail.x," ");
    // in case of snake hit its body or hit the bound
    if (isHitMyselft() || isHitBoard(TopLeft, BotRight))
    {
        Alive = false;                  //snake die
        mvprintw(Head.y, Head.x, "x");  //print conflict position
        refresh();
        napms(100);
        mvprintw(Head.y, Head.x, "X");
        refresh();
        napms(500);
        return 3;
    }
    move(0,0);
    refresh(); //show the snake into screen
    napms(SnakeSpeed); //delay of each snake movement
    return 0;
}

bool Snake::isAlive() {
    if (Alive)
        return true;
    return false;
}

// check whether head match any its body or not
bool Snake::isHitMyselft() {
    for (int i = 0; i < posSnake.size(); i++) {
        if (Head.x == posSnake[i].x && Head.y == posSnake[i].y)
            return true;
    }
    return false;
}

// check whether head match the bound or not
bool Snake::isHitBoard(Pos TopLeft, Pos BotRight) {
    if (Head.x == TopLeft.x || Head.y == TopLeft.y || Head.x == BotRight.x || Head.y == BotRight.y)
        return true;
    return false;
}
