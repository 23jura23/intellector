#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include <ncurses.h>
#include <string>
#include <vector>

#include "ViewBase.hpp"
#include "ViewModelCurses.hpp"

namespace ViewCurses {

class viewCurses : public viewBase {
    using pair = std::pair<size_t, size_t>;

public:
    viewCurses();
    viewCurses(ViewModelCurses&);
    ~viewCurses();

    void run();
    void update(ViewModelCurses&);
    void refresh_view();

private:
    struct ModelContainer {
        ModelContainer(ViewModelCurses&);
        ViewModelCurses& board;
    };

    std::unique_ptr<ModelContainer> container_;

    void outBoard();
    void outCell(const ViewModelCurses::ViewCellCurses&, pair);

    static constexpr size_t d = 7;
    static constexpr pair delta_down = { 0, 2 * (d - 3) };
    static constexpr pair delta_right_down = { (d + 3) + (d - 3), d - 3 };
    static constexpr pair delta_right_up = { 2 * (d + 3) + 2 * (d - 3), 0 };

    const int maxy, maxx;
    size_t tlx = d - 1, tly = 0; //top left x y

    pair getTL(pair); //get top left corner coordinates of cell

    Position currentPos;
};

}

#endif
