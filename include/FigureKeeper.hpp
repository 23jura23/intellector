#ifndef _FIGUREKEEPER_HPP
#define _FIGUREKEEPER_HPP

#include "Position.hpp"
#include "Figure.hpp"
#include "Board.hpp"
#include "MoveTypes.hpp"
#include "Evaluate.hpp"

#include <unordered_set>
#include <unordered_map>
#include <vector>


class FigureKeeper
{
public:
	FigureKeeper() = default;
	FigureKeeper(const Board &board);

    FigureKeeper(const std::vector<std::pair<Position, Figure>> &v);


	std::unordered_set<Position> &get_figures(const PlayerColour colour);

	void makeMove(Move &move);
	void cancelMove(Move &move);

    size_t get_hash() const;

    friend bool operator==(const FigureKeeper &a, const FigureKeeper &b);
	void insertFigure(Position &pos, Figure &fig);
	void eraseFigure(Position &pos, Figure &fig);
private:

    size_t hash = 0;
	std::unordered_set<Position> white_figures_;
	std::unordered_set<Position> black_figures_;

};

namespace std
{
    template<>
    struct hash<FigureKeeper>
    {
        size_t operator()(const FigureKeeper &fig_keep) const
        {
            return fig_keep.get_hash();
        }
    };
};

bool operator==(const FigureKeeper &a, const FigureKeeper &b);

#endif // _FIGUREKEEPER_HPP
