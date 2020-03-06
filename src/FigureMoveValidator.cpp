//
// Created by vsg on 28.02.2020.
//

#include "FigureMoveValidator.hpp"

[[noreturn]] static void terminator() {
    std::terminate();
}

FigureMoveValidator::FigureMoveValidator(Board& board, PlayerColour colour, Position pos, FigureType type)
        : board_(board), figure_(Figure(colour, type)), pos_(pos) {}

std::shared_ptr<FigureMoveValidator> FigureMoveValidator::create(Board& board, Figure figure, Position pos) {
    PlayerColour colour = figure.colour_;
    switch (figure.type_) {
        case FigureType::INTELLECTOR :
            return std::make_unique<IntellectorMoveValidator>(board, colour, pos);

        case FigureType::DOMINATOR :
            return std::make_unique<DominatorMoveValidator>(board, colour, pos);

        case FigureType::AGGRESSOR :
            return std::make_unique<AggressorMoveValidator>(board, colour, pos);

        case FigureType::DEFENSSOR :
            return std::make_unique<DefenssorMoveValidator>(board, colour, pos);

        case FigureType::LIBERATOR :
            return std::make_unique<LiberatorMoveValidator>(board, colour, pos);

        case FigureType::PROGRESSOR :
            return std::make_unique<ProgressorMoveValidator>(board, colour, pos);
    }
    terminator();
}


IntellectorMoveValidator::IntellectorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::INTELLECTOR) {}

bool IntellectorMoveValidator::checkMove(Position to_pos) {
    Position diff = pos_ - to_pos;
    if (!(diff.makeX() == diff.makeY() && abs(diff.makeX().z_) == 1) &&
        !(diff.makeX() == diff.makeZ() && abs(diff.makeX().y_) == 1) &&
        !(diff.makeY() == diff.makeZ() && abs(diff.makeX().x_) == 1))
        return false;

    if (!board_[to_pos].figure_.has_value())
        return true;

    return (board_[to_pos].figure_->type_ == FigureType::DEFENSSOR &&
            board_[to_pos].figure_->colour_ == figure_.colour_);
}

std::vector<std::shared_ptr<SimpleMove>> IntellectorMoveValidator::allMoves() {
    std::vector<std::shared_ptr<SimpleMove>> answer;
    std::vector<Position> diff{
            {1,  0,  0},
            {-1, 0,  0},
            {0,  1,  0},
            {0,  -1, 0},
            {0,  0,  1},
            {0,  0,  -1}
    };

    for (auto d : diff) {
        if (!board_[pos_ + d].figure_.has_value())
            answer.push_back(std::make_shared<SimpleMove>(pos_, pos_ + d, figure_));
        else if (board_[pos_ + d].figure_->type_ == FigureType::DEFENSSOR)
            answer.push_back(std::make_shared<SwapMove>(pos_, pos_ + d, figure_));
    }

    return answer;
}


DominatorMoveValidator::DominatorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::DOMINATOR) {}

bool DominatorMoveValidator::checkMove(Position move) {
    return false; // TODO
}

std::vector<std::shared_ptr<SimpleMove>> DominatorMoveValidator::allMoves() {
    return std::vector<std::shared_ptr<SimpleMove>>{}; // TODO
}


AggressorMoveValidator::AggressorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::AGGRESSOR) {}

bool AggressorMoveValidator::checkMove(Position move) {
    return false; // TODO
}

std::vector<std::shared_ptr<SimpleMove>> AggressorMoveValidator::allMoves() {
    return std::vector<std::shared_ptr<SimpleMove>>{}; // TODO
}


DefenssorMoveValidator::DefenssorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::DEFENSSOR) {}

bool DefenssorMoveValidator::checkMove(Position move) {
    return false; // TODO
}

std::vector<std::shared_ptr<SimpleMove>> DefenssorMoveValidator::allMoves() {
    return std::vector<std::shared_ptr<SimpleMove>>{}; // TODO
}


LiberatorMoveValidator::LiberatorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::LIBERATOR) {}

bool LiberatorMoveValidator::checkMove(Position move) {
    return false; // TODO
}

std::vector<std::shared_ptr<SimpleMove>> LiberatorMoveValidator::allMoves() {
    return std::vector<std::shared_ptr<SimpleMove>>{}; // TODO
}


ProgressorMoveValidator::ProgressorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::PROGRESSOR) {}

bool ProgressorMoveValidator::checkMove(Position move) {
    return false; // TODO
}

std::vector<std::shared_ptr<SimpleMove>> ProgressorMoveValidator::allMoves() {
    return std::vector<std::shared_ptr<SimpleMove>>{}; // TODO
}
