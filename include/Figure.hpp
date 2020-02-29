//
// Created by vsg on 28.02.2020.
//

#ifndef _MY_FOLDER_FIGURE_HPP
#define _MY_FOLDER_FIGURE_HPP

#include <vector>
#include <optional>
#include <memory>
#include "Types.hpp"
#include "Cell.hpp"

enum class FigureType {
    INTELLECTOR,
    DOMINATOR,
    AGGRESSOR,
    DEFENSSOR,
    LIBERATOR,
    PROGRESSOR,
    NONE
};

enum class PlayerColour {
    black_, white_
};

struct Triple {
    PlayerColour colour_;
    Cell pos_;
    FigureType type_;
    Triple(PlayerColour colour, Cell pos, FigureType type)
            : colour_(colour), pos_(pos), type_(type) {};
};

class Figure {
public:
    Figure(Cell pos, PlayerColour colour, FigureType type = FigureType::NONE)
    : colour_(colour), pos_(pos), type_(type) {}


    virtual bool checkMove(const Board& board_, Cell to_pos_);
//    virtual std::optional<Board> makeMove(const Board& board_, Cell to_pos_);
    virtual std::vector<Cell> allMoves(const Board& board_);

    [[nodiscard]] PlayerColour getColor()  const { return colour_; }
    [[nodiscard]] Cell         getPos()    const { return pos_; }
    [[nodiscard]] FigureType   getType()   const { return type_; }
    [[nodiscard]] Triple       getTriple() const { return Triple(colour_, pos_, type_); }

    static std::unique_ptr<Figure> create(Triple);
private:
    const PlayerColour colour_;
    Cell pos_;
    const FigureType type_;
};

//------------------------------------------------------------------------------------------------
class FigureIntellector : public Figure {
public:
    FigureIntellector(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::INTELLECTOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
//    std::optional<Board> makeMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};

class FigureDominator : public Figure {
public:
    FigureDominator(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::DOMINATOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};

class FigureAggressor : public Figure {
public:
    FigureAggressor(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::AGGRESSOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};

class FigureDefenssor : public Figure {
public:
    FigureDefenssor(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::DEFENSSOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};

class FigureLiberator : public Figure {
public:
    FigureLiberator(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::LIBERATOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};

class FigureProgressor : public Figure {
public:
    FigureProgressor(Cell pos, PlayerColour colour)
    : Figure(pos, colour, FigureType::PROGRESSOR) {};


    bool checkMove(const Board& board_, Cell to_pos_) override;
    std::vector<Cell> allMoves(const Board& board_) override;
};


#endif //MY_FOLDER_FIGURE_HPP
