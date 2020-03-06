//
// Created by vsg on 03.03.2020.
//

#ifndef _INTELLECTOR_FIGUREMOVE_HPP
#define _INTELLECTOR_FIGUREMOVE_HPP

//#include "Board.hpp"

#include "Board.hpp"
#include "Position.hpp"

class FigureMove {
public:
    FigureMove(Board &board, PlayerColour colour, Position pos, FigureType type);

    virtual bool checkMove(Position to_pos) = 0;

    virtual const std::vector<Position> allMoves() = 0;

    static std::unique_ptr<FigureMove> create(Board &board, Figure figure, Position pos);

protected:
    const Board &board_;
    const PlayerColour colour_;
    const Position pos_;
    const FigureType type_;
};

//------------------------------------------------------------------------------------------------
class FigureMoveIntellector : public FigureMove {
public:
    FigureMoveIntellector(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

class FigureMoveDominator : public FigureMove {
public:
    FigureMoveDominator(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

class FigureMoveAggressor : public FigureMove {
public:
    FigureMoveAggressor(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

class FigureMoveDefenssor : public FigureMove {
public:
    FigureMoveDefenssor(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

class FigureMoveLiberator : public FigureMove {
public:
    FigureMoveLiberator(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

class FigureMoveProgressor : public FigureMove {
public:
    FigureMoveProgressor(Board &board, PlayerColour colour, Position pos);

    bool checkMove(Position to_pos) override;

    const std::vector<Position> allMoves() override;
};

#endif //_INTELLECTOR_FIGUREMOVE_HPP
