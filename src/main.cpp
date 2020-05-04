#include <memory.h>

#include <iostream>

#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewInitCurses.hpp"

int main() {
    try {
        viewCurses::MenuMultiplexerCurses menuMultiplexer;
        viewCurses::RET_CODE rc = menuMultiplexer.show();
        static_cast<void>(rc);
//        if (initCursesDone != 0)
//            throw MenuException("Not all menus were closed and ncurses is still running");
        //    Board* board = new Board;
        //        viewCurses::ViewModelCurses tmp = viewCurses::ViewModelCurses
        //        { *board, PlayerColour::white_ }; viewCurses::ViewCurses
        //        view(std::make_shared<viewCurses::ViewModelCurses>(*board,
        //        PlayerColour::white_)); view.run();
    } catch (const ViewBaseException& e) {
        std::cout << "View error: " << e.what() << std::endl;
    }
    return 0;
}
