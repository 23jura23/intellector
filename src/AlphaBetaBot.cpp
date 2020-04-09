#include "AlphaBetaBot.hpp"
#include "Game.hpp"
#include "Evaluate.hpp"

#include <cassert>

const int DEPTH = 4;
PlayerColour Colour;

std::pair<int, std::shared_ptr<SimpleMove>> AlphaBetaBot::make_virtual_move(const Game &game,
                                                                            PlayerColour colour,
                                                                            bool max,
                                                                            int alpha,
                                                                            int beta,
                                                                            int depth) {
    int value = evaluation_function_(game, Colour);

    if(abs(value) > 1e5)
    {
        return {value, nullptr};
    }

    if (depth == 0) {
        return std::pair<int, std::shared_ptr<SimpleMove>>{
            evaluation_function_(game, Colour),
            nullptr};
    }

    std::vector<std::shared_ptr<SimpleMove>> all_moves;

    // sort(all_moves.begin(), all_moves.end(), [&](auto a, auto b)
    // {
    //     Game gamecopy1(game);
    //     gamecopy1.makeMove(*a);
    //     Game gamecopy2(game);
    //     gamecopy2.makeMove(*b);
    //     int eval1 = evaluation_function_(gamecopy1.getBoard(), colour);
    //     int eval2 = evaluation_function_(gamecopy2.getBoard(), colour);
    //     if(max)
    //         return eval1 > eval2;
    //     else 
    //         return eval1 < eval2;
    // });

    Board board = Board(game.getBoard());

    for (auto &row : board.data_)
        for (auto &cell : row) {
            std::vector<std::shared_ptr<SimpleMove>> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) 
            	all_moves.push_back(move);
        }

    if (max) {
        std::pair<int, std::shared_ptr<SimpleMove>> res = {-1000, nullptr};
        for (const auto &move : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);
            if(!move)
            {
            	assert(0);
            }
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
        std::pair<int, std::shared_ptr<SimpleMove>> res = {1000, nullptr};
        for (auto &move : all_moves) {
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
    auto colour = game.getColourCurrentPlayer();
    Colour = colour;
	return make_virtual_move(gamecopy, colour, true, -1000, 1000, DEPTH).second;
}
