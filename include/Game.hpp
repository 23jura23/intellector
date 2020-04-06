//
// Created by vsg on 04.03.2020.
//

#ifndef _INTELLECTOR_CONTROLLER_HPP
#define _INTELLECTOR_CONTROLLER_HPP

#include "Board.hpp"
#include "BotFactory.hpp"
#include "FigureMoveValidator.hpp"
#include "MoveTypes.hpp"

class Game {
   public:
    // TODO конец игры?

    Game();

    Game(const GameSettings& settings) {
        if (settings.first_player())
            white_bot_ = BotFactory(settings);
        if (settings.second_player())
            black_bot_ = BotFactory(settings);
    }

    void setGameSettings(const GameSettings& settings);

    bool makeMove(const SimpleMove& move);

    [[nodiscard]] std::vector<std::shared_ptr<SimpleMove>> allFigureMoves(Position pos) const;

    [[nodiscard]] const Board& getBoard() const {
        return board_;
    }

    [[nodiscard]] PlayerColour getColourCurrentPlayer() const {
        return turn_;
    }

    [[nodiscard]] std::optional<PlayerColour> getWinner() const;

   private:
    Board board_;
    PlayerColour turn_ = PlayerColour::white_;
    std::shared_ptr<Bot> white_bot_ = nullptr, black_bot_ = nullptr;
};

#endif  //_INTELLECTOR_CONTROLLER_HPP
