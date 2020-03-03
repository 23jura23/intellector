//
// Created by vsg on 03.03.2020.
//

#include <Cell.hpp>

Cell::Cell(Triple new_figure)
        : figure_(Figure::create(new_figure)) {
    Position pos = new_figure.pos_;
    if ((pos.posW() % 2 == 0 && pos.posH() % 3 == 0) || (pos.posW() % 2 == 1 && pos.posH() % 3 == 1))
        colour_ = CellColour::BLACK;
    else
        colour_ = CellColour::WHITE;
}

Cell::Cell(Position pos)
        : figure_(nullptr) {
    if ((pos.posW() % 2 == 0 && pos.posH() % 3 == 0) || (pos.posW() % 2 == 1 && pos.posH() % 3 == 1))
        colour_ = CellColour::BLACK;
    else
        colour_ = CellColour::WHITE;
}
