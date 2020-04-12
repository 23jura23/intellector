#include "Evaluate.hpp"
#include "Board.hpp"
#include "Figure.hpp"
#include "Cell.hpp"
#include "Game.hpp"

bool operator==(const Board &a, const Board &b)
{
    return a.data_ == b.data_;
}

bool operator==(const Figure &a, const Figure &b)
{
    return (a.colour_ == b.colour_ && a.type_ == b.type_);
}

bool operator==(const Cell &a, const Cell &b)
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
    const std::unordered_map<FigureType, int> figure_value = 
    {
        {FigureType::INTELLECTOR, 1000000},  
        {FigureType::DOMINATOR  ,       7},  // ферзь
        {FigureType::AGGRESSOR  ,       6},  //по черным
        {FigureType::DEFENSSOR  ,       4},  
        {FigureType::LIBERATOR  ,       2},  // через один
        {FigureType::PROGRESSOR ,       3}   //пешка
    };

    int figureValue(const std::optional<Figure> &figure, const PlayerColour colour)
    {
        if(figure.has_value())
        {
            if(figure->colour_ == colour)
                return figure_value.at(figure->type_);
            else
                return -figure_value.at(figure->type_);
        }
        else
            return 0;
    }

	int scoreSumFigurePoints(const Game& game, const PlayerColour colour)
    {
        Board board = game.getBoard();
        int sum = 0;
        for(const auto &row : board.data_)
            for(const auto &cell : row)
                sum += figureValue(cell.figure_, colour); 
        return sum;
    }   
};

namespace delta
{
    // const std::unordered_map<evaluate_function_t, delta_function_t> deltas = 
    // {
    //     {scoreSumFigurePoints, deltaSumFigurePoints}
    // };


    int deltaSumFigurePoints(const Move& move, const PlayerColour colour)
    {
        int delta = 0;
        delta -= evaluate::figureValue(move.from_figure_old_, colour);
        delta += evaluate::figureValue(move.from_figure_new_, colour);
        delta -= evaluate::figureValue(move.to_figure_old_, colour);
        delta += evaluate::figureValue(move.to_figure_new_, colour);
        return delta;
    }

}
