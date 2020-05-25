
#include "doctest.h"

#include "TestBotFactory.hpp"
#include "AlphaBetaBot.hpp"
#include "OptimizedAlphaBetaBot.hpp"
#include "Game.hpp"
#include "Evaluate.hpp"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

TEST_CASE("Time test")
{
    for(int depth = 5; depth >= 1; depth--)
    {

        auto bot1 = TestBotFactory(2, depth);
        auto bot2 = TestBotFactory(2, depth);


        Game game_wrapper{};

        auto game = game_wrapper.makeCopyForBot();

        double maximum_time = 0;
        int cnt = 0;
        for(; cnt < 20 && game.getGameStatus() == GameStatus::game_running_; cnt++)
        {
            auto start = std::chrono::steady_clock::now();
            Move move;
            if(game.getColourCurrentPlayer() == PlayerColour::white_) 
                move = bot1->makeMove(game);
            else 
                move = bot2->makeMove(game);

            auto finish = std::chrono::steady_clock::now();

            CHECK(std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() <= 10);
            maximum_time = std::max(maximum_time, std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count());
            game.makeMove(move);
        }
        cout << "In depth = " << depth + 1 << " maximum_time = " << maximum_time << " s" << endl;
    }
}

TEST_CASE("Two AlphaBeta")
{
    const int depth = 4;
    auto bot1 = TestBotFactory(2, depth);
    auto bot2 = TestBotFactory(3, depth);

    Game game_wrapper{};

    auto game = game_wrapper.makeCopyForBot();

    int cnt = 0;
    for(;game.getGameStatus() == GameStatus::game_running_;)
    {
        auto move1 = bot1->test_makeMove(game);
        auto move2 = bot2->test_makeMove(game);
        CHECK(move1.first == move2.first);

        game.makeMove(move1.second);
        cnt++;
    }
    cout << cnt << " moves" << endl;
}
