#include "View/Curses/Menu/ViewMenuCurses.hpp"

#include "View/Curses/Menu/ViewMenuTypes.hpp"

namespace viewCurses {

MENU_TYPE MenuCurses::type() const {
    return MENU_TYPE::BASE_MENU;
}

}  // namespace viewCurses
