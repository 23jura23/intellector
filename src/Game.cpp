//
// Created by vsg on 04.03.2020.
//

#include "Game.hpp"

Game::Game() {
    black_bot_ = BotFactory(GameSettings(0, false, true));
}

void Game::setGameSettings(const GameSettings& settings) {
    if (settings.first_player())
        white_bot_ = BotFactory(settings);
    if (settings.second_player())
        black_bot_ = BotFactory(settings);
}

bool Game::makeMove(const SimpleMove& move) {
    if (!board_[move.from_].figure_.has_value() || board_[move.from_].figure_->colour_ != turn_)
        return false;
    if (!inBoard(move.from_) || !inBoard(move.to_))
        return false;

    if (!move.makeMove(board_))
        return false;

    if (turn_ == PlayerColour::white_) {
        turn_ = PlayerColour::black_;
        (*black_bot_->makeMove(*this)).makeMove(board_);
        turn_ = PlayerColour::white_;
    } else {
        turn_ = PlayerColour::white_;
        (*white_bot_->makeMove(*this)).makeMove(board_);
        turn_ = PlayerColour::black_;
    }
    return true;
}

std::vector<std::shared_ptr<SimpleMove>> Game::allFigureMoves(Position pos) const {
    if (!board_[pos].figure_.has_value() || board_[pos].figure_->colour_ != turn_)
        return {};

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}

std::optional<PlayerColour> Game::getWinner() const {  // может можно получше
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
