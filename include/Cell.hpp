//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_CELL_HPP
#define _PROJECT_CELL_HPP

#include <memory>
#include "Figure.hpp"
#include "Position.hpp"

enum class CellStatus { // А может надо в View реализовать
    NOT_MARKED,
    CAN_MOVE,
    CAN_ATTACK,
    CURRENT,
    LAST_MOVE,
};

enum class CellColour {
    WHITE,
    BLACK
};

class Cell {
public:
//    Cell(PlayerColour colour, Position pos, FigureType type);
    Cell(Figure figure, Position pos);
    explicit Cell(Position pos);
    Cell& operator= (const Cell&);


    std::optional<Figure> figure_;
    CellColour colour_;
    CellStatus status_ = CellStatus::NOT_MARKED;

};

#endif //_PROJECT_CELL_HPP
