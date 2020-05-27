#ifndef _BOT_HPP
#define _BOT_HPP

#include <functional>
#include <map>
#include <memory>

#include "MoveTypes.hpp"

class Game;

class Bot 
{
public:
    Bot() = default;
    virtual ~Bot() = default;
    virtual Move makeMove(const Game &g) = 0;
    virtual std::pair<int, Move> test_makeMove(const Game &g) = 0;

    virtual void resetFinishedMove() = 0;

    virtual bool isMoveFinished() = 0;
};

#endif  // _BOT_HPP
