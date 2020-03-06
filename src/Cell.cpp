//
// Created by vsg on 03.03.2020.
//

#include <Cell.hpp>

//Cell::Cell(PlayerColour colour, Position pos, FigureType type)
//    : figure_(Figure(colour, type)), colour_(Cell(pos).colour_) {}

Cell::Cell(Figure figure, Position pos)
        : figure_(figure), colour_(Cell(pos).colour_), pos_(pos) {}

Cell::Cell(Position pos)
        : figure_(), pos_(pos) {
    if ((pos.posW() % 2 == 0 && pos.posH() % 3 == 0) || (pos.posW() % 2 == 1 && pos.posH() % 3 == 1))
        colour_ = CellColour::BLACK;
    else
        colour_ = CellColour::WHITE;
}

Cell& Cell::operator=(const Cell& other) {
    if (this == &other)
        return *this;
    if (other.figure_.has_value())
        figure_.emplace(other.figure_.value());
    else
        figure_.reset();
    colour_ = other.colour_;
    pos_ = other.pos_;
    return *this;
}