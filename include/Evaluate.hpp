#ifndef _EVALUATE_HPP
#define _EVALUATE_HPP

#include <unordered_map>
#include "Board.hpp"
#include "Figure.hpp"
#include "Game.hpp"

static PlayerColour other_colour(PlayerColour colour)
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

	static int scoreSumFigurePoints(const Game& game, const PlayerColour colour)
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

	// static int scoreSumWithDangers(const Game& game, const PlayerColour colour)
	// {

	// }
};

#endif
