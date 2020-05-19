#include "OptimizedAlphaBetaBot.hpp"

#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

#include "EvalGame.hpp"
#include "FunctionSet.hpp"
#include "Game.hpp"

using std::cout;
using std::endl;

namespace OptAlphaBetaData
{
    int cnt;
    PlayerColour Colour;
}

// std::unordered_map<std::pair<Board, std::pair<int, int>>, std::pair<int, Move>> answers;
// std::vector<std::unordered_map<Board, std::pair<int, Move>>> answers(DEPTH + 1);

std::pair<int, Move> OptimizedAlphaBetaBot::make_virtual_move(Game &game,
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

    OptAlphaBetaData::cnt++;

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
            all_moves.emplace_back(functions_.delta(move, OptAlphaBetaData::Colour), move);
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
        for (auto &[_, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            game.makeMove(move);
            
            figures_.makeMove(move);

            auto mvm = make_virtual_move(game, other_colour(colour), !max, alpha, beta, depth - 1, value + functions_.delta(move, OptAlphaBetaData::Colour));

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
        for (auto &[_, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            game.makeMove(move);
            figures_.makeMove(move);

            auto mvm = make_virtual_move(game, other_colour(colour), !max, alpha, beta, depth - 1, value + functions_.delta(move, OptAlphaBetaData::Colour));

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

Move OptimizedAlphaBetaBot::makeMove(const Game &game) 
{
    Game gamecopy(game.makeCopyForBot());
    figures_ = FigureKeeper(game.getBoard());

    OptAlphaBetaData::cnt = 0;
    auto colour = game.getColourCurrentPlayer();
    OptAlphaBetaData::Colour = colour;

    std::pair<int, Move> res;

    int l = -200;
    int r =  200;
    int eval = functions_.evaluate(game, OptAlphaBetaData::Colour);
    int g = eval;
    for(; l < r; )
    {
        int beta = std::max(g, l + 1);
        res = make_virtual_move(gamecopy, colour, true, beta - 1, beta, depth_, eval);
        g = res.first;
        if(g < beta)
            r = g;
        else
            l = g;
    }

    // cout << OptAlphaBetaData::cnt << ' ' << res.first << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    return res.second;
}
