
#include "BotFactory.hpp"

#include <memory>
#include <atomic>

#include "AlphaBetaBot.hpp"
#include "Evaluate.hpp"
#include "GreedyBot.hpp"
#include "OptimizedAlphaBetaBot.hpp"
#include "RandomBot.hpp"

std::shared_ptr<Bot> BotFactory(int difficulty) {
    std::shared_ptr<Bot> bot;
    switch (difficulty) {
        case 0:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
            break;
        case 1:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<GreedyBot>(evaluate::scoreSumFigurePoints));
            break;
        default:
            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(difficulty+1, 0));
//            break;
//        case 6:
//            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(4, 0));
//            break;
//        case 10:
//            bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<OptimizedAlphaBetaBot>(5, 0));
//            break;
//        default:
//            assert(false);
    }
    return bot;
}
