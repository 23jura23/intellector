//
// Created by vsg on 06.03.2020.
//

#include "MoveTypes.hpp"

//std::shared_ptr<SimpleMove> SimpleMove::create(const Cell& from_cell,
//                                               const Cell& to_cell,
//                                               PlayerColour turn) {
//    if (!from_cell.figure_.has_value() || from_cell.figure_->colour_ != turn)
//        return nullptr;
//
//    Position from = from_cell.pos_, to = to_cell.pos_;
//
//    if (!inBoard(from) || !inBoard(to))
//        return nullptr;
//
//
//    if (from_cell.figure_.value().type_ == FigureType::INTELLECTOR &&           // Рокировка
//        to_cell.figure_.has_value() &&
//        to_cell.figure_.value().type_ == FigureType::DEFENSSOR &&
//        from_cell.figure_.value().colour_ == from_cell.figure_.value().colour_)
//        return std::make_shared<SwapMove>(from_cell, to_cell, turn);
//
//
//    if (to_cell.figure_.has_value() &&                                          // Если они одного цвета, то невозможно
//        from_cell.figure_.value().colour_ == from_cell.figure_.value().colour_)
//        return nullptr;
//
//
//    if (from_cell.figure_.value().type_ == FigureType::PROGRESSOR &&            // Если это пешка и она доходит до конца
//        ((to_cell.pos_.posH() == 0 && to_cell.pos_.posW() % 2 == 1) ||
//         (to_cell.pos_.posH() == Board::cols_ - 1 && to_cell.pos_.posW() == Board::rows_ - 1)))
//        return std::make_shared<TransformMove>(from_cell, to_cell, turn);
//
//
//    return std::make_shared<SimpleMove>(from_cell, to_cell, turn);
//}
