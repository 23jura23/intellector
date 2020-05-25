#include <memory>
#include "BotFactory.hpp"
#include "RandomBot.hpp"
#include "OptimizedAlphaBetaBot.hpp"
#include "AlphaBetaBot.hpp"
#include "GreedyBot.hpp"
#include "Evaluate.hpp"


std::shared_ptr<Bot> TestBotFactory(const int &type, const int &depth)
{
    std::shared_ptr<Bot> bot;
    switch(type)
    {
        case 0:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
            break;
        case 1:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<GreedyBot>(evaluate::scoreSumFigurePoints));
            break;
        case 2:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(depth, 0));
            break;
        case 3:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<AlphaBetaBot>(depth, 0));
            break;
        default:
            assert(false);
    }
    return bot;
}
