#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include "ViewBase.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

namespace Curses {

class viewCurses : public viewBase {
    using BoardField = std::vector<std::vector<Cell>>;
    using pair = std::pair<size_t, size_t>;

public:
    viewCurses(const BoardField& board);
    ~viewCurses();

    void update(const BoardField&);
    void refresh_view();

private:
    struct BoardFieldContainer {
        BoardFieldContainer(const BoardField&);
        const BoardField& board_;
    };

    std::unique_ptr<BoardFieldContainer> container_;

    void outBoard();
    void outFigure(const Cell&, pair);

    static constexpr size_t d = 7;
    static constexpr pair delta_down = { 0, 2 * (d - 3) };
    static constexpr pair delta_right_down = { (d + 3) + (d - 3), d - 3 };
    static constexpr pair delta_right_up = { 2 * (d + 3) + 2 * (d - 3), 0 };
    
    const int maxy, maxx;
    size_t tlx = d - 1, tly = 0; //top left x y

    pair getTL(pair); //get top left corner coordinates of cell
};

}

#endif
