//
// Created by vsg on 06.03.2020.
//

#include "MoveTypes.hpp"
#include "FigureMoveValidator.hpp"

bool SimpleMove::makeMove(Board& board) {
    std::shared_ptr<FigureMoveValidator> figure = FigureMoveValidator::create(board,
                                                                              board[from_].figure_.value(),
                                                                              from_);

    if (!figure->checkMove(to_))
        return false;

    board[to_].figure_.emplace(board[from_].figure_.value());
    board[from_].figure_ = std::nullopt;
    return true;
}

bool SwapMove::makeMove(Board& board) {
    if (board[from_].figure_->type_ != FigureType::INTELLECTOR ||
        !board[to_].figure_.has_value())
        return false;

    std::shared_ptr<FigureMoveValidator> figure = FigureMoveValidator::create(board,
                                                                              board[from_].figure_.value(),
                                                                              from_);

    if (!figure->checkMove(to_))
        return false;

    board[to_].figure_.emplace(board[from_].figure_.value());
    board[from_].figure_.emplace(figure->getFigure());
    return true;
}

bool TransformMove::makeMove(Board& board) {
    if (board[from_].figure_->type_ != FigureType::PROGRESSOR ||
        !((to_.posH() == 0 && to_.posW() % 2 == 1) || to_.posH() == Board::cols_ - 1))
        return false;

    std::shared_ptr<FigureMoveValidator> figure = FigureMoveValidator::create(board,
                                                                              board[from_].figure_.value(),
                                                                              from_);

    if (!figure->checkMove(to_))
        return false;

    board[to_].figure_.emplace(board[from_].figure_.value());
    board[from_].figure_.emplace(board[from_].figure_->colour_, figure_type_);
    return true;
}
