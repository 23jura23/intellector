#ifndef _VIEW_WIN_MENU_CURSES_HPP_
#define _VIEW_WIN_MENU_CURSES_HPP_

#include <vector>

#include "View/Curses/Menu/Menus/BasicButton/BasicButton.hpp"

namespace viewCurses {

struct WinMenuCurses final : MainMenuCurses {
    WinMenuCurses(PlayerColour);
    RET_CODE show(int) override;
    MENU_TYPE type() const override;

   private:
    std::pair<size_t, size_t> getTL() const override;

};  // class WinMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_WIN_MENU_CURSES_HPP_

