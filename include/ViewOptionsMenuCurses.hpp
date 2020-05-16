#ifndef _VIEW_OPTIONS_MENU_CURSES_HPP_
#define _VIEW_OPTIONS_MENU_CURSES_HPP_

#include <vector>

#include "ViewMainMenuCurses.hpp"

namespace viewCurses {

struct OptionsMenuCurses final : MainMenuCurses {
    OptionsMenuCurses();
    RET_CODE show(int) override;
    MENU_TYPE type() const override;
    //   private:
    //   void draw() override; ???

};  // class OptionsMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_OPTIONS_MENU_CURSES_HPP_
