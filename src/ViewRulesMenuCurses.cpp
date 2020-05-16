#include "ViewRulesMenuCurses.hpp"

#include <assert.h>

#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {

RulesMenuCurses::RulesMenuCurses()
        : MainMenuCurses{{
              {"resources/intellector_info_rules.btn", BUTTON_STYLE::NONE},
          }} {
}

RET_CODE RulesMenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
        default:
            rc = RET_CODE::BACK;
            break;
    }
    return rc;
}

MENU_TYPE RulesMenuCurses::type() const {
    return MENU_TYPE::RULES_MENU;
}

std::pair<size_t, size_t> RulesMenuCurses::getTL() const {
    int maxx = getmaxx(stdscr);
    int maxy = getmaxy(stdscr);
    return {maxx / 2 - maxButtonWidth_ / 2, maxy / 2 - maxButtonHeight_};
}

};  // namespace viewCurses
