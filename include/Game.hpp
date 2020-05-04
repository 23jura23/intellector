//
// Created by vsg on 04.03.2020.
//

#ifndef _INTELLECTOR_CONTROLLER_HPP
#define _INTELLECTOR_CONTROLLER_HPP

#include "Board.hpp"
#include "BotFactory.hpp"
#include "FigureMoveValidator.hpp"
#include "MoveTypes.hpp"

enum class GameStatus { game_running_, game_over_white_win_, game_over_black_win_ };

class Game {
    // TODO первые 4 байта случайное число + в конце проверить размер ???crc32???
    // TODO MakeMove синхронный?
    // TODO MakeCopyForBot
   public:
    Game();
    Game(const Game& other)
            : board_(other.board_)
            , turn_(other.turn_)
            , white_bot_(nullptr)
            , black_bot_(nullptr) {
    }

    explicit Game(const GameSettings& settings) {
        if (settings.first_player())
            white_bot_ = BotFactory(settings);
        if (settings.second_player())
            black_bot_ = BotFactory(settings);
    }

    [[nodiscard]] Game makeCopyForBot() const {
        Game result;
        result.board_ = board_;
        result.turn_ = turn_;
        result.white_bot_ = nullptr;
        result.black_bot_ = nullptr;

        result.history_of_moves_ = {};
        result.point_of_history_ = 0;
        return result;
    }

    void setGameSettings(const GameSettings& settings);

    bool makeMove(const Move& move);

    [[nodiscard]] std::vector<Move> allFigureMoves(Position pos) const;

    [[nodiscard]] const Board& getBoard() const {
        return board_;
    }

    [[nodiscard]] PlayerColour getColourCurrentPlayer() const {
        return turn_;
    }

    const std::vector<Move>& getHistoryOfMoves() const;

    [[nodiscard]] GameStatus getGameStatus() const;

    bool cancelMove();

    bool nextMove();
    bool prevMove();

   private:
    Board board_;
    PlayerColour turn_ = PlayerColour::white_;
    std::shared_ptr<Bot> white_bot_ = nullptr, black_bot_ = nullptr;

    std::vector<Move> history_of_moves_ = {};
    size_t point_of_history_ = 0;
};

#endif  //_INTELLECTOR_CONTROLLER_HPP
