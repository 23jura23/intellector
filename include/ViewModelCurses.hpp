#ifndef _VIEW_MODEL_CURSES_HPP
#define _VIEW_MODEL_CURSES_HPP

#include "Board.hpp"
#include "Game.hpp"

namespace ViewCurses {

struct ViewModelCurses {
    typedef std::vector<std::shared_ptr<SimpleMove>> MovesTable;

    ViewModelCurses(Board&, PlayerColour);
    ViewModelCurses(Board&, PlayerColour, MovesTable&);

    struct ViewCellCurses {
        enum class ViewCellCursesStatus {
            ACTIVE,
            INACTIVE,
            CURRENT
        };

        ViewCellCurses(Cell, ViewCellCursesStatus = ViewCellCursesStatus::INACTIVE);
        //        ViewCellCurses(Cell, std::vector<std::shared_ptr<SimpleMove>>);

        Cell cell;
        std::vector<std::shared_ptr<SimpleMove>> inMoves;
        ViewCellCursesStatus status;
    };

    std::vector<std::vector<ViewCellCurses>> viewBoard;
    PlayerColour turn;
};

}

#endif
