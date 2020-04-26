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
        std::shared_ptr<viewCurses::ViewCurses> view =
            std::make_shared<viewCurses::ViewCurses>(controller);

        view->run();
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
