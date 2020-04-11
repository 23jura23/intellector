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
#include <unordered_map>

std::mt19937 randoms(std::time(0));

using std::cout;
using std::endl;

const int DEPTH = 5;
PlayerColour Colour;
int cnt = 0;

std::unordered_map<std::pair<Board, std::pair<int, int>>, std::pair<int, std::shared_ptr<Move>>> answers;

std::pair<int, std::shared_ptr<Move>> AlphaBetaBot::make_virtual_move(const Game &game,
                                                                            PlayerColour colour,
                                                                            bool max,
                                                                            int alpha,
                                                                            int beta,
                                                                            int depth) {

    auto it = answers.find({game.getBoard(), std::make_pair(alpha, beta)});
    if(it != answers.end())
    {
        return it->second;
    }
    int value = evaluation_function_(game, Colour);

    cnt++;
    if(abs(value) > 1e5)
    {
        answers[{game.getBoard(), std::make_pair(alpha, beta)}] = {value, nullptr};
        return {value, nullptr};
    }


    cnt++;

    if (depth == 0) {
        return std::pair<int, std::shared_ptr<Move>>{
            evaluation_function_(game, Colour),
            nullptr};
    }

    struct ModifiedGame
    {
        ModifiedGame() = delete;
        std::shared_ptr<Game> gamecopy;
        std::shared_ptr<Move> move;
        int eval;

        ModifiedGame(const ModifiedGame &other)
        {
            gamecopy = other.get_gamecopy();
            move = other.move;
            eval = other.eval;
        }

        ModifiedGame(const std::shared_ptr<Game> &game, std::shared_ptr<Move> mv, int val) : gamecopy(game), move(mv), eval(val) {};

        const std::shared_ptr<Game> get_gamecopy() const
        {
            return gamecopy;
        }
    };

    std::vector<ModifiedGame> all_moves;

    Board board = Board(game.getBoard());

    for (const auto &row : board.data_)
        for (const auto &cell : row) {

            std::vector<std::shared_ptr<Move>> moves = game.allFigureMoves(cell.pos_);
            for (const auto &move : moves) 
            {
                Game gamecopy(game);
                gamecopy.makeMove(*move);

                all_moves.emplace_back(std::make_shared<Game>(gamecopy), move, evaluation_function_(gamecopy, Colour));
            }
        }

    int k = max ? 1 : -1;
    std::sort(all_moves.begin(), all_moves.end(), [&](const auto &a, const auto &b)
    {
        return k * a.eval > k * b.eval;
    });

    // std::shuffle(all_moves.begin(), all_moves.end(), randoms);

    if (max) {
        std::pair<int, std::shared_ptr<Move>> res = {-1e9, nullptr};
        for (const auto &mod_game : all_moves) {
            if (alpha > beta)
                break;

            auto mvm = make_virtual_move(*mod_game.get_gamecopy(), other_colour(colour), !max, alpha, beta, depth - 1);

            if(res.first < mvm.first)
            {
                res.first = mvm.first;
                res.second = mod_game.move;
            }

            alpha = std::max(alpha, mvm.first);
        }
        answers[{game.getBoard(), std::make_pair(alpha, beta)}] = res;
        return res;
    } else {
        std::pair<int, std::shared_ptr<Move>> res = {1e9, nullptr};
        for (const auto &mod_game : all_moves) {
            if (alpha > beta)
                break;
            auto mvm = make_virtual_move(*mod_game.get_gamecopy(), other_colour(colour), !max, alpha, beta, depth - 1);

            if(res.first > mvm.first)
            {
                res.first = mvm.first;
                res.second = mod_game.move;
            }
            beta = std::min(beta, mvm.first);
        }
        answers[{game.getBoard(), std::make_pair(alpha, beta)}] = res;

        return res;
    }
}

std::shared_ptr<Move> AlphaBetaBot::makeMove(const Game &game) {
    Game gamecopy(game);
    cnt = 0;
    auto colour = game.getColourCurrentPlayer();
    Colour = colour;

    auto res = make_virtual_move(gamecopy, colour, true, -1000, 1000, DEPTH);

    // cout << cnt << ' ' << res.first << endl;
    // std::this_thread::sleep_for (std::chrono::seconds(3));
    return res.second;
}
