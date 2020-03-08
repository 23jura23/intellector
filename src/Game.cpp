//
// Created by vsg on 04.03.2020.
//

#include "Game.hpp"

bool Game::makeMove(std::unique_ptr<SwapMove> move) {
    Position from_pos = move->from_, to_pos = move->to_;

    board_[to_pos] = Cell(Figure(turn_, FigureType::INTELLECTOR), to_pos);
    board_[from_pos] = Cell(Figure(turn_, FigureType::DEFENSSOR), from_pos);
    return true;
}

bool Game::makeMove(std::unique_ptr<TransformMove> move) {
    Position from_pos = move->from_, to_pos = move->to_;

    board_[to_pos] = Cell(Figure(turn_, move->figure_type_), to_pos);
    board_[from_pos] = Cell(from_pos);
    return true;
}

bool Game::makeMove(std::unique_ptr<SimpleMove> move) {
    if (move == nullptr)
        return false;

    Position from_pos = move->from_, to_pos = move->to_;

    board_[to_pos] = Cell(move->figure_, to_pos);
    board_[from_pos] = Cell(from_pos);
    if (turn_ == PlayerColour::white_)
        turn_ = PlayerColour::black_;
    else
        turn_ = PlayerColour::white_;
    return true;
}

std::vector<std::shared_ptr<SimpleMove>> Game::allFigureMoves(Position pos, PlayerColour turn) {
    if (!board_[pos].figure_.has_value() ||
        board_[pos].figure_->colour_ != turn)
        return {};

    std::shared_ptr<FigureMoveValidator> figure = FigureMoveValidator::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}
