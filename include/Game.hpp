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
    // TODO просить бота делать ходы
    // TODO конец игры?
    // TODO сделать конструктор для ботов

    bool makeMove(const SimpleMove& move);

    [[nodiscard]] std::vector<std::shared_ptr<SimpleMove>> allFigureMoves(Position pos, PlayerColour turn) const;

    [[nodiscard]] const Board& getBoard() const { return board_; }

    [[nodiscard]] PlayerColour getColourCurrentPlayer() const { return turn_; }

    [[nodiscard]] std::optional<PlayerColour> getWinner() const;

private:
    Board board_;
    PlayerColour turn_ = PlayerColour::white_;
};

#endif //_INTELLECTOR_CONTROLLER_HPP
