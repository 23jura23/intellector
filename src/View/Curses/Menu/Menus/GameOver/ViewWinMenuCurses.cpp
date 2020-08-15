#include "View/Curses/Menu/Menus/GameOver/ViewWinMenuCurses.hpp"

#include <assert.h>

#include "View/Curses/Menu/Multiplexer/ViewMenuMultiplexerCurses.hpp"
#include "View/Curses/Menu/ViewMenuTypes.hpp"

namespace viewCurses {

WinMenuCurses::WinMenuCurses(PlayerColour colour)
        : MainMenuCurses{[colour]() {
            if (colour == PlayerColour::white_)
                return buttonsVectorT{{"resources/white_wins.btn", BUTTON_STYLE::NONE}};
            else
                return buttonsVectorT{{"resources/black_wins.btn", BUTTON_STYLE::NONE}};
        }()} {
}

RET_CODE WinMenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
        case -1:
            break;
        default:
            rc = RET_CODE::BACK;
            break;
    }
    return rc;
}

MENU_TYPE WinMenuCurses::type() const {
    return MENU_TYPE::RULES_MENU;
}

std::pair<size_t, size_t> WinMenuCurses::getTL() const {
    int maxx = getmaxx(stdscr);
    int maxy = getmaxy(stdscr);
    return {maxx / 2 - maxButtonWidth_ / 2, maxy / 2 - maxButtonHeight_};
}

};  // namespace viewCurses
