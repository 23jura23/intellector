#ifndef _EVALGAME_HPP
#define _EVALGAME_HPP

#include "Bot/AlphaBetaBot/Evaluate/FunctionSet/FunctionSet.hpp"
#include "Evaluate.hpp"
#include "Model/ModelImpl/Game.hpp"

class EvalGame
{
public:
    Game game_;
    const PlayerColour bot_colour_;

    FunctionSet functions_;

    int eval_;

    EvalGame(const Game game, 
             const PlayerColour &bot_colour, 
             int set_number) : game_(game), bot_colour_(bot_colour), functions_(set_number), eval_(functions_.evaluate(game_, bot_colour_)) {};


    bool makeMove(const Move& move)
    {
        eval_ += functions_.delta(move, bot_colour_);
        return game_.makeMove(move);
    }

};

#endif //_EVALGAME_HPP
