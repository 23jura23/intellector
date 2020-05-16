//
// Created by vsg on 04.03.2020.
//

#include "Game.hpp"

Game::Game() {
    black_bot_ = BotFactory(GameSettings(2, false, true));
}

void Game::setGameSettings(const GameSettings& settings) {
    if (settings.first_player())
        white_bot_ = BotFactory(settings);
    if (settings.second_player())
        black_bot_ = BotFactory(settings);
}

bool Game::makeMove(const Move& move) {
    if (!board_[move.from_].figure_.has_value() || board_[move.from_].figure_->colour_ != turn_)
        return false;
    if (!inBoard(move.from_) || !inBoard(move.to_))
        return false;

    if (!move.makeMove(board_))
        return false;

    history_of_moves_.push_back(move);
    ++point_of_history_;

    if (turn_ == PlayerColour::white_) {
        turn_ = PlayerColour::black_;
        if (black_bot_) {
            Move bot_move = black_bot_->makeMove(*this);
            bot_move.makeMove(board_);
            turn_ = PlayerColour::white_;

            history_of_moves_.push_back(bot_move);
            ++point_of_history_;
        }
    } else {
        turn_ = PlayerColour::white_;
        if (white_bot_) {
            Move bot_move = white_bot_->makeMove(*this);
            bot_move.makeMove(board_);
            turn_ = PlayerColour::black_;

            history_of_moves_.push_back(bot_move);
            ++point_of_history_;
        }
    }
    return true;
}

std::vector<Move> Game::allFigureMoves(Position pos) const {
    if (!board_[pos].figure_.has_value() || board_[pos].figure_->colour_ != turn_)
        return {};

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}

const std::vector<Move>& Game::getHistoryOfMoves() const {
    return history_of_moves_;
}

size_t Game::getPointOfHistory() const {
    return point_of_history_;
}

GameStatus Game::getGameStatus() const {  // может можно получше
    bool is_white_intellector = false;
    bool is_black_intellector = false;
    bool player_can_move = false;

    for (const auto& row : board_.data_)
        for (const auto& cell : row) {
            if (!cell.figure_.has_value())
                continue;
            if (cell.figure_->type_ == FigureType::INTELLECTOR) {
                if (cell.figure_->colour_ == PlayerColour::white_)
                    is_white_intellector = true;
                else
                    is_black_intellector = true;
            }

            if (cell.figure_->colour_ != turn_ || player_can_move)
                continue;

            std::shared_ptr<FigureMoveValidator> figure =
                FigureMoveValidator::create(board_, board_[cell.pos_].figure_.value(), cell.pos_);

            player_can_move = !figure->allMoves().empty();
        }

    if (is_black_intellector && is_white_intellector && player_can_move)
        return GameStatus::game_running_;

    if (!is_black_intellector)
        return GameStatus::game_over_white_win_;
    if (!is_white_intellector)
        return GameStatus::game_over_black_win_;

    return turn_ == PlayerColour::black_ ? GameStatus::game_over_white_win_
                                         : GameStatus::game_over_black_win_;
}

bool Game::cancelMove() {
    if (point_of_history_ != history_of_moves_.size() || point_of_history_ == 0)
        return false;

    --point_of_history_;
    turn_ = other_colour(turn_);

    if (history_of_moves_[point_of_history_].cancelMove(board_)) {
        history_of_moves_.pop_back();
        return true;
    }
    turn_ = other_colour(turn_);
    ++point_of_history_;
    return false;
}

bool Game::nextMove() {
    if (point_of_history_ == history_of_moves_.size())
        return false;

    if (!history_of_moves_[point_of_history_].makeMove(board_))
        return false;

    turn_ = other_colour(turn_);
    ++point_of_history_;
    return true;
}

bool Game::prevMove() {
    if (point_of_history_ == 0)
        return false;

    --point_of_history_;
    turn_ = other_colour(turn_);

    if (history_of_moves_[point_of_history_].cancelMove(board_)) {
        return true;
    }
    turn_ = other_colour(turn_);
    ++point_of_history_;
    return false;
}
