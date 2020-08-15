#ifndef _GREEDYBOT_HPP
#define _GREEDYBOT_HPP

#include <functional>

#include "Bot/AlphaBetaBot/Evaluate/Evaluate.hpp"
#include "Bot/Bot.hpp"
#include "Model/ModelImpl/MoveTypes.hpp"

class GreedyBot : Bot
{
public:
    GreedyBot() = delete;

    ~GreedyBot() override = default;

    GreedyBot(evaluate_function_t eval_function) : evaluation_finction_(eval_function) {};
    Move makeMove(const Game &game) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;

    void resetFinishedMove() override;
    bool isMoveFinished() override;

   private:
    std::atomic<bool> finished_move = true;

    evaluate_function_t evaluation_finction_;
};

#endif
