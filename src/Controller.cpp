//
// Created by vsg on 22.02.2020.
//

#include "Controller.hpp"

Controller::Controller(std::shared_ptr<Game> game)
    : game_{game} {
}

void Controller::makeMove(const SimpleMove& move) {
    game_->makeMove(move);
}

void Controller::updateAll() {
    // TODO auto choice which to update (only instanced!)
    updateViewModel<ViewCurses::viewCurses>();
}

PlayerColour Controller::getCurrentPlayer() const {
    return game_->getColourCurrentPlayer();
}
