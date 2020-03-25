//
// Created by vsg on 22.02.2020.
//

#include "Board.hpp"

Board::Board() {
    const std::vector<std::pair<Figure, Position>> arrangement_{
            {Figure{PlayerColour::white_, FigureType::DOMINATOR},   Position{0, 0}},
            {Figure{PlayerColour::white_, FigureType::LIBERATOR},   Position{1, 0}},
            {Figure{PlayerColour::white_, FigureType::AGGRESSOR},   Position{2, 0}},
            {Figure{PlayerColour::white_, FigureType::DEFENSSOR},   Position{3, 0}},
            {Figure{PlayerColour::white_, FigureType::INTELLECTOR}, Position{4, 0}},
            {Figure{PlayerColour::white_, FigureType::DEFENSSOR},   Position{5, 0}},
            {Figure{PlayerColour::white_, FigureType::AGGRESSOR},   Position{6, 0}},
            {Figure{PlayerColour::white_, FigureType::LIBERATOR},   Position{7, 0}},
            {Figure{PlayerColour::white_, FigureType::DOMINATOR},   Position{8, 0}},

            {Figure{PlayerColour::white_, FigureType::PROGRESSOR},  Position{0, 1}},
            {Figure{PlayerColour::white_, FigureType::PROGRESSOR},  Position{2, 1}},
            {Figure{PlayerColour::white_, FigureType::PROGRESSOR},  Position{4, 1}},
            {Figure{PlayerColour::white_, FigureType::PROGRESSOR},  Position{6, 1}},
            {Figure{PlayerColour::white_, FigureType::PROGRESSOR},  Position{8, 1}},


            {Figure{PlayerColour::black_, FigureType::DOMINATOR},   Position{0, 6}},
            {Figure{PlayerColour::black_, FigureType::LIBERATOR},   Position{1, 5}},
            {Figure{PlayerColour::black_, FigureType::AGGRESSOR},   Position{2, 6}},
            {Figure{PlayerColour::black_, FigureType::DEFENSSOR},   Position{3, 5}},
            {Figure{PlayerColour::black_, FigureType::INTELLECTOR}, Position{4, 6}},
            {Figure{PlayerColour::black_, FigureType::DEFENSSOR},   Position{5, 5}},
            {Figure{PlayerColour::black_, FigureType::AGGRESSOR},   Position{6, 6}},
            {Figure{PlayerColour::black_, FigureType::LIBERATOR},   Position{7, 5}},
            {Figure{PlayerColour::black_, FigureType::DOMINATOR},   Position{8, 6}},

            {Figure{PlayerColour::black_, FigureType::PROGRESSOR},  Position{0, 5}},
            {Figure{PlayerColour::black_, FigureType::PROGRESSOR},  Position{2, 5}},
            {Figure{PlayerColour::black_, FigureType::PROGRESSOR},  Position{4, 5}},
            {Figure{PlayerColour::black_, FigureType::PROGRESSOR},  Position{6, 5}},
            {Figure{PlayerColour::black_, FigureType::PROGRESSOR},  Position{8, 5}},
    };
    data_.resize(cols_);
    for (int w = 0; w < cols_; ++w)
        for (int h = 0; h < rows_ - w % 2; ++h)
            data_[w].emplace_back(Position(w, h));

    for (auto new_cell : arrangement_) {
        (*this)[new_cell.second].figure_.emplace(new_cell.first);
    }
}

Board::Board(const Board& other) {
    if (&other == this)
        return;

    for (int w = 0; w < cols_; ++w) {
        for (int h = 0; h < rows_ - w % 2; ++h) {
            if (!other.data_[w][h].figure_.has_value())
                data_[w].emplace_back(Position(w, h));
            else {
                data_[w].emplace_back(Position(w, h), other.data_[w][h].figure_.value());
            }
        }
    }
}

const Cell& Board::operator[](Position pos) const {
    return data_[pos.posW()][pos.posH()];
}

Cell& Board::operator[](Position pos) {
    return data_[pos.posW()][pos.posH()];
}
