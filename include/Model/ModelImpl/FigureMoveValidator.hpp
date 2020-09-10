//
// Created by vsg on 03.03.2020.
//

#ifndef _INTELLECTOR_FIGUREMOVEVALIDATOR_HPP
#define _INTELLECTOR_FIGUREMOVEVALIDATOR_HPP

#include "Board.hpp"
#include "MoveTypes.hpp"
#include "Position.hpp"

class FigureMoveValidator {
   public:
    FigureMoveValidator(const Board& board,
                        PlayerColour colour,
                        Position pos,
                        FigureType type,
                        std::size_t move_number);
    virtual ~FigureMoveValidator() = default;

    [[nodiscard]] Figure getFigure() const {
        return figure_;
    }

    virtual bool checkMove(Position to_pos) = 0;

    virtual std::vector<Move> allMoves() = 0;

    static std::shared_ptr<FigureMoveValidator> create(const Board& board,
                                                       Figure figure,
                                                       Position pos,
                                                       std::size_t move_number);

   protected:
    const Board& board_;
    const Figure figure_;
    const Position pos_;
    const std::size_t move_number_;
};

class IntellectorMoveValidator : public FigureMoveValidator {
   public:
    IntellectorMoveValidator(const Board& board,
                             PlayerColour colour,
                             Position pos,
                             std::size_t move_number);
    ~IntellectorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

class DominatorMoveValidator : public FigureMoveValidator {
   public:
    DominatorMoveValidator(const Board& board,
                           PlayerColour colour,
                           Position pos,
                           std::size_t move_number);
    ~DominatorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

class AggressorMoveValidator : public FigureMoveValidator {
   public:
    AggressorMoveValidator(const Board& board,
                           PlayerColour colour,
                           Position pos,
                           std::size_t move_number);
    ~AggressorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

class DefenssorMoveValidator : public FigureMoveValidator {
   public:
    DefenssorMoveValidator(const Board& board,
                           PlayerColour colour,
                           Position pos,
                           std::size_t move_number);
    ~DefenssorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

class LiberatorMoveValidator : public FigureMoveValidator {
   public:
    LiberatorMoveValidator(const Board& board,
                           PlayerColour colour,
                           Position pos,
                           std::size_t move_number);
    ~LiberatorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

class ProgressorMoveValidator : public FigureMoveValidator {
   public:
    ProgressorMoveValidator(const Board& board,
                            PlayerColour colour,
                            Position pos,
                            std::size_t move_number);
    ~ProgressorMoveValidator() override = default;

    bool checkMove(Position to_pos) override;

    std::vector<Move> allMoves() override;
};

#endif  //_INTELLECTOR_FIGUREMOVEVALIDATOR_HPP
