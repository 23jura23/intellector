#include <iostream>
#include "Board.hpp"
#include "ViewCurses.hpp"
#include "Game.hpp"

int main() {
    Board* board = new Board;
    Curses::viewCurses view(board->getBoard());
    while (getch())
        view.refresh_view();
    return 0;
}
