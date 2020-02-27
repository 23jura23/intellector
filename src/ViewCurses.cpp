#include "Board.hpp"
#include "ViewCurses.h"

viewCurses::viewCurses()
{
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
}

viewCurses::~viewCurses()
{

    endwin();
}

void viewCurses::refresh()
{
    outBoard();
}

void viewCurses::outBoard()
{
    
}
