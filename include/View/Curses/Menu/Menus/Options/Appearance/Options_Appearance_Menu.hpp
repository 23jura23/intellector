#ifndef _VIEW_OPTIONS_APPEARANCE_MENU_CURSES_HPP_
#define _VIEW_OPTIONS_APPEARANCE_MENU_CURSES_HPP_

#include <vector>

#include "View/Curses/Menu/Menus/BasicButton/BasicButton.hpp"

namespace viewCurses {

struct Options_Appearance_MenuCurses final : MainMenuCurses {
    Options_Appearance_MenuCurses();
    RET_CODE show(int) override;
    MENU_TYPE type() const override;
};  // class AppearanceMenCurses

}  // namespace viewCurses

#endif // _VIEW_OPTIONS_APPEARANCE_MENU_CURSES_HPP_
