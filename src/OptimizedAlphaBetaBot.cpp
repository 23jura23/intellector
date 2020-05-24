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
    std::mt19937 rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}



std::unordered_map<std::pair<FigureKeeper, std::pair<int, std::pair<int, int>>>, std::pair<int, Move>> states;
// std::unordered_set<Move> history;

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
    if(it != states.end() /*&& history.find(it->second.second) == history.end()*/)
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
            // if(history.find(move) == history.end())
            {
                game.makeMove(move);
                all_moves.emplace_back(functions_.delta(move, OptAlphaBetaData::Colour), move);
                game.cancelMove();       
            }
    }

    // if(history.size() > 0)
    //     cout << history.size() << endl;

    std::shuffle(all_moves.begin(), all_moves.end(), OptAlphaBetaData::rand);

    std::stable_sort(all_moves.begin(), all_moves.end(), [&](const auto &a, const auto &b) 
    {
        return k * a.first > k * b.first;
    });

    // for(int i = 0; i < all_moves.size(); i++)
    // {

    // }

    if (max) 
    {
        std::pair<int, Move> res = {-1e9, {}};
        for (auto [_, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            // if(history.find(move) != history.end())
            //     continue;

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

        states[{figures_, {depth, {alpha, beta}}}] = res;
        return res;
    } 
    else 
    {
        std::pair<int, Move> res = {1e9, {}};
        for (auto [_, move] : all_moves) 
        {
            if (alpha > beta)
                break;

            // if(history.find(move) != history.end())
            //     continue;

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
    // int g = eval;
    // for(; l < r; )
    // {
    states.clear();
    //     int beta = std::max(g, l + 1);
    //     res = make_virtual_move(gamecopy, colour, true, beta - 1, beta, depth_, eval);
    //     g = res.first;
    //     if(g < beta)
    //         r = g;
    //     else
    //         l = g;
    // }

    res = make_virtual_move(gamecopy, colour, true, l - 1, r + 1, depth_, eval);
    // cout << OptAlphaBetaData::cnt << ' ' << res.first << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // assert(!(res.second == Move()));
    // if(history.find(res.second) != history.end())
    // {
    //     cout << "BAD " << res.second.from_.posW() << ' ' << res.second.from_.posH() << endl;
    //     cout << "BAD " << res.second.to_.posW() << ' ' << res.second.to_.posH() << endl;
    // }
    // assert(history.find(res.second) == history.end());

    // history.insert(res.second);
    // cout << res.second.from_.posW() << ' ' << res.second.from_.posH() << endl;
    // cout << res.second.to_.posW() << ' ' << res.second.to_.posH() << endl;

    // cout << "HISTORY " << history.size() << endl;
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
    // int g = eval;
    // for(; l < r; )
    // {
    states.clear();
    //     int beta = std::max(g, l + 1);
    //     res = make_virtual_move(gamecopy, colour, true, beta - 1, beta - 1, depth_, eval);
    //     g = res.first;
    //     if(g < beta)
    //         r = g;
    //     else
    //         l = g;
    // }

    res = make_virtual_move(gamecopy, colour, true, l, r, depth_, eval);

    // cout << OptAlphaBetaData::cnt << ' ' << res.first << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // history.insert(res.second);

    return res;
}