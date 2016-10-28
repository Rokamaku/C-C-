#include "board.h"

#include <time.h>
#include <unistd.h>


void initWin();
void DisplayInfo();
int main()
{
    initWin();
    if (COLS < 28 || LINES < 8) //if terminal size is too small exit game
    {
        mvprintw(0, 0, "Too small to display!");
        refresh();
        getch();
        endwin();
        return 1;
    }
    DisplayInfo();
    //mvprintw(LINES / 2, COLS / 2, "SNAKE");
    int key;
    getch();
    clear();

    Board* board = new Board(COLS, LINES - 3); //create new board with width = width of terminal and height = height of terminal - 3
    board->drawBoard(); //create bound
    board->GamePlay();  //in game
    getch();    //wait any key pressed
    endwin();   //escape curse mode
    return 0;
}

void initWin() {
    if (getenv ("ESCDELAY") == NULL) //adjust the time esc delay = 25ms
        ESCDELAY = 25;
    initscr(); //switch on curse mode
    cbreak(); // Line buffering disabled. pass on everything
    noecho(); //do not show key pressed in screen
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0); //do not show cursor in screen if terminal support
    start_color(); //start color mode of terminal
    init_pair(1, COLOR_RED, COLOR_BLACK); //create a pair of color: fore color and background color
    init_pair(2,COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_MAGENTA);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

}
//display some information
void DisplayInfo() {
    attron(A_BOLD);
    mvprintw(LINES / 3, COLS / 3 + 5, "SNAKE GAME");
    mvprintw(LINES / 3 + 2, COLS /3, "Bui Hoang Anh");
    mvprintw(LINES / 3 + 3, COLS /3, "PHam Nguyen Khanh Thinh");
    mvprintw(LINES / 3 + 4, COLS /3, "Nguyen Phuoc Sang");
    attron(A_BLINK);
    mvprintw(LINES / 3 + 6, COLS /3, "Press ENTER to play");
    attroff(A_BLINK);
    attroff(A_BOLD);
    attron(A_BOLD | COLOR_PAIR(4));
    int i = 0;
    int key;
    do {
        if (i == 19)
        {
            i = 0;
            for (int j = 0; j < 19; j++)
                mvprintw(LINES / 3 + 7, COLS / 3 + j, " ");
            refresh();
        }
        mvprintw(LINES / 3 + 7, COLS / 3 + i, "*");
        refresh();
        napms(250);
        i++;
    } while (key = getch() != '\n');
    attroff(A_BOLD |COLOR_PAIR(4));
    //refresh();
}
