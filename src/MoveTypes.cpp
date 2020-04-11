//
// Created by vsg on 06.03.2020.
//

#include "MoveTypes.hpp"

#include "FigureMoveValidator.hpp"

bool Move::makeMove(Board& board) const {
    if (!board[from_].figure_.has_value() || board[from_].figure_.value() != from_figure_old_ ||
        board[to_].figure_ != to_figure_old_)
        return false;

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board, from_figure_old_, from_);

    if (!figure->checkMove(to_))
        return false;

    board[to_].figure_.emplace(board[from_].figure_.value());
    std::optional<Figure> tmp(from_figure_new_);
    std::swap(board[from_].figure_, tmp);
    return true;
}
