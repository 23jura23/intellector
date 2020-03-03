//
// Created by vsg on 22.02.2020.
//

#include "Board.hpp"

Board::Board() {
    const std::vector<Triple> arrangement_{ // Надо именить на что-то нормальное
            {PlayerColour::white_, Position{0, 0}, FigureType::DOMINATOR},
            {PlayerColour::white_, Position{1, 0}, FigureType::LIBERATOR},
            {PlayerColour::white_, Position{2, 0}, FigureType::AGGRESSOR},
            {PlayerColour::white_, Position{3, 0}, FigureType::DEFENSSOR},
            {PlayerColour::white_, Position{4, 0}, FigureType::INTELLECTOR},
            {PlayerColour::white_, Position{5, 0}, FigureType::DEFENSSOR},
            {PlayerColour::white_, Position{6, 0}, FigureType::AGGRESSOR},
            {PlayerColour::white_, Position{7, 0}, FigureType::LIBERATOR},
            {PlayerColour::white_, Position{8, 0}, FigureType::DOMINATOR},

            {PlayerColour::white_, Position{0, 1}, FigureType::PROGRESSOR},
            {PlayerColour::white_, Position{2, 1}, FigureType::PROGRESSOR},
            {PlayerColour::white_, Position{4, 1}, FigureType::PROGRESSOR},
            {PlayerColour::white_, Position{6, 1}, FigureType::PROGRESSOR},
            {PlayerColour::white_, Position{8, 1}, FigureType::PROGRESSOR},


            {PlayerColour::black_, Position{0, 6}, FigureType::DOMINATOR},
            {PlayerColour::black_, Position{1, 5}, FigureType::LIBERATOR},
            {PlayerColour::black_, Position{2, 6}, FigureType::AGGRESSOR},
            {PlayerColour::black_, Position{3, 5}, FigureType::DEFENSSOR},
            {PlayerColour::black_, Position{4, 6}, FigureType::INTELLECTOR},
            {PlayerColour::black_, Position{5, 5}, FigureType::DEFENSSOR},
            {PlayerColour::black_, Position{6, 6}, FigureType::AGGRESSOR},
            {PlayerColour::black_, Position{7, 5}, FigureType::LIBERATOR},
            {PlayerColour::black_, Position{8, 6}, FigureType::DOMINATOR},

            {PlayerColour::black_, Position{0, 5}, FigureType::PROGRESSOR},
            {PlayerColour::black_, Position{2, 5}, FigureType::PROGRESSOR},
            {PlayerColour::black_, Position{4, 5}, FigureType::PROGRESSOR},
            {PlayerColour::black_, Position{6, 5}, FigureType::PROGRESSOR},
            {PlayerColour::black_, Position{8, 5}, FigureType::PROGRESSOR},
    };
    data_.resize(cols_);
    for (int w = 0; w < cols_; ++w)
        for (int h = 0; h < rows_ - w % 2; ++h)
            data_[w].emplace_back(Position(w, h));

    for (auto new_figure : arrangement_) {
        Position pos = new_figure.pos_;
        (*this)[pos] = Cell(new_figure);
    }
}

Board::Board(const Board &other) {
    if (&other == this)
        return;

    for (int w = 0; w < cols_; ++w) {
        for (int h = 0; h < rows_ - w % 2; ++h) {
            if (other.data_[w][h].figure_ == nullptr)
                data_[w].emplace_back(Position(w, h));
            else {
                Triple new_figure = other.data_[w][h].figure_->getTriple();
                data_[w].emplace_back(new_figure);
            }
        }
    }
}

bool Board::move(Position of_pos, Position to_pos, PlayerColour turn) {
    if ((*this)[of_pos].figure_->getColor() != turn ||
        !(*this)[of_pos].figure_->checkMove(*this, to_pos))
        return false;

    if ((*this)[of_pos].figure_->getType() == FigureType::INTELLECTOR &&
        (*this)[to_pos].figure_->getType() == FigureType::DEFENSSOR) {

        Triple figure_intellector = (*this)[of_pos].figure_->getTriple();
        Triple figure_defenssor = (*this)[to_pos].figure_->getTriple();

        figure_intellector.pos_ = to_pos, figure_defenssor.pos_ = of_pos;
        (*this)[of_pos] = Cell(figure_defenssor);
        (*this)[to_pos] = Cell(figure_intellector);
        return true;
    }
    Triple figure = (*this)[of_pos].figure_->getTriple();
    figure.pos_ = to_pos;

    (*this)[to_pos] = Cell(figure);
    (*this)[of_pos] = Cell(of_pos);
    return true; // TODO случай с пешкой
}

const std::vector<std::vector<Cell>> &Board::getBoard() const {
    return data_;
}

const Cell &Board::getCell(Position pos) const {
    return data_[pos.posW()][pos.posH()];
}

Cell &Board::operator[](Position pos) {
    return data_[pos.posW()][pos.posH()];
}
