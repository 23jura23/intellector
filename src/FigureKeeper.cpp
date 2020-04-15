#include "FigureKeeper.hpp"
#include <iostream>
#include <chrono>
#include <thread>


using std::cout;
using std::endl;

FigureKeeper::FigureKeeper(const Board &board)
{
	for (auto &row : board.data_)
        for (auto &cell : row) 
        {
        	if(cell.figure_.has_value())
        	{
        		Position pos = cell.pos_;
        		insertFigure(get_figures(cell.figure_->colour_), pos);
        	}
        }
}

std::unordered_set<Position>& FigureKeeper::get_figures(const PlayerColour colour)
{
	if(colour == PlayerColour::black_)
		return black_figures_;
	else
		return white_figures_;
}

void FigureKeeper::insertFigure(std::unordered_set<Position> &set, Position &pos)
{
	pos.makeSum();
	assert(set.find(pos) == set.end());
	set.insert(pos);
}

void FigureKeeper::eraseFigure(std::unordered_set<Position> &set, Position &pos)
{
	pos.makeSum();
	assert(set.find(pos) != set.end());
	set.erase(pos);
}



void FigureKeeper::makeMove(Move &move)
{
	if(move.to_figure_old_.has_value())
	{
		eraseFigure(get_figures(move.to_figure_old_->colour_), move.to_);

	}
	eraseFigure(get_figures(move.from_figure_old_.colour_), move.from_);

	insertFigure(get_figures(move.to_figure_new_.colour_), move.to_);

	if(move.from_figure_new_.has_value())
	{
		insertFigure(get_figures(move.from_figure_new_->colour_), move.from_);
	}
}

void FigureKeeper::cancelMove(Move &move)
{
	eraseFigure(get_figures(move.to_figure_new_.colour_), move.to_);
	if(move.from_figure_new_.has_value())
	{
		eraseFigure(get_figures(move.from_figure_new_->colour_), move.from_);
	}

	if(move.to_figure_old_.has_value())
	{
		insertFigure(get_figures(move.to_figure_old_->colour_), move.to_);
	}
	insertFigure(get_figures(move.from_figure_old_.colour_), move.from_);
}
