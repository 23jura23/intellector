#include "AlphaBetaBot.hpp"
#include "Game.hpp"
#include "Evaluate.hpp"

#include <cassert>

#include <iostream>
#include <thread>         
#include <chrono>
#include <random>

#include <thread>
#include <chrono>

std::mt19937 randoms(std::time(0));

using std::cout;
using std::endl;

const int DEPTH = 5;
PlayerColour Colour;
int cnt = 0;

std::pair<int, std::shared_ptr<SimpleMove>> AlphaBetaBot::make_virtual_move(const Game &game,
                                                                            PlayerColour colour,
                                                                            bool max,
                                                                            int alpha,
                                                                            int beta,
                                                                            int depth) {
    int value = evaluation_function_(game, Colour);

    cnt++;
    if(abs(value) > 1e5)
    {
        return {value, nullptr};
    }

    if (depth == 0) {
        return std::pair<int, std::shared_ptr<SimpleMove>>{
            evaluation_function_(game, Colour),
            nullptr};
    }

    std::vector<std::pair<std::shared_ptr<SimpleMove>, int>> all_moves;


    Board board = Board(game.getBoard());

    for (auto &row : board.data_)
        for (auto &cell : row) {
            std::vector<std::shared_ptr<SimpleMove>> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) 
                all_moves.emplace_back(move, evaluate::figure_value.at(cell.figure_.value().type_));
        }

    std::sort(all_moves.begin(), all_moves.end(), [&](auto a, auto b)
    {
        return a.second > b.second;
    });

    // std::shuffle(all_moves.begin(), all_moves.end(), randoms);

    if (max) {
        std::pair<int, std::shared_ptr<SimpleMove>> res = {-1e9, nullptr};
        for (const auto &[move, _] : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);

            copy.makeMove(*move);
            auto mvm = make_virtual_move(copy, other_colour(colour), !max, alpha, beta, depth - 1);

            if(res.first < mvm.first)
            {
                res.first = mvm.first;
                res.second = move;
            }

            alpha = std::max(alpha, mvm.first);
        }
        return res;
    } else {
        std::pair<int, std::shared_ptr<SimpleMove>> res = {1e9, nullptr};
        for (auto &[move, _] : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);
            copy.makeMove(*move);
            auto mvm = make_virtual_move(copy, other_colour(colour), !max, alpha, beta, depth - 1);

            if(res.first > mvm.first)
            {
                res.first = mvm.first;
                res.second = move;
            }
            beta = std::min(beta, mvm.first);
        }
        return res;
    }
}

std::shared_ptr<SimpleMove> AlphaBetaBot::makeMove(const Game &game) {
    Game gamecopy(game);
    cnt = 0;
    auto colour = game.getColourCurrentPlayer();
    Colour = colour;
    auto res = make_virtual_move(gamecopy, colour, true, -1000, 1000, DEPTH);
    cout << cnt << endl;
    std::this_thread::sleep_for (std::chrono::seconds(10));
    return res.second;
}
