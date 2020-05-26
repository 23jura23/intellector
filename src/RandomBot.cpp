#include "RandomBot.hpp"

#include <cassert>
#include <random>
#include <atomic>

#include "Game.hpp"

const int seed = 1337;

std::mt19937 rnd(seed);

void RandomBot::resetFinishedMove() 
{
    finished_move = false;
}

bool RandomBot::isMoveFinished()
{
    return finished_move;
}

Move RandomBot::makeMove(const Game &game) 
{

    assert(!finished_move);

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

    finished_move = true;

    return all_moves[necessary_move];
}

std::pair<int, Move> RandomBot::test_makeMove(const Game &game) 
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

    return {0, all_moves[necessary_move]};
}
