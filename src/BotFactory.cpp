
#include <memory>

#include "BotFactory.hpp"
#include "RandomBot.hpp"
#include "AlphaBetaBot.hpp"
std::shared_ptr<Bot> BotFactory(const GameSettings &settings) {
    // void(settings.difficulty());
    int difficulty = settings.difficulty();
    std::shared_ptr<Bot> bot;
    if(difficulty == 0)
    	bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
    else 
    	bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<AlphaBetaBot>(6, evaluate::scoreSumFigurePoints));
    return bot;
}
