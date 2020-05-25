#include "FigureKeeper.hpp"
#include "Evaluate.hpp"
#include <iostream>
#include <chrono>
#include <thread>


using std::cout;
using std::endl;

FigureKeeper::FigureKeeper(const Board &board)
{
    // white_figures_.reserve(25);
    // black_figures_.reserve(25);

    hash = 0;
	for (auto &row : board.data_)
        for (auto &cell : row) 
        {
        	if(cell.figure_.has_value())
        	{
        		Position pos = cell.pos_;
                Figure   fig = *cell.figure_;
        		insertFigure(pos, fig);
        	}
        }
}

FigureKeeper::FigureKeeper(const std::vector<std::pair<Position, Figure>> &v)
{
    for(auto &i : v)
    {
        Position pos = i.first;
        Figure   fig = i.second;
        insertFigure(pos, fig);
    }
}


size_t FigureKeeper::get_hash() const
{
    return hash;
}

std::vector<Position>& FigureKeeper::get_figures(const PlayerColour colour)
{
	if(colour == PlayerColour::black_)
		return black_figures_;
	else
		return white_figures_;
}

void FigureKeeper::insertFigure(Position &pos, Figure &fig)
{
    std::vector<Position> &set = get_figures(fig.colour_);
	pos.makeSum();
    set.emplace_back(pos);
    hash ^= std::hash<Position>()(pos) * std::hash<Figure>()(fig);
}

void FigureKeeper::eraseFigure(Position &pos, Figure &fig)
{
    std::vector<Position> &set = get_figures(fig.colour_);

	pos.makeSum();
	set.erase(std::find(set.begin(), set.end(), pos));
    hash ^= std::hash<Position>()(pos) * std::hash<Figure>()(fig);
}



void FigureKeeper::makeMove(Move &move)
{
	if(move.to_figure_old_.has_value())
	{
		eraseFigure(move.to_, *move.to_figure_old_);

	}
	eraseFigure(move.from_, move.from_figure_old_);

	insertFigure(move.to_, move.to_figure_new_);

	if(move.from_figure_new_.has_value())
	{
		insertFigure(move.from_, *move.from_figure_new_);
	}
}

void FigureKeeper::cancelMove(Move &move)
{
	eraseFigure(move.to_, move.to_figure_new_);
	if(move.from_figure_new_.has_value())
	{
		eraseFigure(move.from_, *move.from_figure_new_);
	}

	if(move.to_figure_old_.has_value())
	{
		insertFigure(move.to_, *move.to_figure_old_);
	}
	insertFigure(move.from_, move.from_figure_old_);
}

bool operator==(const FigureKeeper &a, const FigureKeeper &b)
{
    bool is_white_match = true;
    bool is_black_match = true;
    for(const auto &pos : a.white_figures_)
        is_white_match &= (std::find(b.white_figures_.begin(), b.white_figures_.end(), pos) != b.white_figures_.end());

    for(const auto &pos : a.black_figures_)
        is_black_match &= (std::find(b.black_figures_.begin(), b.black_figures_.end(), pos) != b.black_figures_.end());
    

    return a.get_hash() == b.get_hash() && is_white_match && is_black_match;
}

