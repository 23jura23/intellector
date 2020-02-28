#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include "ViewBase.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

class viewCurses : public viewBase {
public:
    viewCurses();
    ~viewCurses();

    void refresh();

private:
    void outBoard();
    struct hexCell {
        using Paint = std::vector<std::string>;
        size_t x,y; //left top angle 
        const int d = 7; //edge size
        size_t xsize = d-1 + d + d-1, ysize = d-1 + 1 + d-1; //size of Paint
        Paint draw;
        hexCell(Figure,size_t, size_t); 
    };
};

#endif
