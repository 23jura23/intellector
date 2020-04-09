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
		{FigureType::INTELLECTOR, 100},  
		{FigureType::DOMINATOR  ,   7},  // ферзь
		{FigureType::AGGRESSOR  ,   4},  //по черным
		{FigureType::DEFENSSOR  ,   4},  
		{FigureType::LIBERATOR  ,   2},  // через один
		{FigureType::PROGRESSOR ,   3}   //пешка
	};

	static int scoreSumFigurePoints(const Game& game, const PlayerColour colour)
	{
		Board board = game.getBoard();
		int sum = 0;
		bool enemy_intellector = 0;
		bool allied_intellector = 0;
		for(auto &row : board.data_)
			for(auto &cell : row)
				if(cell.figure_.has_value())
				{
					// sum++;
					Figure figure = *cell.figure_;
					if(figure.type_ == FigureType::INTELLECTOR)
					{
						if(figure.colour_ == colour)
							allied_intellector = 1;
						else
							enemy_intellector = 1;
					}

					if(figure.colour_ == colour)
						sum += figure_value.at(figure.type_);
					else
						sum -= figure_value.at(figure.type_);
				}
		if(!enemy_intellector)
			return 1e9;
		else if(!allied_intellector)
			return -1e9;
		return sum;
	}	

	// static int scoreSumWithDangers(const Game& game, const PlayerColour colour)
	// {

	// }
};

#endif
