#ifndef _VIEW_PREVIEW_MENU_CURSES_HPP_
#define _VIEW_PREVIEW_MENU_CURSES_HPP_

#include "ViewMenuCurses.hpp"

namespace viewCurses {

class PreviewMenuCurses final : MenuCurses {
   public:
    void show() override;
};

}  // namespace viewCurses

#endif  // _VIEW_PREVIEW_MENU_CURSES_HPP_
