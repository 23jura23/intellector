#ifndef _FUNCTIONSET_HPP
#define _FUNCTIONSET_HPP

#include "Bot/AlphaBetaBot/Evaluate/Evaluate.hpp"
#include "Model/ModelImpl/Game.hpp"

class FunctionSet
{
public:
    evaluate_function_t evaluate_;
    delta_function_t delta_;

    explicit FunctionSet(int set_number);

    int evaluate(Game &game, const PlayerColour colour);
    int evaluate(const Game &game, const PlayerColour colour);


    int delta(const Move &move, const PlayerColour colour);
    int delta(Move &move, const PlayerColour colour);

};

#endif //_FUNCTIONSET_HPP
