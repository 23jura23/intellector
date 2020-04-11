#ifndef _EVALUATE_HPP
#define _EVALUATE_HPP

#include <unordered_map>
#include "Board.hpp"
#include "Figure.hpp"
#include "Game.hpp"
#include <unordered_map>


namespace std
{

    template <>
    struct hash<Board>
    {
        size_t operator()(const Board& board) const
        {
            size_t h = 0;
            for (const auto &row : board.data_)
                for (const auto &cell : row)
                {
                    h *= 23;
                    if(cell.figure_.has_value())
                    {
                        size_t val = 0;
                        switch (cell.figure_->type_)
                        {
                            case FigureType::INTELLECTOR : val = 1; break;
                            case FigureType::DOMINATOR   : val = 2; break;
                            case FigureType::AGGRESSOR   : val = 3; break;
                            case FigureType::DEFENSSOR   : val = 4; break;
                            case FigureType::LIBERATOR   : val = 5; break;
                            case FigureType::PROGRESSOR  : val = 6; break;
                        }
                        val <<= 1;
                        val += (cell.figure_->colour_ == PlayerColour::white_);
                        h += val;
                    }
                    else
                    {
                        h++;
                    }
                }
            return h;
        }
    };

    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>>
    {
        size_t operator()(const std::pair<T1, T2> &pr) const
        {
            return std::hash<T1>()(pr.first) * 31 + std::hash<T2>()(pr.second);
            // return 228;
        }

    };

};

const bool operator==(const Board &a, const Board &b);

const bool operator==(const Figure &a, const Figure &b);

const bool operator==(const Cell &a, const Cell &b);

PlayerColour other_colour(PlayerColour colour);

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

    int scoreSumFigurePoints(const Game& game, const PlayerColour colour);

    // static int scoreSumWithDangers(const Game& game, const PlayerColour colour)
    // {

    // }
};

#endif
