#include "ViewCurses.hpp"
#include "Board.hpp"

#include <assert.h>

viewCurses::viewCurses()
{
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
    assert(wresize(stdscr, 300,400) == OK);
    
}

viewCurses::hexCell::hexCell(Figure figure, size_t x, size_t y)
    : x { x }
    , y { y }
    , draw { xsize }
{
    
    switch (figure) {
    case Figure::INTELLECTOR:
        draw = {
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "...................",
            "..................."
        };
        break;
    case Figure::DOMINATOR:

        break;
    case Figure::AGGRESSOR:

        break;
    case Figure::DEFENSSOR:

        break;
    case Figure::LIERATOR:

        break;
    case Figure::PROGRESSOR:

        break;
    }
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
