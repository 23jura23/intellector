#ifndef _VIEW_MENU_CURSES_HPP_
#define _VIEW_MENU_CURSES_HPP_

#include <ncurses.h>

#include <istream>
#include <stdexcept>
#include <vector>

#include "View/Curses/Model/ModelImpl/Picture/ViewPictureCurses.hpp"

namespace viewCurses {

class MenuException : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};

enum class RET_CODE;
enum class MENU_TYPE;

class MenuCurses {
   public:
    virtual ~MenuCurses() = default;
    virtual RET_CODE show(int c) = 0;
    virtual MENU_TYPE type() const;
};  // class MenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_CURSES_HPP_
