//
// Created by vsg on 04.03.2020.
//

#ifndef _INTELLECTOR_CONTROLLER_HPP
#define _INTELLECTOR_CONTROLLER_HPP

#include "Board.hpp"
#include "FigureMoveValidator.hpp"
#include "MoveTypes.hpp"

class Game {
public:
    bool makeMove(std::unique_ptr<SwapMove> move);
    bool makeMove(std::unique_ptr<TransformMove> move);
    bool makeMove(std::unique_ptr<SimpleMove> move);

    std::vector<std::shared_ptr<SimpleMove>> allFigureMoves(Position pos, PlayerColour turn);

    [[nodiscard]] const Board& getBoard() const { return board_; }
    [[nodiscard]] const PlayerColour getColourCurrentPlayer() const { return turn_; }
private:
    Board board_;
    PlayerColour turn_;
};

#endif //_INTELLECTOR_CONTROLLER_HPP
