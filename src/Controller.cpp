//
// Created by vsg on 04.03.2020.
//

#include "Controller.hpp"

bool Controller::makeMove(Position of_pos, Position to_pos, PlayerColour turn) { // TODO отметить в клетках, что я сдклал ход
    if (!board_[of_pos].figure_.has_value() ||
        board_[of_pos].figure_->colour_ != turn)
        return false;

    std::unique_ptr<FigureMove> figure = FigureMove::create(board_, board_[of_pos].figure_.value(), of_pos);

    if (!figure->checkMove(to_pos))
        return false;

    if (board_[of_pos].figure_->type_ == FigureType::INTELLECTOR &&
        board_[to_pos].figure_.has_value() &&
        board_[to_pos].figure_->type_ == FigureType::DEFENSSOR) {

//        board_[of_pos].figure_.swap(board_[to_pos].figure_);
        return true;
    }

    Figure figure_of = board_[of_pos].figure_.value();
    board_[to_pos] = Cell(figure_of, to_pos);
    board_[of_pos] = Cell(of_pos);
    return true; // TODO случай с пешкой
}

std::vector<Position> Controller::allFigureMoves(Position pos, PlayerColour turn) {
    if (!board_[pos].figure_.has_value() ||
        board_[pos].figure_->colour_ != turn)
        return std::vector<Position>{};

    std::unique_ptr<FigureMove> figure = FigureMove::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}
