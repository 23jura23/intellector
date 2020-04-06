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

GameStatus Game::getGameStatus() const {  // может можно получше
    bool is_white_intellector = false;
    bool is_black_intellector = false;
    bool white_can_move = false;
    bool black_can_move = false;

    for (const auto& row : board_.data_)
        for (const auto& cell : row) {
            if (!cell.figure_.has_value())
                continue;
            if (cell.figure_->type_ == FigureType::INTELLECTOR)
                cell.figure_->colour_ == PlayerColour::white_ ? is_white_intellector = true
                                                              : is_black_intellector = true;

            std::shared_ptr<FigureMoveValidator> figure =
                FigureMoveValidator::create(board_, board_[cell.pos_].figure_.value(), cell.pos_);

            if ((cell.figure_->colour_ == PlayerColour::white_ && white_can_move) ||
                (cell.figure_->colour_ == PlayerColour::black_ && black_can_move))
                continue;

            cell.figure_->colour_ == PlayerColour::white_
                ? white_can_move = !figure->allMoves().empty()
                : black_can_move = !figure->allMoves().empty();
        }

    if (is_black_intellector && is_white_intellector && black_can_move && white_can_move)
        return GameStatus::game_running_;

    if (is_black_intellector && black_can_move)
        return GameStatus::game_over_black_win_;
    if (is_white_intellector && white_can_move)
        return GameStatus::game_over_white_win_;
    return GameStatus::game_over_;
}
