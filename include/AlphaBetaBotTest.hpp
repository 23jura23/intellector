
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


// TEST_CASE("Two AlphaBeta")
// {
//     const int depth = 4;
//     auto bot1 = TestBotFactory(2, depth);
//     auto bot2 = TestBotFactory(3, depth);

//     Game game{};

//     int cnt = 0;
//     for(;game.getGameStatus() == GameStatus::game_running_;)
//     {
//         auto move1 = bot1->test_makeMove(game);
//         auto move2 = bot2->test_makeMove(game);
//         CHECK(move1.first == move2.first);
//         // if(!(move1.steady_clocknd == move2.second))
//         {
//             // auto move11 = move1.second;
//             // auto move22 = move2.second;

//             // cout << move11.from_.x_ << ' ' << move11.from_.y_ << ' ' << move11.from_.z_ << endl;
//             // cout << move22.from_.x_ << ' ' << move22.from_.y_ << ' ' << move22.from_.z_ << endl;
//             // cout << move11.to_.x_ << ' ' << move11.to_.y_ << ' ' << move11.to_.z_ << endl;
//             // cout << move22.to_.x_ << ' ' << move22.to_.y_ << ' ' << move22.to_.z_ << endl;
//             // cout << move11.from_.posW() << ' ' << move11.from_.posH() << endl;
//             // cout << move22.from_.posW() << ' ' << move22.from_.posH() << endl;

//         }
//         game.makeMove(move1.second);
//         cnt++;
//         if(cnt % 10 == 0)
//         {
//             cout << cnt << endl;
//         }
//     }
//     cout << cnt << " moves" << endl;
// }

TEST_CASE("Time test")
{

    // const int depth = 5;
    for(int depth = 1; depth <= 5; depth++)
    {

        auto bot1 = TestBotFactory(2, depth);
        auto bot2 = TestBotFactory(2, depth);


        Game game_wrapper{};

        auto game = game_wrapper.makeCopyForBot();

        // auto move1 = bot1->test_makeMove(game);
        // auto move2 = bot2->test_makeMove(game);
        // CHECK(move1 == move2);
        // return;
        double maximum_time = 0;
        for(;game.getGameStatus() == GameStatus::game_running_;)
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
            // cout << "Move maked" << endl;
            // cout << evaluate::scoreSumFigurePoints(game, PlayerColour::white_) << ' ' << (game.getColourCurrentPlayer() == PlayerColour::white_)<< endl;
        }
        cout << "In depth = " << depth + 1 << " maximum_time = " << maximum_time << " s" << endl;
    }
}