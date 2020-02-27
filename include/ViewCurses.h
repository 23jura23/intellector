#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include "ViewBase.h"
#include <ncurses.h>

class viewCurses : public viewBase {
public:
    viewCurses();
    ~viewCurses();

    void refresh();

private:
    void outBoard();
};

#endif
