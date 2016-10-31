#include "board.h"

#include <time.h>
#include <unistd.h>


void initWin();
void DisplayInfo();
int GetGameSpeed();
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
    int speed = GetGameSpeed();
    getch();
    clear();

    Board* board = new Board(COLS, LINES - 3); //create new board with width = width of terminal and height = height of terminal - 3
    board->drawBoard(); //create bound
    board->GamePlay(speed);  //in game
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
//display some information and get game speed
void DisplayInfo() {
    attron(A_BOLD);
    mvprintw(LINES / 3, COLS / 3 + 5, "SNAKE GAME");
    mvprintw(LINES / 3 + 2, COLS /3, "Bui Hoang Anh");
    mvprintw(LINES / 3 + 3, COLS /3, "Pham Nguyen Khanh Thinh");
    mvprintw(LINES / 3 + 4, COLS /3, "Nguyen Phuoc Sang");
    attroff(A_BOLD);
}

int GetGameSpeed() {
    attron(A_BOLD);
    mvprintw(LINES / 3 + 6, COLS /3, "Select game speed: " );
    mvprintw(LINES / 3 + 6, COLS / 3 + 22, "<|");
    mvprintw(LINES / 3 + 6, COLS / 3 + 27, "|>");
    int level = 1;
    int i = 0;
    int keyPressed;
    while ((keyPressed = getch()) != '\n') { //if player press enter play game with current level value
        //if press left level decrease;
        if (keyPressed == KEY_LEFT)
        {
            level--;
            attron(A_REVERSE);
            mvprintw(LINES / 3 + 6, COLS / 3 + 22, "<|");
            attroff(A_REVERSE);
            refresh();
            napms(80);
            attron(A_NORMAL);
            mvprintw(LINES / 3 + 6, COLS / 3 + 22, "<|");
            attroff(A_NORMAL);
            refresh();
        }
        //if press right level increase
        if (keyPressed == KEY_RIGHT) {
            level++;
            attron(A_REVERSE);
            mvprintw(LINES / 3 + 6, COLS / 3 + 27, "|>");
            attroff(A_REVERSE);
            refresh();
            napms(80);
            attron(A_NORMAL);
            mvprintw(LINES / 3 + 6, COLS / 3 + 27, "|>");
            attroff(A_NORMAL);
            refresh();
        }
        if (level > 9)      //max level = 9
            level = 1;
        if (level < 1)      //min level = 1
            level = 9;
        mvprintw(LINES / 3 + 6, COLS / 3 + 24, " %d ", level);  //print level to choose
        refresh();
        attron(COLOR_PAIR(4));
        // print a string of '*' character
        if (i == 19)
        {
            i = 0;
            for (int j = 0; j < 19; j++)
                mvprintw(LINES / 3 + 9, COLS / 3 + j, " ");
            refresh();
        }
        mvprintw(LINES / 3 + 9, COLS / 3 + i, "*");
        refresh();
        napms(250);
        i++;
        attroff(COLOR_PAIR(4));
    }
    mvprintw(LINES / 3 + 8, COLS /3, "Press ENTER to play");
    attroff(A_BOLD);
    return level;
}
