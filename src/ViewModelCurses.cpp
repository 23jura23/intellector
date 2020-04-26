#include "ViewModelCurses.hpp"

using namespace ViewCurses;
using ViewCellCurses = ViewModelCurses::ViewCellCurses;

#include <iostream>
using namespace std;

ViewModelCurses::ViewModelCurses(const Board& board, PlayerColour turn)
        : cols_{board.cols_}
        , rows_{board.rows_}
        , turn_{turn} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);
    // avoiding warning. May be harmful, but later there must be a well-done logging.

    viewBoard_.resize(board.cols_);
    for (size_t i = 0; i < board.data_.size(); ++i)
        for (size_t j = 0; j < board.data_[i].size(); ++j)
            viewBoard_[i].emplace_back(board.data_[i][j]);
}

ViewModelCurses::ViewModelCurses(const Board& board, PlayerColour turn, MovesTable& movesTable)
        : ViewModelCurses(board, turn) {
    //TODO(23jura23) receive previous position and highlight its status_
    for (size_t i = 0; i < movesTable.size(); ++i) {
        int x = movesTable[i].to_.posW();
        int y = movesTable[i].to_.posH();
        viewBoard_[x][y].inMoves_.push_back(movesTable[i]);
        viewBoard_[x][y].status_ = ViewCellCurses::ViewCellCursesStatus::ACTIVE;
        cerr << x << " and " << y << " are active!" << endl;
    }
}

ViewModelCurses::ViewCellCurses::ViewCellCurses(Cell cell, ViewCellCursesStatus status)
        : cell_{cell}
        , status_{status} {
}

ViewCellCurses& ViewModelCurses::get(const Position& pos) {
    return viewBoard_[pos.posW()][pos.posH()];
}
const ViewCellCurses& ViewModelCurses::get(const Position& pos) const {
    return viewBoard_[pos.posW()][pos.posH()];
}

// ViewModelCurses::ViewCellCurses::ViewCellCurses(Cell cell_,
// std::vector<std::shared_ptr<SimpleMove>> inMoves_)
//    : cell_ { cell_ }
//    , inMoves_ { inMoves_ }
//{
//}
