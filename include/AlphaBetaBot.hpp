
#ifndef _ALPHABETABOT_HPP
#define _ALPHABETABOT_HPP

#include "Bot.hpp"
// #pragma once

class AlphaBetaBot : Bot
{
public:
    AlphaBetaBot() = delete;
    AlphaBetaBot(int depth, std::function<int(const Game& game, const PlayerColour colour)> evaluation_function) : 
                 depth_(depth),  
                 evaluation_function_(evaluation_function) {};

    std::shared_ptr<SimpleMove> makeMove(const Game &g) override;

private:
    std::pair<int, std::shared_ptr<SimpleMove>> make_virtual_move(const Game &game, PlayerColour colour, bool max, int alpha, int beta, int depth);
    int depth_;
    std::function<int(const Game &game, const PlayerColour &colour)> evaluation_function_;
};

#endif  //_ALPHABETABOT_HPP
