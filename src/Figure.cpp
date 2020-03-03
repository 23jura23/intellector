//
// Created by vsg on 28.02.2020.
//

#include "Figure.hpp"

[[noreturn]] static void terminator() {
    std::terminate();
}

Triple::Triple(PlayerColour colour, Position pos, FigureType type)
        : colour_(colour), pos_(pos), type_(type) {}

Figure::Figure(PlayerColour colour, Position pos, FigureType type)
        : colour_(colour), pos_(pos), type_(type) {}

PlayerColour Figure::getColor() const { return colour_; }

Position Figure::getPos() const { return pos_; }

FigureType Figure::getType() const { return type_; }

Triple Figure::getTriple() const { return Triple(colour_, pos_, type_); }

std::unique_ptr<Figure> Figure::create(Triple new_figure) {
    Position pos = new_figure.pos_;
    FigureType type = new_figure.type_;
    PlayerColour colour = new_figure.colour_;

    switch (type) {
        case FigureType::INTELLECTOR :
            return std::make_unique<FigureIntellector>(colour, pos);

        case FigureType::DOMINATOR :
            return std::make_unique<FigureDominator>(colour, pos);

        case FigureType::AGGRESSOR :
            return std::make_unique<FigureAggressor>(colour, pos);

        case FigureType::DEFENSSOR :
            return std::make_unique<FigureDefenssor>(colour, pos);

        case FigureType::LIBERATOR :
            return std::make_unique<FigureLiberator>(colour, pos);

        case FigureType::PROGRESSOR :
            return std::make_unique<FigureProgressor>(colour, pos);
//
//        case FigureType::NONE :
//            return std::make_unique<Figure>(colour, pos);
    }
    terminator();
}


FigureIntellector::FigureIntellector(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::INTELLECTOR) {}

bool FigureIntellector::checkMove(const Board &board, Position to_pos) {
//    if (abs(pos_ - to_pos) == 1 &&
//        (board.getCell(to_pos).figure_ == nullptr))
//        return true;
//    return abs(pos_ - to_pos) == 1 &&
//           (board.getCell(to_pos).figure_->getType() == FigureType::DEFENSSOR &&
//            board.getCell(to_pos).figure_->getColor() == colour_);
return false;
}

std::vector<Position> FigureIntellector::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}


FigureDominator::FigureDominator(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::DOMINATOR) {};

bool FigureDominator::checkMove(const Board &board, Position to_pos) {
    return false; // TODO
}

std::vector<Position> FigureDominator::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}


FigureAggressor::FigureAggressor(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::AGGRESSOR) {};

bool FigureAggressor::checkMove(const Board &board, Position to_pos) {
    return false; // TODO
}

std::vector<Position> FigureAggressor::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}


FigureDefenssor::FigureDefenssor(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::DEFENSSOR) {};

bool FigureDefenssor::checkMove(const Board &board, Position to_pos) {
    return false; // TODO
}

std::vector<Position> FigureDefenssor::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}


FigureLiberator::FigureLiberator(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::LIBERATOR) {};

bool FigureLiberator::checkMove(const Board &board, Position to_pos) {
    return false; // TODO
}

std::vector<Position> FigureLiberator::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}


FigureProgressor::FigureProgressor(PlayerColour colour, Position pos)
        : Figure(colour, pos, FigureType::PROGRESSOR) {};

bool FigureProgressor::checkMove(const Board &board, Position to_pos) {
    return false; // TODO
}

std::vector<Position> FigureProgressor::allMoves(const Board &board) {
    return std::vector<Position>{}; // TODO
}
