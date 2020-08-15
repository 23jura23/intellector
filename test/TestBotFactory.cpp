#include <memory>

#include "Bot/AlphaBetaBot/AlphaBetaBot.hpp"
#include "Bot/AlphaBetaBot/Evaluate/Evaluate.hpp"
#include "Bot/AlphaBetaBot/OptimizedAlphaBetaBot.hpp"
#include "Bot/BotFactory/BotFactory.hpp"
#include "Bot/GreedyBot/GreedyBot.hpp"
#include "Bot/RandomBot/RandomBot.hpp"

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
