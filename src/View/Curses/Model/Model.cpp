#include "View/Curses/Model/Model.hpp"

using namespace viewCurses;

#include <iostream>
using namespace std;

ViewModelCurses::ViewModelCurses(const Game& game)
        : cols_{game.getBoard().cols_}
        , rows_{game.getBoard().rows_}
        , turn_{game.getColourCurrentPlayer()}
        , history_of_moves_{game.getHistoryOfMoves()}
        , point_of_history_{game.getPointOfHistory()}
        , settings{game.getGameSettings()}
        , playerTurn{(turn_ == PlayerColour::white_ && !settings.first_player()) || (turn_ == PlayerColour::black_ && !settings.second_player())}
            {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);
    // avoiding warning. May be harmful, but later there must be a well-done logging.

    const auto& board = game.getBoard();
    viewBoard_.resize(board.cols_);
    for (size_t i = 0; i < board.data_.size(); ++i)
        for (size_t j = 0; j < board.data_[i].size(); ++j)
            viewBoard_[i].emplace_back(board.data_[i][j]);
}

ViewModelCurses::ViewModelCurses(const Game& game, MovesTable& movesTable)
        : ViewModelCurses{game} {
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

