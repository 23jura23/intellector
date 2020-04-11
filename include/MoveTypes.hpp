//
// Created by vsg on 06.03.2020.
//

#ifndef _INTELLECTOR_MOVETYPES_HPP
#define _INTELLECTOR_MOVETYPES_HPP

#include <utility>

#include "Board.hpp"
#include "Figure.hpp"
#include "Position.hpp"

class Move {
   public:
    Move(const Position& from_pos,
         const Position& to_pos,
         const Figure& from_figure,
         std::optional<Figure> to_figure_old)
            : from_(from_pos)
            , to_(to_pos)
            , from_figure_old_(from_figure)
            , to_figure_new_(from_figure)
            , from_figure_new_(std::nullopt)
            , to_figure_old_(std::move(to_figure_old)) {
    }

    Move(const Position& from_pos,
         const Position& to_pos,
         const Figure& from_figure,
         std::optional<Figure> to_figure_old,
         const Figure& to_figure_new)
            : from_(from_pos)
            , to_(to_pos)
            , from_figure_old_(from_figure)
            , to_figure_new_(to_figure_new)
            , from_figure_new_(std::nullopt)
            , to_figure_old_(std::move(to_figure_old)) {
    }

    Move(const Position& from_pos,
         const Position& to_pos,
         const Figure& from_figure,
         std::optional<Figure> to_figure_old,
         const Figure& to_figure_new,
         const Figure& from_figure_new)
            : from_(from_pos)
            , to_(to_pos)
            , from_figure_old_(from_figure)
            , to_figure_new_(to_figure_new)
            , from_figure_new_(from_figure_new)
            , to_figure_old_(std::move(to_figure_old)) {
    }

    virtual bool makeMove(Board& board) const;

    Position from_, to_;
    Figure from_figure_old_, to_figure_new_;
    std::optional<Figure> from_figure_new_, to_figure_old_;
};

#endif  //_INTELLECTOR_MOVETYPES_HPP
