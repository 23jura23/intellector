#include "ViewMenuMultiplexerCurses.hpp"

#include <assert.h>

#include <iostream>
using std::cerr, std::endl;

#include "Board.hpp"
#include "Controller.hpp"
#include "Game.hpp"
#include "ViewCurses.hpp"
#include "ViewInitCurses.hpp"
#include "ViewMainMenuCurses.hpp"

namespace viewCurses {
RET_CODE MenuMultiplexerCurses::show() {
    auto er = freopen("error.txt", "a", stderr);
    static_cast<void>(er);
    initCurses();
    MainMenuCurses mainMenu;
    bool running = 1;
    RET_CODE rc;
    while (running) {
        RET_CODE act = mainMenu.show();
        switch (act) {
            case RET_CODE::NOTHING:
                break;
            case RET_CODE::FAILURE:
                throw MenuException("MainMenu crashed");
                break;
            case RET_CODE::START_NEW_GAME:
                rc = launchNewGame();
                static_cast<void>(rc);
                break;
            case RET_CODE::EXIT:
                running = 0;
                break;
        }
    }
    terminateCurses();
    assert(initCursesDone == 0);
    return RET_CODE::NOTHING;
}

RET_CODE MenuMultiplexerCurses::launchNewGame() {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
    // if one wants to add a network game, then the controller must be probably
    // not recreated each time, but created once with a game and passed here
    // as an argument
    // oh f*ck, controller is template and static...
    // so this crutch is needed:
    controller->updateViewModel<viewCurses::ViewCurses>();

    ViewCurses view = ViewCurses(controller);
    RET_CODE rc = view.show();
    return rc;
}

}  // namespace viewCurses
