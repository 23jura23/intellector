//
// Created by vsg on 28.02.2020.
//

#ifndef _MY_FOLDER_FIGURE_HPP
#define _MY_FOLDER_FIGURE_HPP

#include <vector>
#include <optional>
#include <memory>
#include "Types.hpp"
#include "Position.hpp"
//#include "Board.hpp"

enum class FigureType {
    INTELLECTOR,
    DOMINATOR,
    AGGRESSOR,
    DEFENSSOR,
    LIBERATOR,
    PROGRESSOR
};

enum class PlayerColour {
    black_, white_
};

struct Triple {
    PlayerColour colour_;
    Position pos_;
    FigureType type_;

    Triple(PlayerColour colour, Position pos, FigureType type);
};

class Figure {
public:
    Figure(PlayerColour colour, Position pos, FigureType type);

    virtual bool checkMove(const Board &board, Position to_pos) = 0;

    virtual std::vector<Position> allMoves(const Board &board) = 0;

    [[nodiscard]] PlayerColour getColor() const;
    [[nodiscard]] Position getPos() const;
    [[nodiscard]] FigureType getType() const;
    [[nodiscard]] Triple getTriple() const;

    static std::unique_ptr<Figure> create(Triple);

protected:
    Position pos_;
    const PlayerColour colour_;
    const FigureType type_;
};

//------------------------------------------------------------------------------------------------
class FigureIntellector : public Figure {
public:
    FigureIntellector(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};

class FigureDominator : public Figure {
public:
    FigureDominator(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};

class FigureAggressor : public Figure {
public:
    FigureAggressor(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};

class FigureDefenssor : public Figure {
public:
    FigureDefenssor(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};

class FigureLiberator : public Figure {
public:
    FigureLiberator(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};

class FigureProgressor : public Figure {
public:
    FigureProgressor(PlayerColour colour, Position pos);

    bool checkMove(const Board &board, Position to_pos) override;

    std::vector<Position> allMoves(const Board &board) override;
};


#endif //MY_FOLDER_FIGURE_HPP
