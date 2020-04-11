#include "Evaluate.hpp"
#include "Board.hpp"
#include "Figure.hpp"
#include "Cell.hpp"
#include "Game.hpp"

const bool operator==(const Board &a, const Board &b)
{
    return a.data_ == b.data_;
}

const bool operator==(const Figure &a, const Figure &b)
{
    return (a.colour_ == b.colour_ && a.type_ == b.type_);
}

const bool operator==(const Cell &a, const Cell &b)
{
    // return a.data_ == b.data_;
    if(a.pos_ != b.pos_ || a.colour_ != b.colour_)
        return 0;

    if((a.figure_.has_value() && !b.figure_.has_value()) || (!a.figure_.has_value() && b.figure_.has_value()))
        return 0;

    if(a.figure_.has_value())
    {
        if(!(*a.figure_ == *b.figure_))
            return 0;
    }

    return 1;
}

PlayerColour other_colour(PlayerColour colour)
{
    if(colour == PlayerColour::black_)
        return PlayerColour::white_;
    else
        return PlayerColour::black_;
}

namespace evaluate
{
	int scoreSumFigurePoints(const Game& game, const PlayerColour colour)
    {
        Board board = game.getBoard();
        int sum = 0;
        for(const auto &row : board.data_)
            for(const auto &cell : row)
                if(cell.figure_.has_value())
                {
                    Figure figure = *cell.figure_;

                    if(figure.colour_ == colour)
                        sum += figure_value.at(figure.type_);
                    else
                        sum -= figure_value.at(figure.type_);
                }
        return sum;
    }   
};
