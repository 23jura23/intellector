//
// Created by vsg on 06.03.2020.
//

#include "Model/ModelImpl/MoveTypes.hpp"

#include "Model/ModelImpl/FigureMoveValidator.hpp"

bool Move::makeMove(Board& board) const {
    if (!board[from_].figure_.has_value() || board[from_].figure_.value() != from_figure_old_ ||
        board[to_].figure_ != to_figure_old_)
        return false;

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board, from_figure_old_, from_, point_of_history_);

    if (!figure->checkMove(to_))
        return false;

    board[to_].figure_.emplace(to_figure_new_);
    std::optional<Figure> tmp(from_figure_new_);
    std::swap(board[from_].figure_, tmp);
    return true;
}

bool Move::cancelMove(Board& board) const {
    if (!board[to_].figure_.has_value() || board[to_].figure_.value() != to_figure_new_ ||
        board[from_].figure_ != from_figure_new_)
        return false;

    board[from_].figure_.emplace(from_figure_old_);
    std::optional<Figure> tmp(to_figure_old_);
    std::swap(board[to_].figure_, tmp);

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board, from_figure_old_, from_, point_of_history_);

    if (figure->checkMove(to_))
        return true;

    board[to_].figure_.emplace(to_figure_new_);
    tmp = from_figure_new_;
    std::swap(board[from_].figure_, tmp);
    return false;
}
