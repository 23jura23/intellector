#include "Evaluate.hpp"

#include "Board.hpp"
#include "Cell.hpp"
#include "Figure.hpp"
#include "Game.hpp"

namespace evaluate 
{
    const std::unordered_map<FigureType, int> figure_value = 
        {
            {FigureType::INTELLECTOR, 1000000},
            {FigureType::DOMINATOR  ,       7},  // ферзь
            {FigureType::AGGRESSOR  ,       6},  //по черным
            {FigureType::DEFENSSOR  ,       4},
            {FigureType::LIBERATOR  ,       2}, // через один
            {FigureType::PROGRESSOR ,       3}  //пешка
        };

    int figureValue(const std::optional<Figure> &figure, const PlayerColour colour) 
    {
        if (figure.has_value()) {
            if (figure->colour_ == colour)
                return figure_value.at(figure->type_);
            else
                return -figure_value.at(figure->type_);
        } 
        else
            return 0;
    }

    int scoreSumFigurePoints(const Game &game, const PlayerColour colour) 
    {
        Board board = game.getBoard();
        int sum = 0;
        for (const auto &row : board.data_)
            for (const auto &cell : row) 
                sum += figureValue(cell.figure_, colour);
        return sum;
    }
};  // namespace evaluate

namespace delta 
{
    // const std::unordered_map<evaluate_function_t, delta_function_t> deltas =
    // {
    //     {scoreSumFigurePoints, deltaSumFigurePoints}
    // };

    int deltaSumFigurePoints(const Move &move, const PlayerColour colour) 
    {
        int delta = 0;
        delta -= evaluate::figureValue(move.from_figure_old_, colour);
        delta += evaluate::figureValue(move.to_figure_new_, colour);
        delta += evaluate::figureValue(move.from_figure_new_, colour);
        delta -= evaluate::figureValue(move.to_figure_old_, colour);
        return delta;
    }

}  // namespace delta

bool operator==(const Move &a, const Move& b)
{
    return a.to_ == b.to_ && 
           a.from_figure_new_ == b.from_figure_new_ && 
           a.to_figure_new_ == b.to_figure_new_ &&
           a.from_figure_old_ == b.from_figure_old_ &&
           a.to_figure_old_ == b.to_figure_old_;
}

