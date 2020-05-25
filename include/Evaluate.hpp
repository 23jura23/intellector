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

    template<>
    struct hash<PlayerColour>
    {
        size_t operator()(const PlayerColour &pc) const
        {
            if(pc == PlayerColour::white_)
                return 1069741;
            else
                return 455671379;
        }

    };

    template<>
    struct hash<FigureType>
    {
        size_t operator()(const FigureType &ft) const
        {
            if(ft == FigureType::INTELLECTOR)     return            7919ull;
            else if(ft == FigureType::DOMINATOR)  return       179424697ull;
            else if(ft == FigureType::AGGRESSOR)  return      2038074761ull;
            else if(ft == FigureType::DEFENSSOR)  return            7933ull;
            else if(ft == FigureType::LIBERATOR)  return   2760727273697ull;
            else if(ft == FigureType::PROGRESSOR) return  29996224243919ull;
            else assert(0);

        }
    };

    template <>
    struct hash<Figure>
    {
        size_t operator()(const Figure &fig) const
        {
            auto t = std::pair{fig.colour_, fig.type_};
            if(t == std::pair{PlayerColour::black_, FigureType::INTELLECTOR})      return      22801763573ull;
            else if(t == std::pair{PlayerColour::black_, FigureType::DOMINATOR})   return   15002868201619ull;
            else if(t == std::pair{PlayerColour::black_, FigureType::AGGRESSOR})   return     267986485651ull;
            else if(t == std::pair{PlayerColour::black_, FigureType::DEFENSSOR})   return    3294896430451ull;
            else if(t == std::pair{PlayerColour::black_, FigureType::LIBERATOR})   return   55125235480849ull;
            else if(t == std::pair{PlayerColour::black_, FigureType::PROGRESSOR})  return      46498768607ull;

            else if(t == std::pair{PlayerColour::white_, FigureType::INTELLECTOR}) return    8101615860743ull;
            else if(t == std::pair{PlayerColour::white_, FigureType::DOMINATOR})   return     828513359743ull;
            else if(t == std::pair{PlayerColour::white_, FigureType::AGGRESSOR})   return   78701296245757ull;
            else if(t == std::pair{PlayerColour::white_, FigureType::DEFENSSOR})   return           733741ull;
            else if(t == std::pair{PlayerColour::white_, FigureType::LIBERATOR})   return      55883811611ull;
            else if(t == std::pair{PlayerColour::white_, FigureType::PROGRESSOR})  return          1069697ull;
            else assert(0);
        }
    };

    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>> 
    {
        size_t operator()(const std::pair<T1, T2> &pr) const 
        {
            return std::hash<T1>()(pr.first) ^ std::hash<T2>()(pr.second);
        }
    };

    template <>
    struct hash<Position>
    {
        size_t operator()(const Position &pos) const
        {
            return (static_cast<size_t>(pos.posW()) * 244053389ull) ^ (static_cast<size_t>(pos.posH()) * 3731825564471ull);
        } 

    };

    template <>
    struct hash<Move>
    {
        size_t operator()(const Move &mv) const
        {
            return (std::hash<Position>()(mv.from_) ^ 244053389ull) ^ (std::hash<Position>()(mv.to_) ^ 3731825564471ull);
        }
    };
};  // namespace std

bool operator==(const Move &a, const Move& b);

namespace evaluate 
{

    int scoreSumFigurePoints(const Game &game, const PlayerColour colour);
};  // namespace evaluate

namespace delta 
{
    int deltaSumFigurePoints(const Move &move, const PlayerColour colour);
}

#endif
