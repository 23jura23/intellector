#ifndef _FIGUREKEEPER_HPP
#define _FIGUREKEEPER_HPP

#include "Position.hpp"
#include "Figure.hpp"
#include "Evaluate.hpp"

#include <unordered_set>
#include <unordered_map>


class FigureKeeper
{
public:
	FigureKeeper() = default;
	FigureKeeper(const Board &board);


	std::unordered_set<Position> &get_figures(const PlayerColour colour);

	void makeMove(Move &move);
	void cancelMove(Move &move);

private:
	void insertFigure(std::unordered_set<Position> &set, Position &pos);
	void eraseFigure(std::unordered_set<Position> &set, Position &pos);

    long long hash = 0;
	std::unordered_set<Position> white_figures_;
	std::unordered_set<Position> black_figures_;

};

#endif // _FIGUREKEEPER_HPP
