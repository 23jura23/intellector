#include "Board.hpp"
#include "Controller.cpp"
#include "ViewCurses.hpp"
#include "ViewModelCurses.hpp"
#include <iostream>

int main()
{
    Board* board = new Board;
    try {
        ViewCurses::viewCurses view;
        auto tmp = ViewCurses::ViewModelCurses { *board, PlayerColour::white_ };
        view.update(tmp);
        while (getch()) {
            view.refresh_view();
        }
    } catch (const ViewBaseException& e) {
        std::cout << "View error: " << e.what() << std::endl;
    }
    return 0;
}
