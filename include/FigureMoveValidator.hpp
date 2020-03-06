//
// Created by vsg on 03.03.2020.
//

#ifndef _INTELLECTOR_FIGUREMOVEVALIDATOR_HPP
#define _INTELLECTOR_FIGUREMOVEVALIDATOR_HPP

#include "Board.hpp"
#include "Position.hpp"
#include "MoveTypes.hpp"

class FigureMoveValidator {
public:
    FigureMoveValidator(Board& board, PlayerColour colour, Position pos, FigureType type);

    virtual bool checkMove(Position to_pos) = 0;

    virtual std::vector<std::shared_ptr<SimpleMove>> allMoves() = 0;

    static std::shared_ptr<FigureMoveValidator> create(Board& board, Figure figure, Position pos);

protected:
    const Board& board_;
    const Figure figure_;
    const Position pos_;
};

class IntellectorMoveValidator : public FigureMoveValidator {
public:
    IntellectorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

class DominatorMoveValidator : public FigureMoveValidator {
public:
    DominatorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

class AggressorMoveValidator : public FigureMoveValidator {
public:
    AggressorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

class DefenssorMoveValidator : public FigureMoveValidator {
public:
    DefenssorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

class LiberatorMoveValidator : public FigureMoveValidator {
public:
    LiberatorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

class ProgressorMoveValidator : public FigureMoveValidator {
public:
    ProgressorMoveValidator(Board& board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    std::vector<std::shared_ptr<SimpleMove>> allMoves() override;
};

#endif //_INTELLECTOR_FIGUREMOVEVALIDATOR_HPP
