#include "board.h"


#include <time.h>
#include <unistd.h>


void initWin();
int main()
{
    initWin();
    if (COLS < 5 || LINES < 8)
    {
        mvprintw(0, 0, "Too small to display!");
        getch();
        endwin();
        return 1;
    }
    Board* board = new Board(COLS, LINES - 3);
    board->drawBoard();
    board->GamePlay();
    getch();
    endwin();
    return 0;
}

void initWin() {
    if (getenv ("ESCDELAY") == NULL)
      ESCDELAY = 25;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2,COLOR_CYAN, COLOR_BLACK);

}
