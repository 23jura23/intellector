#ifndef _RANDOMBOT_HPP
#define _RANDOMBOT_HPP

#include <atomic>

#include "Bot.hpp"

class RandomBot : Bot
{
public:
    RandomBot() = default;
    Move makeMove(const Game &g) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;

    void resetFinishedMove() override;

    bool isMoveFinished() override;

private:
    std::atomic<bool> finished_move = true;
};

#endif //_RANDOMBOT_HPP
