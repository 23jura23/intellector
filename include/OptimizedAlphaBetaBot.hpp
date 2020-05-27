
#ifndef _OPTIMIZEDALPHABETABOT_HPP
#define _OPTIMIZEDALPHABETABOT_HPP

#include <atomic>

#include "Bot.hpp"
#include "FunctionSet.hpp"
#include "FigureKeeper.hpp"


class OptimizedAlphaBetaBot : Bot
{
public:
    OptimizedAlphaBetaBot() = delete;
    
    ~OptimizedAlphaBetaBot() override = default;

    OptimizedAlphaBetaBot(int depth, int set_number) : 
                 depth_(depth),  
                 functions_(set_number) {};

    Move makeMove(const Game &g) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;

    void resetFinishedMove() override;
    bool isMoveFinished() override;

private:
    std::pair<int, Move> make_virtual_move(Game &game,
                                           PlayerColour colour,
                                           bool max,
                                           int alpha,
                                           int beta,
                                           int depth, 
                                           int prev_value);

    std::atomic<bool> finished_move = true;

    int depth_;
    FunctionSet functions_;
    FigureKeeper figures_;
};

#endif  //_OPTIMIZEDALPHABETABOT_HPP
