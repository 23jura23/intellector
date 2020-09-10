//
// Created by vsg on 04.03.2020.
//

#ifndef _INTELLECTOR_CONTROLLER_HPP
#define _INTELLECTOR_CONTROLLER_HPP

#include <future>
#include <thread>

#include "Bot/BotFactory/BotFactory.hpp"
#include "GameSettings.hpp"
#include "Board.hpp"
#include "FigureMoveValidator.hpp"
#include "MoveTypes.hpp"

enum class GameStatus { game_running_, game_over_white_win_, game_over_black_win_ };

class Game {
    // TODO первые 4 байта случайное число + версия?
    // TODO MakeMove синхронный?
   public:
    explicit Game(const GameSettings& settings = GameSettings{4,0,1,0});
    ~Game() = default;
    //    Game(const Game& other) = delete;
    Game(const Game& other)
            : board_{other.board_}
            , turn_{other.turn_}
            , white_bot_{nullptr}
            , black_bot_{nullptr}
            , bot_move_{}
            , is_calculated_{false}
            , settings_{other.settings_}
            , history_of_moves_{other.history_of_moves_}
            , point_of_history_{other.point_of_history_}
            , move_number_{other.move_number_} {
    }

    [[nodiscard]] Game makeCopyForBot() const {
        Game result{settings_};
        result.board_ = board_;
        result.turn_ = turn_;
        result.white_bot_ = nullptr;
        result.black_bot_ = nullptr;
        result.bot_move_ = {};

        result.history_of_moves_ = {};
        result.point_of_history_ = 0;
        result.move_number_ = move_number_;
        return result;
    }

    void setGameSettings(const GameSettings& settings);

    bool loadGame(const std::string& filename);
    void saveGame(const std::string& filename);

    bool makeWhiteBotMove();
    bool makeBlackBotMove();
    bool makeBotMove();
    bool makeMove(const Move& move);

    [[nodiscard]] std::vector<Move> allFigureMoves(Position pos) const;

    [[nodiscard]] const Board& getBoard() const {
        return board_;
    }

    [[nodiscard]] PlayerColour getColourCurrentPlayer() const {
        return turn_;
    }

    [[nodiscard]] const std::vector<Move>& getHistoryOfMoves() const;
    [[nodiscard]] size_t getPointOfHistory() const;
    [[nodiscard]] bool atEndOfHistory() const;

    [[nodiscard]] GameStatus getGameStatus() const;

    [[nodiscard]] GameSettings getGameSettings() const;

    bool cancelMove();

    bool nextMove();
    bool prevMove();

   private:
    Board board_;
    PlayerColour turn_ = PlayerColour::white_;
    std::shared_ptr<Bot> white_bot_ = nullptr, black_bot_ = nullptr;
    std::future<Move> bot_move_ = {};
    bool is_calculated_ = false;
    GameSettings settings_;
    //    int difficulty = 0;

    std::vector<Move> history_of_moves_ = {};
    unsigned int point_of_history_ = 0;
    unsigned int move_number_ = 0;
};

#endif  //_INTELLECTOR_CONTROLLER_HPP
