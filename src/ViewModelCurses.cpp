#include "ViewModelCurses.hpp"

using namespace ViewCurses;

#include <iostream>
using namespace std;

ViewModelCurses::ViewModelCurses(const Board& board, PlayerColour turn)
    : turn { turn }
{
    freopen("error.txt","a",stderr);
    viewBoard.resize(board.cols_);
    for (size_t i = 0; i < board.data_.size(); ++i)
        for (size_t j = 0; j < board.data_[i].size(); ++j)
            viewBoard[i].emplace_back(board.data_[i][j]);
}

ViewModelCurses::ViewModelCurses(const Board& board_, PlayerColour turn_, MovesTable& movesTable)
    : ViewModelCurses(board_, turn_)
{
    for (size_t i = 0; i < movesTable.size(); ++i) {
        int x = movesTable[i]->to_.posW();
        int y = movesTable[i]->to_.posH();
        viewBoard[x][y].inMoves.push_back(movesTable[i]);
        viewBoard[x][y].status = ViewCellCurses::ViewCellCursesStatus::ACTIVE;
        cerr << x << " and " << y << " are active!" << endl;
    }
}

ViewModelCurses::ViewCellCurses::ViewCellCurses(Cell cell, ViewCellCursesStatus status)
    : cell { cell }
    , status { status}
{
}

//ViewModelCurses::ViewCellCurses::ViewCellCurses(Cell cell, std::vector<std::shared_ptr<SimpleMove>> inMoves)
//    : cell { cell }
//    , inMoves { inMoves }
//{
//}
