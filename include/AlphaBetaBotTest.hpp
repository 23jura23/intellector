
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


TEST_CASE("Two AlphaBeta")
{
    const int depth = 3;
    auto bot1 = TestBotFactory(2, depth);
    auto bot2 = TestBotFactory(3, depth);

    Game game{};

    int cnt = 0;
    for(;game.getGameStatus() == GameStatus::game_running_;)
    {
        auto move1 = bot1->test_makeMove(game);
        auto move2 = bot2->test_makeMove(game);
        CHECK(move1.first == move2.first);
        game.makeMove(move1.second);
        cnt++;
        // if(cnt % 10 == 0)
        // {
        //     cout << cnt << endl;
        // }
    }
}

TEST_CASE("Time test")
{

    const int depth = 5;
    auto bot = TestBotFactory(2, depth);

    Game game{};

    double maximum_time = 0;
    for(;game.getGameStatus() == GameStatus::game_running_;)
    {
        auto start = std::chrono::steady_clock::now();
        auto move = bot->makeMove(game);
        auto finish = std::chrono::steady_clock::now();

        CHECK(std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() <= 10);
        maximum_time = std::max(maximum_time, std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count());
        game.makeMove(move);
    }
    cout << "maximum_time = " << maximum_time << endl;
}

TEST_CASE("Better than me")
{
    // auto bot1 = TestBotFactory(2, 3);
    auto bot = TestBotFactory(2, 4);


    Game game{};

    for(;game.getGameStatus() == GameStatus::game_running_;)
    {
        game.makeMove(bot->makeMove(game));
    }

    CHECK(game.getGameStatus() == GameStatus::game_over_white_win_);
    // if(game.getGameStatus() == GameStatus::game_over_black_win_)
    // {
    //     cout << "GG" << endl;
    // }
}