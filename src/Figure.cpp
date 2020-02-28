//
// Created by vsg on 28.02.2020.
//

#include "Figure.hpp"

//std::optional<Board> Figure::makeMove(const Board &board_, Cell to_pos_) {
////    if (checkMove(board_, to_pos_))
////        return static_cast<board>(board_);
////    else
//    return {};
//
//}

std::unique_ptr<Figure> Figure::create(Triple new_figure) {
    Cell pos = new_figure.pos_;
    FigureType type = new_figure.type_;
    PlayerColour colour = new_figure.colour_;

    switch (type) {
        case FigureType::INTELLECTOR :
            return std::make_unique<FigureIntellector>(pos, colour);

        case FigureType::DOMINATOR :
            return std::make_unique<FigureDominator>(pos, colour);

        case FigureType::AGGRESSOR :
            return std::make_unique<FigureAggressor>(pos, colour);

        case FigureType::DEFENSSOR :
            return std::make_unique<FigureDefenssor>(pos, colour);

        case FigureType::LIERATOR :
            return std::make_unique<FigureLiberator>(pos, colour);

        case FigureType::PROGRESSOR :
            return std::make_unique<FigureProgressor>(pos, colour);

        case FigureType::NONE :
            return std::make_unique<Figure>(pos, colour);
    }
}

bool Figure::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> Figure::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureIntellector::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureIntellector::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureDominator::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureDominator::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureAggressor::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureAggressor::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureDefenssor::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureDefenssor::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureLiberator::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureLiberator::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}


bool FigureProgressor::checkMove(const Board &board_, Cell to_pos_) {
    return false; // TODO
}

std::vector<Cell> FigureProgressor::allMoves(const Board &board_) {
    return std::vector<Cell>{}; // TODO
}