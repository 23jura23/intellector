#include "FigureKeeper.hpp"
#include "Evaluate.hpp"
#include <iostream>
#include <chrono>
#include <thread>


using std::cout;
using std::endl;

FigureKeeper::FigureKeeper(const Board &board)
{
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

std::unordered_set<Position>& FigureKeeper::get_figures(const PlayerColour colour)
{
	if(colour == PlayerColour::black_)
		return black_figures_;
	else
		return white_figures_;
}

void FigureKeeper::insertFigure(Position &pos, Figure &fig)
{
    std::unordered_set<Position> &set = get_figures(fig.colour_);
	pos.makeSum();
	assert(set.find(pos) == set.end());
	set.insert(pos);
    hash ^= std::hash<Position>()(pos) * std::hash<Figure>()(fig);
    // hash++;
}

void FigureKeeper::eraseFigure(Position &pos, Figure &fig)
{
    std::unordered_set<Position> &set = get_figures(fig.colour_);

	pos.makeSum();
	assert(set.find(pos) != set.end());
	set.erase(pos);
    // hash ^= std::hash<std::pair<Position, Figure>>()({pos, fig});  
    hash ^= std::hash<Position>()(pos) * std::hash<Figure>()(fig);
    // hash--;
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
    // if(a.get_hash() != b.get_hash() && a.white_figures_ == b.white_figures_ && a.black_figures_ == b.black_figures_)
    // {
        // cout << a.white_figures_.size() << ' ' <<  b.white_figures_.size() << endl;
        // assert(0);
    // }
    return a.get_hash() == b.get_hash() && a.white_figures_ == b.white_figures_ && a.black_figures_ == b.black_figures_;
}

