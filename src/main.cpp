#include "Board.hpp"
#include "Controller.cpp"
#include "ViewCurses.hpp"
#include "ViewModelCurses.hpp"
#include <iostream>

int main()
{
    Board* board = new Board;
    try {
        auto tmp = ViewCurses::ViewModelCurses { *board, PlayerColour::white_ };
        ViewCurses::viewCurses view(tmp);
        view.run();
    } catch (const ViewBaseException& e) {
        std::cout << "View error: " << e.what() << std::endl;
    }
    return 0;
}
