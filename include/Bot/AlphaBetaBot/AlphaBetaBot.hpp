
#ifndef _ALPHABETABOT_HPP
#define _ALPHABETABOT_HPP

#include <atomic>

#include "Bot/AlphaBetaBot/Evaluate/FunctionSet/FunctionSet.hpp"
#include "Bot/AlphaBetaBot/FigureKeeper/FigureKeeper.hpp"
#include "Bot/Bot.hpp"

class AlphaBetaBot : Bot
{
public:
    AlphaBetaBot() = delete;
    
    ~AlphaBetaBot() override = default;

    AlphaBetaBot(int depth, int set_number) : 
                 depth_(depth),  
                 functions_(set_number) {};

    Move makeMove(const Game &g) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;


    FigureKeeper &getFigures();

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

#endif  //_ALPHABETABOT_HPP
