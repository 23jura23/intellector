#include "RandomBot.hpp"

#include <cassert>
#include <random>

#include "Game.hpp"

const int seed = 1337;

std::mt19937 rnd(seed);

Move RandomBot::makeMove(const Game &game) 
{
    Board board = Board(game.getBoard());

    std::vector<Move> all_moves;

    for (auto &row : board.data_)
        for (auto &cell : row) 
        {
            std::vector<Move> moves = game.allFigureMoves(cell.pos_);
            for (auto move : moves) all_moves.push_back(move);
        }

    assert(all_moves.size() > 0);
    size_t necessary_move = rnd() % all_moves.size();

    return all_moves[necessary_move];
}
