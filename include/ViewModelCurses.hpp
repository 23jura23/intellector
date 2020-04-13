#ifndef _VIEW_MODEL_CURSES_HPP
#define _VIEW_MODEL_CURSES_HPP

#include "Board.hpp"
#include "Game.hpp"
#include "ViewModelBase.hpp"

namespace ViewCurses {

struct ViewModelCurses : public ViewModelBase {
    typedef std::vector<std::shared_ptr<Move>> MovesTable;

    ViewModelCurses(const Board&, PlayerColour);
    ViewModelCurses(const Board&, PlayerColour, MovesTable&);

    struct ViewCellCurses {
        enum class ViewCellCursesStatus {
            ACTIVE,    // possible move
            INACTIVE,  // nothing special
            CURRENT,   // current pointer position
            SELECTED,  // selected to make move
            PREVIOUS   // previous cell of moved figure
        };

        ViewCellCurses(Cell, ViewCellCursesStatus = ViewCellCursesStatus::INACTIVE);

        Cell cell;
        std::vector<std::shared_ptr<Move>> inMoves;
        ViewCellCursesStatus status;
    };
    ViewCellCurses& operator[](const Position& pos);
    const ViewCellCurses& operator[](const Position& pos) const;

    const int cols, rows;
    std::vector<std::vector<ViewCellCurses>> viewBoard;
    PlayerColour turn;
};

}  // namespace ViewCurses

#endif
