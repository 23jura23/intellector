#include "Bot/AlphaBetaBot/AlphaBetaBot.hpp"

#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Bot/AlphaBetaBot/Evaluate/EvalGame.hpp"
#include "Bot/AlphaBetaBot/Evaluate/FunctionSet/FunctionSet.hpp"
#include "Model/ModelImpl/Game.hpp"

using std::cout;
using std::endl;

namespace AlphaBetaData
{
    int cnt;
    PlayerColour Colour;
}

FigureKeeper &AlphaBetaBot::getFigures()
{
    return figures_;
}

void AlphaBetaBot::resetFinishedMove()
{
    finished_move = false;
}

bool AlphaBetaBot::isMoveFinished()
{
    return finished_move;
}


std::pair<int, Move> AlphaBetaBot::make_virtual_move(Game &game,
                                                     PlayerColour colour,
                                                     bool max,
                                                     int alpha,
                                                     int beta,
                                                     int depth, 
                                                     int prev_value) 
{
    int value = prev_value;
    if (abs(value) > 1e5) 
    {
        return {value, {}};
    }

    AlphaBetaData::cnt++;

    if (depth == 0) 
    {
        return std::pair<int, Move>{value, {}};
    }

    std::vector<std::pair<int, Move>> all_moves;


    int k = max ? 1 : -1;

    for(const auto &pos: figures_.get_figures(colour))
    {
        for (const auto &move : game.allFigureMoves(pos))
        {
            game.makeMove(move);
            all_moves.emplace_back(functions_.delta(move, AlphaBetaData::Colour), move);
            game.cancelMove();       
        }

    }


    std::sort(all_moves.begin(), all_moves.end(), [&](const auto &a, const auto &b) 
    {
        return k * a.first > k * b.first;
    });

    if (max) 
    {
        std::pair<int, Move> res = {-1e9, {}};
        for (auto &[delta, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            game.makeMove(move);
            
            figures_.makeMove(move);

            auto mvm = make_virtual_move(game, other_colour(colour), !max, alpha, beta, depth - 1, value + delta);

            if (res.first < mvm.first) 
            {
                res.first = mvm.first;
                res.second = move;
            }
            figures_.cancelMove(move);
            game.cancelMove();
            alpha = std::max(alpha, mvm.first);
        }

        return res;
    } 
    else 
    {
        std::pair<int, Move> res = {1e9, {}};
        for (auto &[delta, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            game.makeMove(move);
            figures_.makeMove(move);

            auto mvm = make_virtual_move(game, other_colour(colour), !max, alpha, beta, depth - 1, value + delta);

            if (res.first > mvm.first) 
            {
                res.first = mvm.first;
                res.second = move;
            }

            figures_.cancelMove(move);
            game.cancelMove();
            beta = std::min(beta, mvm.first);
        }

        return res;
    }
}

Move AlphaBetaBot::makeMove(const Game &game) 
{

    Game gamecopy(game.makeCopyForBot());
    figures_ = FigureKeeper(game.getBoard());

    AlphaBetaData::cnt = 0;

    auto colour = game.getColourCurrentPlayer();
    AlphaBetaData::Colour = colour;

    std::pair<int, Move> res;

    int l = -2e5;
    int r =  2e5;

    int eval = functions_.evaluate(game, AlphaBetaData::Colour);
    res = make_virtual_move(gamecopy, colour, true, l, r, depth_, eval);

    finished_move = true;

    return res.second;
}


std::pair<int, Move> AlphaBetaBot::test_makeMove(const Game &game) 
{
    Game gamecopy(game.makeCopyForBot());
    figures_ = FigureKeeper(game.getBoard());

    AlphaBetaData::cnt = 0;

    auto colour = game.getColourCurrentPlayer();
    AlphaBetaData::Colour = colour;

    std::pair<int, Move> res;

    int l = -2e5;
    int r =  2e5;

    int eval = functions_.evaluate(game, AlphaBetaData::Colour);
    res = make_virtual_move(gamecopy, colour, true, l, r, depth_, eval);

    return res;
}
