#ifndef _VIEW_RULES_MENU_CURSES_HPP_
#define _VIEW_RULES_MENU_CURSES_HPP_

#include <vector>

#include "View/Curses/Menu/Menus/BasicButton/BasicButton.hpp"

namespace viewCurses {

struct RulesMenuCurses final : MainMenuCurses {
    RulesMenuCurses();
    RET_CODE show(int) override;
    MENU_TYPE type() const override;

   private:
    std::pair<size_t, size_t> getTL() const override;

};  // class RulesMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_RULES_MENU_CURSES_HPP_
