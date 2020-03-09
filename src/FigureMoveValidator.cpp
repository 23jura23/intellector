//
// Created by vsg on 28.02.2020.
//

#include "FigureMoveValidator.hpp"

[[noreturn]] static void terminator() {
    std::terminate();
}

int sgn(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
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
    if (!inBoard(to_pos)) return false;

    Position diff = pos_ - to_pos;
    if (!(diff.makeX() == diff.makeY() && abs(diff.makeX().z_) == 1) &&
        !(diff.makeX() == diff.makeZ() && abs(diff.makeX().y_) == 1) &&
        !(diff.makeY() == diff.makeZ() && abs(diff.makeY().x_) == 1))
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
        Position pos = pos_ + d;
        if (!inBoard(pos)) continue;

        if (!board_[pos].figure_.has_value())
            answer.push_back(std::make_shared<SimpleMove>(pos_, pos_ + d, figure_));
        else if (board_[pos].figure_->type_ == FigureType::DEFENSSOR &&
                 board_[pos].figure_->colour_ == figure_.colour_)
            answer.push_back(std::make_shared<SwapMove>(pos_, pos_ + d, figure_));
    }

    return answer;
}


DominatorMoveValidator::DominatorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::DOMINATOR) {}

bool DominatorMoveValidator::checkMove(Position to_pos) {
    if (!inBoard(to_pos)) return false;

    Position diff = pos_ - to_pos;
    Position path_to_pos(0, 0, 0);
    if (diff.makeX() == diff.makeY())
        path_to_pos = Position(0, 0, sgn(diff.makeX().z_));
    if (diff.makeX() == diff.makeZ())
        path_to_pos = Position(0, 0, sgn(diff.makeX().y_));
    if (diff.makeY() == diff.makeZ())
        path_to_pos = Position(0, 0, sgn(diff.makeY().x_));

    if (path_to_pos == Position(0, 0, 0))
        return false;

    Position i{};
    for (i = path_to_pos; i != diff; i += path_to_pos) {
        if (board_[to_pos].figure_.has_value())
            return false;
    }

    return !board_[to_pos].figure_.has_value() || board_[to_pos].figure_->colour_ != figure_.colour_;
}

std::vector<std::shared_ptr<SimpleMove>> DominatorMoveValidator::allMoves() {
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
        for (Position pos = pos_ + d;; pos += d) {

            if (!inBoard(pos)) break;
            if (board_[pos].figure_.has_value() && board_[pos].figure_->colour_ == figure_.colour_) break;

            answer.push_back(std::make_shared<SimpleMove>(pos_, pos, figure_));
            if (board_[pos].figure_.has_value() && board_[pos].figure_->colour_ != figure_.colour_) break;
        }
    }

    return answer;
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

bool DefenssorMoveValidator::checkMove(Position to_pos) {
    if (!inBoard(to_pos)) return false;

    Position diff = pos_ - to_pos;
    if (!(diff.makeX() == diff.makeY() && abs(diff.makeX().z_) == 1) &&
        !(diff.makeX() == diff.makeZ() && abs(diff.makeX().y_) == 1) &&
        !(diff.makeY() == diff.makeZ() && abs(diff.makeY().x_) == 1))
        return false;

    return !board_[to_pos].figure_.has_value() || board_[to_pos].figure_->colour_ != figure_.colour_;
}

std::vector<std::shared_ptr<SimpleMove>> DefenssorMoveValidator::allMoves() {
    std::vector<std::shared_ptr<SimpleMove>> answer;
    std::vector<Position> diff{
            {1,  0,  0},
            {-1, 0,  0},
            {0,  1,  0},
            {0,  -1, 0},
            {0,  0,  1},
            {0,  0,  -1},
    };

    for (auto d : diff) {
        Position pos = pos_ + d;
        if (!inBoard(pos)) continue;
        if (board_[pos].figure_.has_value() && board_[pos].figure_->colour_ == figure_.colour_) continue;

        answer.push_back(std::make_shared<SimpleMove>(pos_, pos, figure_));
    }

    return answer;
}


LiberatorMoveValidator::LiberatorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::LIBERATOR) {}

bool LiberatorMoveValidator::checkMove(Position to_pos) {
    if (!inBoard(to_pos)) return false;

    Position diff = pos_ - to_pos;
    if (!(diff.makeX() == diff.makeY() && abs(diff.makeX().z_) == 2) &&
        !(diff.makeX() == diff.makeZ() && abs(diff.makeX().y_) == 2) &&
        !(diff.makeY() == diff.makeZ() && abs(diff.makeY().x_) == 2))
        return false;

    return !board_[to_pos].figure_.has_value() || board_[to_pos].figure_->colour_ != figure_.colour_;
}

std::vector<std::shared_ptr<SimpleMove>> LiberatorMoveValidator::allMoves() {
    std::vector<std::shared_ptr<SimpleMove>> answer;
    std::vector<Position> diff{
            {2,  0,  0},
            {-2, 0,  0},
            {0,  2,  0},
            {0,  -2, 0},
            {0,  0,  2},
            {0,  0,  -2},
    };

    for (auto d : diff) {
        Position pos = pos_ + d;
        if (!inBoard(pos)) continue;
        if (board_[pos].figure_.has_value() && board_[pos].figure_->colour_ == figure_.colour_) continue;

        answer.push_back(std::make_shared<SimpleMove>(pos_, pos, figure_));
    }

    return answer;
}


ProgressorMoveValidator::ProgressorMoveValidator(Board& board, PlayerColour colour, Position pos)
        : FigureMoveValidator(board, colour, pos, FigureType::PROGRESSOR) {}

bool ProgressorMoveValidator::checkMove(Position to_pos) {
    if (!inBoard(to_pos)) return false;

    Position diff = pos_ - to_pos;
    if (figure_.colour_ == PlayerColour::white_) {
        if (!(diff.makeX() == diff.makeY() && diff.makeX().z_ == 1) &&
            !(diff.makeX() == diff.makeZ() && diff.makeX().y_ == 1) &&
            !(diff.makeY() == diff.makeZ() && diff.makeY().x_ == 1))
            return false;
    }
    else {
        if (!(diff.makeX() == diff.makeY() && diff.makeX().z_ == -1) &&
            !(diff.makeX() == diff.makeZ() && diff.makeX().y_ == -1) &&
            !(diff.makeY() == diff.makeZ() && diff.makeY().x_ == -1))
            return false;

    }

    return !board_[to_pos].figure_.has_value() || board_[to_pos].figure_->colour_ != figure_.colour_;
}

std::vector<std::shared_ptr<SimpleMove>> ProgressorMoveValidator::allMoves() {
    std::vector<std::shared_ptr<SimpleMove>> answer;
    std::vector<Position> diff{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
    };
    if (figure_.colour_ == PlayerColour::black_)
        for (auto& d : diff) {
            d = d * (-1);
        }

    for (auto d : diff) {
        Position pos = pos_ + d;
        if (!inBoard(pos)) continue;
        if (board_[pos].figure_.has_value() && board_[pos].figure_->colour_ == figure_.colour_) continue;

        if ((pos.posH() == 0 && pos.posW() % 2 == 1) || pos.posH() == Board::cols_ - 1) {
            answer.push_back(std::make_shared<TransformMove>(pos_, pos, figure_, FigureType::DEFENSSOR));
            answer.push_back(std::make_shared<TransformMove>(pos_, pos, figure_, FigureType::PROGRESSOR));
            answer.push_back(std::make_shared<TransformMove>(pos_, pos, figure_, FigureType::LIBERATOR));
            answer.push_back(std::make_shared<TransformMove>(pos_, pos, figure_, FigureType::AGGRESSOR));
            answer.push_back(std::make_shared<TransformMove>(pos_, pos, figure_, FigureType::DOMINATOR));
        }
        else
            answer.push_back(std::make_shared<SimpleMove>(pos_, pos, figure_));
    }

    return answer;
}
