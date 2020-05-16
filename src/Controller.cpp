//
// Created by vsg on 22.02.2020.
//

#include "Controller.hpp"

Controller::Controller(std::shared_ptr<Game> game)
        : game_{game} {
}

void Controller::makeMove(const Move& move) {
    game_->makeMove(move);
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
    updateViewModel<viewCurses::ViewCurses>();
}

PlayerColour Controller::getCurrentPlayer() const {
    return game_->getColourCurrentPlayer();
}
