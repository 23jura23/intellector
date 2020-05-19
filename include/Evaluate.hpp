#ifndef _EVALUATE_HPP
#define _EVALUATE_HPP

#include <cassert>
#include <unordered_map>

#include "Board.hpp"
#include "Figure.hpp"
#include "Game.hpp"

using evaluate_function_t = std::function<int(const Game &game, const PlayerColour &colour)>;
using delta_function_t = std::function<int(const Move &move, const PlayerColour &colour)>;

namespace std 
{

    template <>
    struct hash<Board> 
    {
        size_t operator()(const Board &board) const 
        {
            size_t h = 0;
            for (const auto &row : board.data_)
                for (const auto &cell : row) 
                {
                    h *= 23;
                    if (cell.figure_.has_value()) 
                    {
                        size_t val = 0;
                        switch (cell.figure_->type_) 
                        {
                            case FigureType::INTELLECTOR:
                                val = 1;
                                break;
                            case FigureType::DOMINATOR:
                                val = 2;
                                break;
                            case FigureType::AGGRESSOR:
                                val = 3;
                                break;
                            case FigureType::DEFENSSOR:
                                val = 4;
                                break;
                            case FigureType::LIBERATOR:
                                val = 5;
                                break;
                            case FigureType::PROGRESSOR:
                                val = 6;
                                break;
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
            return std::hash<T1>()(pr.first) ^ std::hash<T2>()(pr.second);
            // return 228;
        }
    };

    template <>
    struct hash<Position>
    {
        size_t operator()(const Position &pos) const
        {
            return std::hash<int>()(pos.x_) * 31 * 31 + std::hash<int>()(pos.y_) * 31 + std::hash<int>()(pos.z_);
        } 

    };

    template <>
    struct hash<Figure>
    {
        inline static const std::unordered_map<std::pair<PlayerColour, FigureType>, size_t> prime_values
        {
            {{PlayerColour::black_, FigureType::INTELLECTOR},  2},
            {{PlayerColour::black_, FigureType::DOMINATOR},    3},
            {{PlayerColour::black_, FigureType::AGGRESSOR},    5},
            {{PlayerColour::black_, FigureType::DEFENSSOR},    7},
            {{PlayerColour::black_, FigureType::LIBERATOR},    9},
            {{PlayerColour::black_, FigureType::PROGRESSOR},  11},

            {{PlayerColour::white_, FigureType::INTELLECTOR}, 13},
            {{PlayerColour::white_, FigureType::DOMINATOR},   17},
            {{PlayerColour::white_, FigureType::AGGRESSOR},   19},
            {{PlayerColour::white_, FigureType::DEFENSSOR},   23},
            {{PlayerColour::white_, FigureType::LIBERATOR},   29},
            {{PlayerColour::white_, FigureType::PROGRESSOR},  31}
        };

        size_t operator()(const Figure &fig) const
        {
            return prime_values.at({fig.colour_, fig.type_});
        }
    };
};  // namespace std

bool operator==(const Move &a, const Move& b);

namespace evaluate 
{

    int scoreSumFigurePoints(const Game &game, const PlayerColour colour);
    // static int scoreSumWithDangers(const Game& game, const PlayerColour colour)
    // {

    // }
};  // namespace evaluate

namespace delta 
{
    int deltaSumFigurePoints(const Move &move, const PlayerColour colour);
}

#endif
