#include <memory.h>

#include <iostream>

#include "Board.hpp"
#include "Controller.hpp"
#include "Game.hpp"
#include "ViewCurses.hpp"
#include "ViewModelCurses.hpp"

int main() {
    try {
        std::shared_ptr<Game> game = std::make_shared<Game>();
        std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
        std::shared_ptr<ViewCurses::viewCurses> view =
            std::make_shared<ViewCurses::viewCurses>(controller);

        view->run();
        //    Board* board = new Board;
        //        ViewCurses::ViewModelCurses tmp = ViewCurses::ViewModelCurses
        //        { *board, PlayerColour::white_ }; ViewCurses::viewCurses
        //        view(std::make_shared<ViewCurses::ViewModelCurses>(*board,
        //        PlayerColour::white_)); view.run();
    } catch (const ViewBaseException& e) {
        std::cout << "View error: " << e.what() << std::endl;
    }
    return 0;
}
