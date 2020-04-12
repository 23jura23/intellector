#include "FunctionSet.hpp"
#include "Evaluate.hpp"

FunctionSet::FunctionSet(int set_number)
{
    if(set_number == 0)
    {
        evaluate_ = evaluate::scoreSumFigurePoints;
        delta_    = delta::deltaSumFigurePoints;
    }
    else
    {
        assert(0);
    }
}

int FunctionSet::evaluate(Game &game, PlayerColour colour)
{
    return evaluate_(game, colour);
}


int FunctionSet::evaluate(const Game &game, const PlayerColour colour)
{
    return evaluate_(game, colour);
}


int FunctionSet::delta(const Move &move, PlayerColour colour)
{
    return delta_(move, colour);
}

int FunctionSet::delta(Move &move, PlayerColour colour)
{
    return delta_(move, colour);
}
