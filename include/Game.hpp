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
    // TODO первые 4 байта случайное число + версия?
    // TODO MakeMove синхронный?
   public:
    explicit Game(const GameSettings& settings = GameSettings(4,0,0,1));
    Game(const Game& other) = default;

//    explicit Game(const GameSettings& settings) {
//        if (settings.first_player())
//            white_bot_ = BotFactory(settings);
//        if (settings.second_player())
//            black_bot_ = BotFactory(settings);
//        difficulty = settings.difficulty();
//    }

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

    bool loadGame(const std::string& filename);

    void saveGame(const std::string& filename);

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

    [[nodiscard]] GameStatus getGameStatus() const;

    [[nodiscard]] GameSettings getGameSettings() const;

    bool cancelMove();

    bool nextMove();
    bool prevMove();

   private:
    Board board_;
    PlayerColour turn_;// = PlayerColour::white_;
    std::shared_ptr<Bot> white_bot_ = nullptr, black_bot_ = nullptr;
    GameSettings settings_;
//    int difficulty = 0;

    std::vector<Move> history_of_moves_ = {};
    unsigned int point_of_history_ = 0;
};

#endif  //_INTELLECTOR_CONTROLLER_HPP
