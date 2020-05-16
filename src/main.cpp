#include <memory.h>

#include <iostream>

#include "ViewInitCurses.hpp"
#include "ViewMenuCurses.hpp"
#include "ViewMenuMultiplexerCurses.hpp"

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
    } catch (const viewCurses::MenuException& e) {
        std::cout << "Menu error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Unknown exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error" << std::endl;
    }
    return 0;
}
