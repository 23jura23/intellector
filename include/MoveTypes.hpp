//
// Created by vsg on 06.03.2020.
//

#ifndef _INTELLECTOR_MOVETYPES_HPP
#define _INTELLECTOR_MOVETYPES_HPP

#include "Board.hpp"
#include "Figure.hpp"
#include "Position.hpp"

class SimpleMove {
   public:
    SimpleMove(const Position& from_pos, const Position& to_pos)
        : from_(from_pos)
        , to_(to_pos) {
    }

    virtual bool makeMove(Board& board) const;

    Position from_, to_;
};

class SwapMove : public SimpleMove {
   public:
    SwapMove(const Position& from_pos, const Position& to_pos)
        : SimpleMove(from_pos, to_pos) {
    }

    bool makeMove(Board& board) const override;
};

class TransformMove : public SimpleMove {
   public:
    TransformMove(const Position& from_pos, const Position& to_pos, const FigureType figure_type)
        : SimpleMove(from_pos, to_pos)
        , figure_type_(figure_type) {
    }

    bool makeMove(Board& board) const override;

    FigureType figure_type_;
};

#endif  //_INTELLECTOR_MOVETYPES_HPP
