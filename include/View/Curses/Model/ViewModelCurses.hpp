#ifndef _VIEW_MODEL_CURSES_HPP
#define _VIEW_MODEL_CURSES_HPP

#include <vector>

#include "Model/ModelImpl/Board.hpp"
#include "Model/ModelImpl/Game.hpp"
#include "View/Base/Model/ViewModelBase.hpp"

namespace viewCurses {

struct ViewModelCurses : public ViewModelBase {
    typedef std::vector<Move> MovesTable;

    ViewModelCurses(const Game&);
    ViewModelCurses(const Game&, MovesTable&);

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

        Cell cell_;
        std::vector<Move> inMoves_;
        ViewCellCursesStatus status_;
    };

    ViewCellCurses& get(const Position& pos);
    const ViewCellCurses& get(const Position& pos) const;

    const int cols_, rows_;
    std::vector<std::vector<ViewCellCurses>> viewBoard_;
    PlayerColour turn_;
    std::vector<Move> history_of_moves_;
    size_t point_of_history_;
    GameSettings settings;
    bool playerTurn;
};

using CellStatus = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus;
using ViewCellCurses = ViewModelCurses::ViewCellCurses;

}  // namespace viewCurses

#endif
