//
// Created by vsg on 28.02.2020.
//

#include "FigureMove.hpp"

[[noreturn]] static void terminator() {
    std::terminate();
}

FigureMove::FigureMove(Board &board, PlayerColour colour, Position pos, FigureType type)
        : board_(board), colour_(colour), pos_(pos), type_(type) {}

std::unique_ptr<FigureMove> FigureMove::create(Board &board, Figure figure, Position pos) {
    PlayerColour colour = figure.colour_;
    switch (figure.type_) {
        case FigureType::INTELLECTOR :
            return std::make_unique<FigureMoveIntellector>(board, colour, pos);

        case FigureType::DOMINATOR :
            return std::make_unique<FigureMoveDominator>(board, colour, pos);

        case FigureType::AGGRESSOR :
            return std::make_unique<FigureMoveAggressor>(board, colour, pos);

        case FigureType::DEFENSSOR :
            return std::make_unique<FigureMoveDefenssor>(board, colour, pos);

        case FigureType::LIBERATOR :
            return std::make_unique<FigureMoveLiberator>(board, colour, pos);

        case FigureType::PROGRESSOR :
            return std::make_unique<FigureMoveProgressor>(board, colour, pos);
    }
    terminator();
}


FigureMoveIntellector::FigureMoveIntellector(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::INTELLECTOR) {}

bool FigureMoveIntellector::checkMove(Position to_pos) {
    if (abs(pos_ - to_pos) != 1)
        return false;

    if (!board_[to_pos].figure_.has_value())
        return true;

    return (board_[to_pos].figure_->type_ == FigureType::DEFENSSOR &&
            board_[to_pos].figure_->colour_ == colour_);
}

const std::vector<Position> FigureMoveIntellector::allMoves() {
    return std::vector<Position>{}; // TODO
}


FigureMoveDominator::FigureMoveDominator(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::DOMINATOR) {}

bool FigureMoveDominator::checkMove(Position to_pos) {
    return false; // TODO
}
const std::vector<Position> FigureMoveDominator::allMoves() {
    return std::vector<Position>{}; // TODO
}


FigureMoveAggressor::FigureMoveAggressor(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::AGGRESSOR) {}

bool FigureMoveAggressor::checkMove(Position to_pos) {
    return false; // TODO
}

const std::vector<Position> FigureMoveAggressor::allMoves() {
    return std::vector<Position>{}; // TODO
}


FigureMoveDefenssor::FigureMoveDefenssor(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::DEFENSSOR) {}

bool FigureMoveDefenssor::checkMove(Position to_pos) {
    return false; // TODO
}

const std::vector<Position> FigureMoveDefenssor::allMoves() {
    return std::vector<Position>{}; // TODO
}


FigureMoveLiberator::FigureMoveLiberator(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::LIBERATOR) {}

bool FigureMoveLiberator::checkMove(Position to_pos) {
    return false; // TODO
}

const std::vector<Position> FigureMoveLiberator::allMoves() {
    return std::vector<Position>{}; // TODO
}


FigureMoveProgressor::FigureMoveProgressor(Board &board, PlayerColour colour, Position pos)
        : FigureMove(board, colour, pos, FigureType::PROGRESSOR) {}

bool FigureMoveProgressor::checkMove(Position to_pos) {
    return false; // TODO
}

const std::vector<Position> FigureMoveProgressor::allMoves() {
    return std::vector<Position>{}; // TODO
}
