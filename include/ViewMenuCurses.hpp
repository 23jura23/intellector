#ifndef _VIEW_MENU_CURSES_HPP_
#define _VIEW_MENU_CURSES_HPP_

#include <ncurses.h>

#include <istream>
#include <stdexcept>
#include <vector>

#include "ViewPictureCurses.hpp"

namespace viewCurses {

class MenuException : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};

enum class RET_CODE;

class MenuCurses {
   public:
    virtual ~MenuCurses() = default;
    virtual RET_CODE show() = 0;
};  // class MenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_CURSES_HPP_
