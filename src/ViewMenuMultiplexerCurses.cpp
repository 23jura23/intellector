#include "ViewMenuMultiplexerCurses.hpp"

#include <assert.h>

#include <iostream>
using std::cerr, std::endl;

#include "Board.hpp"
#include "Controller.hpp"
#include "Game.hpp"
#include "ViewGameMenuCurses.hpp"
#include "ViewHistoryMenuCurses.hpp"
#include "ViewInitCurses.hpp"
#include "ViewMainMenuCurses.hpp"
#include "ViewMenuTypes.hpp"
#include "ViewOptionsMenuCurses.hpp"
#include "ViewOptions_Gameplay_MenuCurses.hpp"
#include "ViewRulesMenuCurses.hpp"
#include "ViewStartMenuCurses.hpp"
#include "ViewWinMenuCurses.hpp"

using std::vector, std::shared_ptr, std::make_shared, std::dynamic_pointer_cast;

namespace viewCurses {

bool MenuWithRC::operator==(const MenuWithRC& other) {
    return menu == other.menu && rc == other.rc;
}

auto lambdaFindersFactory(MENU_TYPE type) {
    return [type](const MenuWithRC& menuRC_) { return menuRC_.menu->type() == type; };
}

MenuMultiplexerCurses::MenuMultiplexerCurses()
        : settings_{0, 4, 0, 1} {
    auto er = freopen("error.txt", "a", stderr);
    static_cast<void>(er);
    initCurses();

    shared_ptr<MenuCurses> mainMenu =
        dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
    aliveMenus.push_back({mainMenu, RET_CODE::NOTHING});
}

MenuMultiplexerCurses::~MenuMultiplexerCurses() {
    if (aliveMenus.size()) {
        for (int i = aliveMenus.size() - 1; i >= 0; --i) {
            aliveMenus[i].menu.reset();
        }
    }
    terminateAllCurses();
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
        if (forceRedraw) {
            clear();
            for (auto& menuRC : aliveMenus) {
                menuRC.rc = menuRC.menu->show(0);
            }
            forceRedraw = 0;
        }

        int c{};
        c = getch();
        cerr << "c: " << c << endl;

        cerr << "GOT " << c << '\n';

        clear();
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
                case MENU_TYPE::OPTIONS_GAMEPLAY_MENU:
                    processRC = processOptions_Gameplay_Menu(menuRC);
                    break;
                case MENU_TYPE::WELCOME_MENU:
                    processRC = processWelcomeMenu(menuRC);
                    break;
                case MENU_TYPE::HISTORY_MENU:
                    processRC = processHistoryMenu(menuRC);
                    break;
                default:
                    throw MenuException("Menu type not handled!");
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

// TODO exception if find(...) or find_if(...) failed

RET_CODE MenuMultiplexerCurses::processStartMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::START_NEW_GAME: {
            auto newGameMenu = launchNewGame();
            forceRedraw = 1;
            aliveMenus.push_back({newGameMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::RULES_MENU: {
            auto newRulesMenu = dynamic_pointer_cast<MenuCurses>(make_shared<RulesMenuCurses>());
            forceRedraw = 1;
            aliveMenus.push_back({newRulesMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::OPTIONS_MENU: {
            auto newOptionsMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<OptionsMenuCurses>());
            forceRedraw = 1;
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
        case RET_CODE::HISTORY_MENU_ENABLE: {
            auto newHistoryMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<HistoryMenuCurses>(getController()));
            forceRedraw = 1;
            aliveMenus.push_back({newHistoryMenu, RET_CODE::NOTHING});
            break;
        }
        case RET_CODE::HISTORY_MENU_DISABLE: {
            auto findHistoryMenuLambda = lambdaFindersFactory(MENU_TYPE::HISTORY_MENU);
            aliveMenus.erase(find_if(aliveMenus.begin(), aliveMenus.end(), findHistoryMenuLambda));
            forceRedraw = 1;
            break;
        }
        case RET_CODE::GAME_OVER_WHITE_WIN: {
            auto newWinMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<WinMenuCurses>(PlayerColour::white_));
            forceRedraw = 1;
            aliveMenus.push_back({newWinMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::GAME_OVER_BLACK_WIN: {
            auto newWinMenu =
                dynamic_pointer_cast<MenuCurses>(make_shared<WinMenuCurses>(PlayerColour::black_));
            forceRedraw = 1;
            aliveMenus.push_back({newWinMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::GAME_OVER_UNEXPECTEDLY:  // TODO(23jura23) some logging or message about unexpected game finish?
        case RET_CODE::GAME_EXIT: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            forceRedraw = 1;
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            auto findHistoryMenuLambda = lambdaFindersFactory(MENU_TYPE::HISTORY_MENU);
            auto historyMenuRC =
                find_if(aliveMenus.begin(), aliveMenus.end(), findHistoryMenuLambda);
            if (historyMenuRC != aliveMenus.end()) {
                aliveMenus.erase(historyMenuRC);
            }
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
            forceRedraw = 1;
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processRulesMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processWinMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::BACK: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            forceRedraw = 1;
            aliveMenus.push_back({newMainMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processRulesMenu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processOptionsMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::OPTIONS_GAMEPLAY: {
            auto newMenu = dynamic_pointer_cast<MenuCurses>(
                make_shared<Options_Gameplay_MenuCurses>(settings_));
            forceRedraw = 1;
            aliveMenus.push_back({newMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        case RET_CODE::BACK: {
            auto newMainMenu = dynamic_pointer_cast<MenuCurses>(make_shared<StartMenuCurses>());
            forceRedraw = 1;
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

RET_CODE MenuMultiplexerCurses::processOptions_Gameplay_Menu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        case RET_CODE::BACK: {
            settings_ = dynamic_pointer_cast<Options_Gameplay_MenuCurses>(menuRC.menu)->getRV();
            auto newMenu = dynamic_pointer_cast<MenuCurses>(make_shared<OptionsMenuCurses>());
            forceRedraw = 1;
            aliveMenus.push_back({newMenu, RET_CODE::NOTHING});
            aliveMenus.erase(find(aliveMenus.begin(), aliveMenus.end(), menuRC));
            break;
        }
        default:
            throw MenuException("processOptions_Gameplay_Menu: wrong return code");
            break;
    }
    return rc;
}

RET_CODE MenuMultiplexerCurses::processWelcomeMenu(MenuWithRC& menuRC) {
    static_cast<void>(menuRC);
    return RET_CODE::NOTHING;
}

RET_CODE MenuMultiplexerCurses::processHistoryMenu(MenuWithRC& menuRC) {
    RET_CODE rc = RET_CODE::NOTHING;
    switch (menuRC.rc) {
        case RET_CODE::NOTHING:
            break;
        default:
            throw MenuException("processHistoryMenu: wrong return code");
            break;
    }
    return rc;
}

std::shared_ptr<Controller> MenuMultiplexerCurses::getController() {
    if (!controller__.has_value())
        controller__ = std::make_shared<Controller>(getGame());
    return *controller__;
}

std::shared_ptr<Game> MenuMultiplexerCurses::getGame() {
    if (!game__.has_value())
        game__ = std::make_shared<Game>(settings_);
    return *game__;
}

shared_ptr<MenuCurses> MenuMultiplexerCurses::launchNewGame() {
    game__.reset();
    controller__.reset();
    std::shared_ptr<Controller> controller = getController();
    // if one wants to add a network game, then the controller must be probably
    // not recreated each time, but created once with a game and passed here
    // as an argument
    // oh, controller is template and static...
    // so this crutch is needed:
    controller->updateViewModel<viewCurses::ViewGameMenuCurses>();

    return dynamic_pointer_cast<MenuCurses>(make_shared<ViewGameMenuCurses>(controller));
}

}  // namespace viewCurses
