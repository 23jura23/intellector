#ifndef _VIEW_MODEL_CURSES_HPP
#define _VIEW_MODEL_CURSES_HPP

#include "Board.hpp"
#include "Game.hpp"
#include "ViewModelBase.hpp"

namespace ViewCurses {

struct ViewModelCurses : public ViewModelBase {
    typedef std::vector<Move> MovesTable;

    ViewModelCurses(const Board&, PlayerColour);
    ViewModelCurses(const Board&, PlayerColour, MovesTable&);

    struct ViewCellCurses {
        enum class ViewCellCursesStatus {
            ACTIVE,         // possible move
            INACTIVE,       // nothing special
            CURRENT,        // current pointer position
            SELECTED,       // selected to make move
            PREVIOUS_FROM,  // previous cell of moved figure
            PREVIOUS_TO     // current cell of moved figure
        };

        ViewCellCurses(Cell, ViewCellCursesStatus = ViewCellCursesStatus::INACTIVE);

        Cell cell;
        std::vector<Move> inMoves;
        ViewCellCursesStatus status;
    };

    ViewCellCurses& get(const Position& pos);
    const ViewCellCurses& get(const Position& pos) const;

    const int cols, rows;
    std::vector<std::vector<ViewCellCurses>> viewBoard;
    PlayerColour turn;
};


using CellStatus = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus;
using ViewCellCurses = ViewModelCurses::ViewCellCurses;

}  // namespace ViewCurses

#endif
