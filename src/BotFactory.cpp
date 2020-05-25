
#include <memory>

#include "BotFactory.hpp"
#include "RandomBot.hpp"
#include "OptimizedAlphaBetaBot.hpp"
#include "AlphaBetaBot.hpp"
#include "GreedyBot.hpp"
#include "Evaluate.hpp"


std::shared_ptr<Bot> BotFactory(const GameSettings &settings) 
{
    int difficulty = settings.difficulty();
    std::shared_ptr<Bot> bot;
    switch(difficulty)
    {
        case 0:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
            break;
        case 2:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<GreedyBot>(evaluate::scoreSumFigurePoints));
            break;
        case 3:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(3, 0));
            break;
        case 6:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(4, 0));
            break;
        case 10:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(5, 0));
            break;
        default:
            assert(false);
    }
    return bot;
}
