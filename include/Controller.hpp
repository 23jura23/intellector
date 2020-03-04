//
// Created by vsg on 04.03.2020.
//

#ifndef _INTELLECTOR_CONTROLLER_HPP
#define _INTELLECTOR_CONTROLLER_HPP

#include "Board.hpp"
#include "FigureMove.hpp"

class Controller {
public:

    bool makeMove(Position of_pos, Position to_pos, PlayerColour turn);
    std::vector<Position> allFigureMoves(Position pos, PlayerColour turn);

    [[nodiscard]] const Board& getBoard() const { return board_; }
private:
    Board board_;
    PlayerColour turn_;
};

#endif //_INTELLECTOR_CONTROLLER_HPP
