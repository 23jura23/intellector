//
// Created by vsg on 06.03.2020.
//

#ifndef _INTELLECTOR_MOVETYPES_HPP
#define _INTELLECTOR_MOVETYPES_HPP

#include "Position.hpp"
#include "Figure.hpp"
#include "Board.hpp"

class SimpleMove {
public:
    SimpleMove(const Position& from_pos, const Position& to_pos, const Figure& figure)
            : from_(from_pos), to_(to_pos)
            , figure_(figure) {}

    Position from_, to_;
    Figure figure_;

//    static std::shared_ptr<SimpleMove> create(const Cell& from_cell, const Cell& to_cell, PlayerColour turn);
};

class SwapMove : public SimpleMove {
public:
    SwapMove(const Position& from_pos, const Position& to_pos, const Figure& figure)
            : SimpleMove(from_pos, to_pos, figure) {}
};


class TransformMove : public SimpleMove {
public:
    TransformMove(const Position& from_pos, const Position& to_pos, const Figure& figure, const FigureType figure_type)
            : SimpleMove(from_pos, to_pos, figure), figure_type_(figure_type) {}

    FigureType figure_type_;
};

#endif //_INTELLECTOR_MOVETYPES_HPP
