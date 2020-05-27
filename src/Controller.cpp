//
// Created by vsg on 22.02.2020.
//

#include "Controller.hpp"

#include <assert.h>

Controller::Controller(std::shared_ptr<Game> game)
        : game_{game} {
}

void Controller::makeMove(const Move& move) {
    game_->makeMove(move);
}

bool Controller::makeBotMove(PlayerColour color) {
    if (color == PlayerColour::white_) {
        return game_->makeWhiteBotMove();
    } else if (color == PlayerColour::black_) {
        return game_->makeBlackBotMove();
    } else {
        assert(false);
    }
}

void Controller::cancelMove() {
    game_->cancelMove();
}

void Controller::nextMove() {
    game_->nextMove();
}

void Controller::prevMove() {
    game_->prevMove();
}

GameStatus Controller::getGameStatus() {
    return game_->getGameStatus();
}

void Controller::updateAll() {
    // TODO auto choice which to update (only instanced!)
    updateViewModel<viewCurses::ViewGameMenuCurses>();
}

PlayerColour Controller::getCurrentPlayer() const {
    return game_->getColourCurrentPlayer();
}
