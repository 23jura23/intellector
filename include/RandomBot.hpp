#ifndef _RANDOMBOT_HPP
#define _RANDOMBOT_HPP

#include "Bot.hpp"

class RandomBot : Bot
{
public:
    RandomBot() = default;
    Move makeMove(const Game &g) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;

};

#endif //_RANDOMBOT_HPP
