#ifndef _BOT_HPP
#define _BOT_HPP

#include <functional>
#include <map>
#include <memory>

#include "Game.hpp"

class Bot {
   public:
    virtual std::shared_ptr<SimpleMove> makeMove(Game &b) = 0;
};

class RandomBot : Bot {
   public:
    std::shared_ptr<SimpleMove> makeMove(Game &b) override;
};

class AlphaBetaBot : Bot {
   public:
    AlphaBetaBot(
        int depth,
        std::function<int(const Board &board, const PlayerColour colour)> evaluation_function)
        : depth_(depth)
        , evaluation_function_(evaluation_function){};

    std::shared_ptr<SimpleMove> makeMove(Game &b) override;

   private:
    int depth_;
    std::function<int(const Board &board, const PlayerColour colour)> evaluation_function_;
};

namespace evaluate {
const std::map<FigureType, int> figure_value = {
    {FigureType::INTELLECTOR, 100},
    {FigureType::DOMINATOR, 7},  // ферзь
    {FigureType::AGGRESSOR, 4},  //по черным
    {FigureType::DEFENSSOR, 4},
    {FigureType::LIBERATOR, 2},  // через один
    {FigureType::PROGRESSOR, 3}  //пешка
};

int scoreSumFigurePoints(const Board &board, const PlayerColour colour) {
    int sum = 0;
    for (auto &row : board.data_)
        for (auto &cell : row)
            if (cell.figure_.has_value()) {
                Figure figure = *cell.figure_;

                if (figure.colour_ == colour)
                    sum += figure_value.at(figure.type_);
                else
                    sum -= figure_value.at(figure.type_);
            }
    return sum;
}
};  // namespace evaluate

#endif  //_BOT_HPP
