#ifndef _RANDOMBOT_HPP
#define _RANDOMBOT_HPP

#include "Bot.hpp"

class RandomBot : Bot
{
public:
    RandomBot() = default;
    std::shared_ptr<Move> makeMove(const Game &g) override;
};

#endif //_RANDOMBOT_HPP
