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
#include "ViewMenuTypes.hpp"
#include "ViewRulesMenuCurses.hpp"
#include "ViewOptionsMenuCurses.hpp"
#include "ViewStartMenuCurses.hpp"

using std::vector, std::shared_ptr, std::make_shared, std::dynamic_pointer_cast;

namespace viewCurses {

bool MenuWithRC::operator==(const MenuWithRC& other) {
    return menu == other.menu && rc == other.rc;
}

//RET_CODE MenuMultiplexerCurses::show_old() {
//    auto er = freopen("error.txt", "a", stderr);
//    static_cast<void>(er);
//    initCurses();
//
//    MainMenuCurses mainMenu;
//    bool running = 1;
//    RET_CODE rc;
//    while (running) {
//        RET_CODE act = mainMenu.show();
//        switch (act) {
//            case RET_CODE::NOTHING:
//                break;
//            case RET_CODE::FAILURE:
//                throw MenuException("MainMenu crashed");
//                break;
//            case RET_CODE::START_NEW_GAME:
//                rc = launchNewGame();
//                static_cast<void>(rc);
//                break;
//            case RET_CODE::EXIT:
//                running = 0;
//                break;
//        }
//    }
//    terminateCurses();
//    assert(initCursesDone == 0);
//    return RET_CODE::NOTHING;
//}

//template <>
//shared_ptr<MenuCurses> MenuMultiplexerCurses::createMenu<MULTIPLEXABLE_MENU::MAIN_MENU>() {
//    return dynamic_pointer_cast<MenuCurses>(make_shared<MainMenuCurses>());
//}
//
//template <>
//shared_ptr<MenuCurses> MenuMultiplexerCurses::createMenu<MULTIPLEXABLE_MENU::GAME_MENU, Args...>(const Args& args) {
//    return dynamic_pointer_cast<MenuCurses>(make_shared<MainMenuCurses>(args));
//}

//template <typename... Args>
//shared_ptr<MenuCurses> MenuMultiplexerCurses::createMenu(MULTIPLEXABLE_MENU menu,
//                                                         const Args&... args) {
//    switch (menu) {
//        case MULTIPLEXABLE_MENU::WELCOME_MENU:
//            break;
//        case MULTIPLEXABLE_MENU::MAIN_MENU:
//            return dynamic_pointer_cast<MenuCurses>(make_shared<MainMenuCurses>());
//        case MULTIPLEXABLE_MENU::GAME_MENU:
//            return dynamic_pointer_cast<MenuCurses>(make_shared<ViewCurses>(args...));
//    }
//    throw MenuException("createMenu: tried to create unknown menu");
//}

MenuMultiplexerCurses::MenuMultiplexerCurses() {
    auto er = freopen("error.txt", "a", stderr);
    static_cast<void>(er);
    initCurses();

    shared_ptr<MenuCurses> mainMenu =
        dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
    //        createMenu(MULTIPLEXABLE_MENU::MAIN_MENU);
    aliveMenus.push_back({mainMenu, RET_CODE::NOTHING});
}

MenuMultiplexerCurses::~MenuMultiplexerCurses() {
    terminateCurses();
}

MENU_TYPE MenuMultiplexerCurses::type() const {
    return MENU_TYPE::MULTIPLEXER_MENU;
}

// Multiplexer do not need chars to run: it get them directly from io and send to other menus
RET_CODE MenuMultiplexerCurses::show(int) {
    // initial stage
    for (auto& menuRC : aliveMenus) {
        menuRC.rc = menuRC.menu->show(
            0);  // 0 = do nothing, just draw. TODO(23jura23) check if all menus actually obey this
    }

    bool running = 1;
    while (running) {
        // sending stage
        int c = getch();
        for (auto& menuRC : aliveMenus) {
            menuRC.rc = menuRC.menu->show(c);
        }

        // processing return codes stage
        vector<MenuWithRC> cashedAliveMenus(aliveMenus);
        for (auto& menuRC : cashedAliveMenus) {
            RET_CODE processRC = RET_CODE::NOTHING;
            switch (menuRC.menu->type()) {
                case MENU_TYPE::BASE_MENU:
                    throw MenuException("Basic MenuCurses is alive: who created it?!");
                case MENU_TYPE::MULTIPLEXER_MENU:
                    throw("MultiplexerMenu is alive: nested multiplexers are not allowed");
                case MENU_TYPE::MAIN_MENU:
                    processRC = processStartMenu(menuRC);
                    break;
                case MENU_TYPE::GAME_MENU:
                    processRC = processGameMenu(menuRC);
                    break;
                case MENU_TYPE::RULES_MENU:
                    processRC = processRulesMenu(menuRC);
                    break;
                case MENU_TYPE::OPTIONS_MENU:
                    processRC = processOptionsMenu(menuRC);
                    break;
                case MENU_TYPE::WELCOME_MENU:
                    processRC = processWelcomeMenu(menuRC);
                    break;
            }
            switch (processRC) {
                case RET_CODE::EXIT:
                    running = 0;
                    break;
                default:
                    break;
            }
        }
    }
    return RET_CODE::NOTHING;
}

// To add a new main submenu one needs to:
// add processMENUNAME(...)
// add struct MENUNAME final : MainMenuCurses {
//   MENUNAME();
//   RET_CODE show(int) override;
//   MENU_TYPE type() const override;
// }
//
// init MainMenuCurses with vector of {path, button_type}
// make some changes in show (after copy-paste :)
// add new type to ViewMenuTypes.hpp and return in in type()
//
// algo add return code to startMenu to be able to enter MENUNAME
//
// write in processMENUNAME some logic with multiplexing it: who creates it (in other processNAME-s), how to exit it (some BACK code, mm?), and so on
// processMENUNAME may either: createNewMenu, deleting the old one (also somewhere starting the game); something else?

RET_CODE MenuMultiplexerCurses::processStartMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::START_NEW_GAME: {
            auto newGameMenu = launchNewGame();
            newGameMenu->show(0);  // initial show
            aliveMenus.push_back({newGameMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::RULES_MENU: {
            auto newOptionsMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<RulesMenuCurses>());
            newOptionsMenu->show(0);  // initial show
            aliveMenus.push_back({newOptionsMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::OPTIONS_MENU: {
            auto newOptionsMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<OptionsMenuCurses>());
            newOptionsMenu->show(0);  // initial show
            aliveMenus.push_back({newOptionsMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::EXIT:
            rc = RET_CODE::EXIT;
            break;
        default:
            throw MenuException("processStartMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processGameMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::GAME_OVER_WHITE_WIN:  // TODO(23jura23) distinguish them some way?
        case RET_CODE::GAME_OVER_BLACK_WIN:
        case RET_CODE::GAME_OVER_UNEXPECTEDLY:
        case RET_CODE::GAME_EXIT: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            newMainMenu->show(0);  // initial show
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processStartMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processRulesMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::BACK: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            newMainMenu->show(0);  // initial show
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processOptionsMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processOptionsMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::BACK: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            newMainMenu->show(0);  // initial show
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processOptionsMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processWelcomeMenu(MenuWithRC& menuRC) {
    static_cast<void>(menuRC);
    return RET_CODE::NOTHING;
}

shared_ptr<MenuCurses> MenuMultiplexerCurses::launchNewGame() {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
    // if one wants to add a network game, then the controller must be probably
    // not recreated each time, but created once with a game and passed here
    // as an argument
    // oh f*ck, controller is template and static...
    // so this crutch is needed:
    controller->updateViewModel<viewCurses::ViewCurses>();

    return dynamic_pointer_cast<MenuCurses>(make_shared<ViewCurses>(controller));
    //)createMenu(MULTIPLEXABLE_MENU::GAME_MENU, controller);
    //    ViewCurses view = ViewCurses(controller);
    //    RET_CODE rc = view.show();
    //    return rc;
}

}  // namespace viewCurses
