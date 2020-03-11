//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_CELL_HPP
#define _PROJECT_CELL_HPP

#include <memory>
#include "Figure.hpp"
#include "Position.hpp"

enum class CellColour {
    WHITE,
    BLACK
};

class Cell {
public:
    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = delete;

    Cell(Position pos, Figure figure);
    explicit Cell(Position pos);

    std::optional<Figure> figure_;
    const CellColour colour_;
    const Position pos_;
};

#endif //_PROJECT_CELL_HPP
