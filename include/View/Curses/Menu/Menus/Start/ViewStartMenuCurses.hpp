#ifndef _VIEW_START_MENU_CURSES_HPP_
#define _VIEW_START_MENU_CURSES_HPP_

#include <vector>

#include "View/Curses/Menu/Menus/BasicButton/ViewMainMenuCurses.hpp"

namespace viewCurses {

struct StartMenuCurses final : MainMenuCurses {
    StartMenuCurses();
    RET_CODE show(int) override;
};  // class StartMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_START_MENU_CURSES_HPP_
