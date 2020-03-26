//
// Created by vsg on 04.03.2020.
//

#include "Game.hpp"

bool Game::makeMove(const SimpleMove& move) {
    if (!board_[move.from_].figure_.has_value() || board_[move.from_].figure_->colour_ != turn_)
        return false;

    if (!move.makeMove(board_))
        return false;

    if (turn_ == PlayerColour::white_)
        turn_ = PlayerColour::black_;
    else
        turn_ = PlayerColour::white_;
    return true;
}

std::vector<std::shared_ptr<SimpleMove>> Game::allFigureMoves(Position pos, PlayerColour turn) const {
    if (!board_[pos].figure_.has_value() ||
        board_[pos].figure_->colour_ != turn)
        return {};

    std::shared_ptr<FigureMoveValidator> figure = FigureMoveValidator::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}

std::optional<PlayerColour> Game::getWinner() const { // может можно получше
    bool is_white = false;
    bool is_black = false;
    for (const auto& row : board_.data_)
        for (const auto& cell : row)
            if (cell.figure_.has_value() && cell.figure_->type_ == FigureType::INTELLECTOR)
                cell.figure_->colour_ == PlayerColour::white_ ? is_white = true : is_black = true;
    if (is_black && is_white)
        return {};
    if (is_black)
        return PlayerColour::black_;
    if (is_white)
        return PlayerColour::white_;
    return {};
}
