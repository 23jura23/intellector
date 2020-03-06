#include <iostream>
#include "Board.hpp"
#include "ViewCurses.hpp"
#include "Controller.cpp"

int main() {
    Board* board = new Board;
    Curses::viewCurses view(board->data_);
    while (getch())
        view.refresh_view();
    return 0;
}
