//
// Created by vsg on 03.03.2020.
//

#include <Cell.hpp>

CellColour getColour(Position pos) {
    if ((pos.posW() % 2 == 0 && pos.posH() % 3 == 0) ||
        (pos.posW() % 2 == 1 && pos.posH() % 3 == 1))
        return CellColour::BLACK;
    else
        return CellColour::WHITE;
}

Cell::Cell(Position pos, Figure figure)
        : Cell(pos) {
    figure_.emplace(figure);
}

Cell::Cell(Position pos)
        : figure_()
        , colour_(getColour(pos))
        , pos_(pos) {
}
