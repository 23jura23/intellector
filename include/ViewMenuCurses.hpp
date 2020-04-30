#ifndef _VIEW_MENU_CURSES_HPP_
#define _VIEW_MENU_CURSES_HPP_

#include <ncurses.h>

#include <stdexcept>
#include <vector>
#include <istream>

#include "ViewPictureCurses.hpp"

namespace viewCurses {

class MenuCurses {
   public:
    virtual ~MenuCurses() = default;
    virtual void show() = 0;
    Picture readPicture(std::istream& is);
};  // class MenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_CURSES_HPP_
