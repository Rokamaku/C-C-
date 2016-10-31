#include "board.h"

//draw board have width = width of terminal and height = height of terminal - 3
void Board::drawBoard() {
    attron(A_REVERSE);
    for (int i = 0; i < width; i++) {
        //print upperbound of game
        mvprintw(startBoardY, startBoardX + i, " ");
    }
    //print left and right bound of game
    for (int i = 0; i < height - 2; i++) {
        mvprintw(startBoardY + 1 + i, startBoardX, " ");                //left bound
        mvprintw(startBoardY + 1 + i, startBoardX + width - 1, " ");    //right bound
    }
    //print lower bound
    for (int i = 0; i < width; i++) {
        mvprintw(startBoardY + height - 1, startBoardX + i, " ");
    }
    refresh(); //show the bound
    attroff(A_REVERSE);
}

void Board::GamePlay() {
    Pos TopLeft, BotRight;  // position of top left corner and bottom right corner bound
    TopLeft.x = startBoardX;
    TopLeft.y = startBoardY;
    BotRight.x = startBoardX + width - 1;
    BotRight.y = startBoardY + height - 1;
    //init Snake with init posiotion of snake is in the central of bound
    Snake* snk = new Snake((startBoardY + height) / 2, (startBoardX + width) / 2);
    snk->initSnake();
    int Direction = 2; //default direction is right
    int KeyPress;
    //print the score at below the bound 1 unit
    mvprintw(startBoardY + height + 1  , startBoardX + 2, "Score: %d", Score);
    //create the fruit at random position inside the bound and except snake position
    initFruit(snk->getSnakePos(),snk->getSnakeHead());
    do {
        if (KeyPress == '\n')
        {
            //check enter pressed to pause game
            WINDOW* winPause = PauseGame();
            //wait for press any key to continue
            KeyPress = wgetch(winPause);
            //delete the window pause game
            destroy_win(winPause);
            //reprint fruit in case of fruit position inside pause window
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(Fruit.y, Fruit.x, "$");
            refresh();
            attroff(COLOR_PAIR(1) | A_BOLD);
        }

        //snake move inside the bound with defaut direction is right
        //it is also provided the bound and fruit position to check whether match snake postion or not
        //key pressed attached detect which direction next of snake
        int info = snk->SnakeMove(Direction, KeyPress, TopLeft, BotRight, Fruit);

        if (info == 0) //snake move normally
            continue;
        else if (info == 1) //if snake move reverse it current direction => ignore
            continue;
        else if (info == 2) //snake eat fruit
        {
            initFruit(snk->getSnakePos(), snk->getSnakeHead()); //create new fruit
            Score++;                                            //increse score
            mvprintw(startBoardY + height + 1 , startBoardX + 2, "Score: %d", Score); //print score
            refresh();//show score and fruit
            napms(snk->getSnakeSpeed() * 100);
        }
        else
        {
            //if snake size + fruit is equal area of bound => win game
            if (snk->getSnakePos().size() + 2 == (startBoardX + width - 2) * (startBoardY + height - 2))
                Victory = true;
            break; //in case snake hit the bound or hit its body => break game
        }
    } while(KeyPress != 27); //play game until esc button is pressed
    if (!snk->isAlive() && !Victory) //if snake is not alive and not winning show the window to end game
        EndGame();
    if (!snk->isAlive() && Victory) //if snake is not alive and winning show the window to end game
        WinGame();

}
//create the fruit
void Board::initFruit(vector<Pos> SnakePos, Pos SnakeHead) {
    srand(time(0)); //create the seed of random function
    int posX, posY; //postion of fruit
    //first, create the postion of fruit randomly in range of bound
    //then check whether fruit created match the snake position or not
    //if match, reinitliaze the fruit until not match
    while (true)
    {
        posX = startBoardX + 1 + rand() % (startBoardX + width - 2 - startBoardX);
        posY = 1 + rand() % (startBoardY + height - 2);
        bool matchSnake = false;
        //check fruit position match snake or not
        for (int i = 0; i < SnakePos.size(); i++)
            if (posX == SnakePos[i].x && posY == SnakePos[i].y)
            {
                matchSnake = true;
                break;
            }
        if (matchSnake) //if fruit match snake reinitliaze the fruit
            continue;
        if (posX == SnakeHead.x && posY == SnakeHead.y)
            continue;
        break;
    }
    //after check, return the position of fruit
    Fruit.x = posX;
    Fruit.y = posY;
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(Fruit.y, Fruit.x, "$"); //print fruit at position which initalized
    refresh(); //show the fruit
    attroff(COLOR_PAIR(1) | A_BOLD);
}
//after the snake die, show a window to inform the score and end game
void Board::EndGame() {
    //create new window with height, width, x position start and y start postion
    WINDOW* notiEnd = create_newwin(8, 26, (startBoardY + height) / 2 - 3, (startBoardX + width) /2 - 13);
    wattron(notiEnd, A_BOLD | COLOR_PAIR(2));
    mvwprintw(notiEnd, 2, 8, "GAME OVER!");
    mvwprintw(notiEnd, 4, 6, "Your score: %d", Score);
    move(0,0);
    wrefresh(notiEnd);//show the window
    napms(1000);
    mvwprintw(notiEnd, 5, 3, "Press ENTER to quit!", Score);
    wrefresh(notiEnd);
    wattroff(notiEnd, A_BOLD | COLOR_PAIR(2));
    while (wgetch(notiEnd) != '\n') {
        continue;
    }
}
//if win game, show this window
void Board::WinGame() {
    WINDOW* notiWin = create_newwin(6, 26, (startBoardY + height) / 2 - 3, (startBoardX + width) /2 - 13);
    wattron(notiWin, A_BOLD | COLOR_PAIR(2));
    mvwprintw(notiWin, 2, 6, "CONGRATULATION !");
    mvwprintw(notiWin, 4, 6, "You are winner !");
    move(0,0);
    wrefresh(notiWin);//show the window
    napms(1000);
    mvwprintw(notiWin, 5, 3, "Press ENTER to quit!", Score);
    wrefresh(notiWin);
    wattroff(notiWin, A_BOLD | COLOR_PAIR(2));
    while (wgetch(notiWin) != '\n') {
        continue;
    }

}

WINDOW* Board::PauseGame() {
    WINDOW* pauseWin = create_newwin(7, 28, (startBoardY + height) / 2 - 3, (startBoardX + width) /2 - 13);
    init_pair(3, COLOR_GREEN, COLOR_MAGENTA);
    wattron(pauseWin, A_BOLD | COLOR_PAIR(3));
    mvwprintw(pauseWin, 3, 7, "GAME PAUSED !");
    wattroff(pauseWin, A_BOLD | COLOR_PAIR(3));
    mvwprintw(pauseWin, 4, 1, "Press any key to continue!");
    move(0,0);
    wrefresh(pauseWin);
    return pauseWin;
}

//create the window
WINDOW* Board::create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
    return local_win;
}
//destroy teh window
void Board::destroy_win(WINDOW *local_win)
{
    int row, col;
    getmaxyx(local_win, row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            mvwprintw(local_win, i, j, " ");
    wrefresh(local_win);
    delwin(local_win);
}


