#include "board.h"


void Board::drawBoard() {
    attron(A_REVERSE);
    for (int i = 0; i < width; i++) {
        mvprintw(startBoardY, startBoardX + i, " ");
    }
    for (int i = 0; i < height - 2; i++) {
        mvprintw(startBoardY + 1 + i, startBoardX, " ");
        mvprintw(startBoardY + 1 + i, startBoardX + width - 1, " ");
    }
    for (int i = 0; i < width; i++) {
        mvprintw(startBoardY + height - 1, startBoardX + i, " ");
    }
    refresh();
    attroff(A_REVERSE);
}

void Board::GamePlay() {
    Pos TopLeft, BotRight;
    TopLeft.x = startBoardX;
    TopLeft.y = startBoardY;
    BotRight.x = startBoardX + width - 1;
    BotRight.y = startBoardY + height - 1;
    Snake* snk = new Snake((startBoardY + height) / 2, (startBoardX + width) / 2);
    snk->initSnake();
    int Direction = 2;
    int KeyPress;
    mvprintw(startBoardY + height + 1  , startBoardX + 2, "Score: %d", Score);
    initFruit(snk->getSnakePos(),snk->getSnakeHead());
    do {
        int info = snk->SnakeMove(Direction, KeyPress, TopLeft, BotRight, Fruit);
        if (info == 0)
            continue;
        else if (info == 1)
            continue;
        else if (info == 2)
        {
            initFruit(snk->getSnakePos(), snk->getSnakeHead());
            Score++;
            mvprintw(startBoardY + height +1 , startBoardX + 2, "Score: %d", Score);
            refresh();
        }
        else
            break;
    } while(KeyPress != 27);
    if (!snk->isAlive())
        EndGame();
}

void Board::initFruit(vector<Pos> SnakePos, Pos SnakeHead) {
    srand(time(0));
    int posX, posY;
    while (true)
    {
        posX = startBoardX + 1 + rand() % (startBoardX + width - 2 - startBoardX);
        posY = 1 + rand() % (startBoardY + height - 2);
        for (int i = 0; i < SnakePos.size(); i++)
            if (posX == SnakePos[i].x && posY == SnakePos[i].y)
                continue;
        if (posX == SnakeHead.x && posY == SnakeHead.y)
            continue;
        break;
    }
    Fruit.x = posX;
    Fruit.y = posY;
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(Fruit.y, Fruit.x, "$");
    refresh();
    attroff(COLOR_PAIR(1) | A_BOLD);
}

void Board::EndGame() {
    WINDOW* notiEnd = create_newwin(6, 26, (startBoardY + height) / 2 - 3, (startBoardX + width) /2 - 13);
    wattron(notiEnd, A_BOLD | COLOR_PAIR(2));
    mvwprintw(notiEnd, 2, 8, "GAME OVER!");
    mvwprintw(notiEnd, 4, 6, "Your score: %d", Score);
    wattroff(notiEnd, A_BOLD | COLOR_PAIR(2));
    move(0,0);
    wrefresh(notiEnd);
    napms(1000);
}

WINDOW* Board::create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
    return local_win;
}
