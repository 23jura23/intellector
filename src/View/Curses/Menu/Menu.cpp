#include "View/Curses/Menu/Menu.hpp"

#include "View/Curses/Menu/MenuTypes.hpp"

namespace viewCurses {

MENU_TYPE MenuCurses::type() const {
    return MENU_TYPE::BASE_MENU;
}

}  // namespace viewCurses
