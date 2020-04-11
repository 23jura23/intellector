#ifndef _GREEDYBOT_HPP
#define _GREEDYBOT_HPP

#include "Bot.hpp"
#include "MoveTypes.hpp"
#include <functional>

class GreedyBot : Bot {
   public:
    GreedyBot() = delete;
    GreedyBot(std::function<int(const Board& board, const PlayerColour colour)> eval_function)
            : evaluation_finction_(eval_function){};
    std::shared_ptr<Move> makeMove(const Game& game) override;

   private:
    std::function<int(const Board& board, const PlayerColour colour)> evaluation_finction_;
};

#endif
