
#ifndef _ALPHABETABOT_HPP
#define _ALPHABETABOT_HPP

#include "Bot.hpp"
#include "FunctionSet.hpp"
#include "FigureKeeper.hpp"

class AlphaBetaBot : Bot
{
public:
    AlphaBetaBot() = delete;
    AlphaBetaBot(int depth, int set_number) : 
                 depth_(depth),  
                 functions_(set_number) {};

    Move makeMove(const Game &g) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;

    FigureKeeper &getFigures();

   private:
    std::pair<int, Move> make_virtual_move(Game &game,
                                           PlayerColour colour,
                                           bool max,
                                           int alpha,
                                           int beta,
                                           int depth, 
                                           int prev_value);

    int depth_;
    FunctionSet functions_;
    FigureKeeper figures_;
};

#endif  //_ALPHABETABOT_HPP
