#include "OptimizedAlphaBetaBot.hpp"

#include <atomic>
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
    // std::mt19937 rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 rand(1337);

}

void OptimizedAlphaBetaBot::resetFinishedMove()
{
    finished_move = false;
}

bool OptimizedAlphaBetaBot::isMoveFinished()
{
    return finished_move;
}

std::unordered_map<std::pair<FigureKeeper, std::pair<int, std::pair<int, int>>>, std::pair<int, Move>> states;

int cnt = 0;

std::pair<int, Move> OptimizedAlphaBetaBot::make_virtual_move(Game &game,
                                                     PlayerColour colour,
                                                     bool max,
                                                     int alpha,
                                                     int beta,
                                                     int depth, 
                                                     int prev_value) 
{
    auto it = states.find({figures_, {depth, {alpha, beta}}});
    if(it != states.end())
    {
        return it->second;
    }

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

    std::shuffle(all_moves.begin(), all_moves.end(), OptAlphaBetaData::rand);

    std::stable_sort(all_moves.begin(), all_moves.end(), [&](const auto &a, const auto &b) 
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

        states[{figures_, {depth, {alpha, beta}}}] = res;
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

        states[{figures_, {depth, {alpha, beta}}}] = res;
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

    int l = -2e5;
    int r =  2e5;
    int eval = functions_.evaluate(game, OptAlphaBetaData::Colour);

    states.clear();
    states.reserve(5e5);

    res = make_virtual_move(gamecopy, colour, true, l - 1, r + 1, depth_, eval);

    finished_move = true;

    return res.second;
}

std::pair<int, Move> OptimizedAlphaBetaBot::test_makeMove(const Game &game) 
{
    Game gamecopy(game.makeCopyForBot());
    figures_ = FigureKeeper(game.getBoard());

    OptAlphaBetaData::cnt = 0;
    auto colour = game.getColourCurrentPlayer();
    OptAlphaBetaData::Colour = colour;

    std::pair<int, Move> res;

    int l = -2e5;
    int r =  2e5;
    int eval = functions_.evaluate(game, OptAlphaBetaData::Colour);

    states.clear();
    states.reserve(5e5);

    res = make_virtual_move(gamecopy, colour, true, l, r, depth_, eval);

    return res;
}
