#include <vector>
#include <atomic>
#include <cassert>

#include "GreedyBot.hpp"
#include "Game.hpp"

void GreedyBot::resetFinishedMove()
{
    finished_move = false;
}

bool GreedyBot::isMoveFinished()
{
    return finished_move;
}

Move GreedyBot::makeMove(const Game &game) 
{

    auto colour = game.getColourCurrentPlayer();
    Board board = Board(game.getBoard());
    std::vector<Move> all_moves;

    for (auto &row : board.data_)
        for (auto &cell : row) 
        {
            std::vector<Move> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) all_moves.push_back(move);
        }

    int max = -1e9;
    Move res;
    for(auto &move : all_moves) 
    {
        Game gamecopy(game.makeCopyForBot());
        gamecopy.makeMove(move);
        int eval = evaluation_finction_(gamecopy, colour);
        if (eval > max) 
        {
            res = move;
            max = eval;
        }
    }

    finished_move = true;
    return res;
}

std::pair<int, Move> GreedyBot::test_makeMove(const Game &game) 
{
    auto colour = game.getColourCurrentPlayer();
    Board board = Board(game.getBoard());
    std::vector<Move> all_moves;

    for (auto &row : board.data_)
        for (auto &cell : row) 
        {
            std::vector<Move> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) all_moves.push_back(move);
        }

    int max = -1e9;
    Move res;
    for(auto &move : all_moves) 
    {
        Game gamecopy(game.makeCopyForBot());
        gamecopy.makeMove(move);
        int eval = evaluation_finction_(gamecopy, colour);
        if (eval > max) 
        {
            res = move;
            max = eval;
        }
    }
    return {max, res};
}

