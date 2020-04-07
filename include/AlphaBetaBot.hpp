#include "Bot.hpp"

class AlphaBetaBot : Bot
{
public:
	AlphaBetaBot() = default;
	AlphaBetaBot(int depth, std::function<int(const Board& board, const PlayerColour colour)> evaluation_function) : 
				 depth_(depth),  
				 evaluation_function_(evaluation_function) {};

	std::shared_ptr<SimpleMove> makeMove(const Game &g) override;

private:
	std::pair<int, std::shared_ptr<SimpleMove>> make_virtual_move(const Game &game, PlayerColour colour, bool max, int alpha, int beta, int depth);
	int depth_;
	std::function<int(const Board &board, const PlayerColour &colour)> evaluation_function_;
};

namespace evaluate
{
	const std::map<FigureType, int> figure_value = 
	{
		{FigureType::INTELLECTOR, 100},  
		{FigureType::DOMINATOR  ,   7},  // ферзь
		{FigureType::AGGRESSOR  ,   4},  //по черным
		{FigureType::DEFENSSOR  ,   4},  
		{FigureType::LIBERATOR  ,   2},  // через один
		{FigureType::PROGRESSOR ,   3}   //пешка
	};

	int scoreSumFigurePoints(const Board& board, const PlayerColour colour)
	{
		int sum = 0;
		for(auto &row : board.data_)
			for(auto &cell : row)
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
