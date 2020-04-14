
#ifndef _ALPHABETABOT_HPP
#define _ALPHABETABOT_HPP

#include "Bot.hpp"
// #include "Evaluate.hpp"
#include "FunctionSet.hpp"
// #pragma once

class AlphaBetaBot : Bot
{
public:
    AlphaBetaBot() = delete;
    AlphaBetaBot(int depth, int set_number) : 
                 depth_(depth),  
                 functions_(set_number) {};

    Move makeMove(const Game &g) override;

   private:
    std::pair<int, Move> make_virtual_move(const Game &game,
                                           PlayerColour colour,
                                           bool max,
                                           int alpha,
                                           int beta,
                                           int depth);
    int depth_;
    // evaluate_function_t evaluation_function_;
    FunctionSet functions_;

};

#endif  //_ALPHABETABOT_HPP
