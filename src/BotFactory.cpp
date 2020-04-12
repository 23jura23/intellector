
#include <memory>

#include "BotFactory.hpp"
#include "RandomBot.hpp"
#include "AlphaBetaBot.hpp"
#include "GreedyBot.hpp"
#include "Evaluate.hpp"


std::shared_ptr<Bot> BotFactory(const GameSettings &settings) {
    // void(settings.difficulty());
    int difficulty = settings.difficulty();
    std::shared_ptr<Bot> bot;
    switch(difficulty)
    {
        case 0:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
            break;
        case 1:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<GreedyBot>(evaluate::scoreSumFigurePoints));
            break;
        default:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<AlphaBetaBot>(6, 0));
    }
    return bot;
}
