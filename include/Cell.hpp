//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_CELL_HPP
#define _PROJECT_CELL_HPP

#include <memory>
#include "Figure.hpp"

enum class CellStatus {
    MARKED,
    NOT_MARKED,
    MARKED_TO_ATTACK,
};

enum class CellColour {
    WHITE,
    BLACK
};

class Cell {
public:
    explicit Cell(Triple new_figure);

    explicit Cell(Position pos);

    std::unique_ptr<Figure> figure_ = nullptr;

    CellColour colour_;
    CellStatus status_ = CellStatus::NOT_MARKED;

};

#endif //_PROJECT_CELL_HPP
