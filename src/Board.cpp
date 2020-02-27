//
// Created by vsg on 22.02.2020.
//

#include "Board.hpp"

std::vector<triple> arrangement_ = {
        {Figure::DOMINATOR, cell{0,0}, white_},
        {Figure::LIERATOR, cell{1,0}, white_},
        {Figure::AGGRESSOR, cell{2,0}, white_},
        {Figure::DEFENSSOR, cell{3,0}, white_},
        {Figure::INTELLECTOR, cell{4,0}, white_},
        {Figure::DEFENSSOR, cell{5,0}, white_},
        {Figure::AGGRESSOR, cell{6,0}, white_},
        {Figure::LIERATOR, cell{7,0}, white_},
        {Figure::DOMINATOR, cell{8,0}, white_},

        {Figure::PROGRESSOR, cell{0,1}, white_},
        {Figure::PROGRESSOR, cell{2,1}, white_},
        {Figure::PROGRESSOR, cell{4,1}, white_},
        {Figure::PROGRESSOR, cell{6,1}, white_},
        {Figure::PROGRESSOR, cell{8,1}, white_},


        {Figure::DOMINATOR, cell{0,6}, black_},
        {Figure::LIERATOR, cell{1,5}, black_},
        {Figure::AGGRESSOR, cell{2,6}, black_},
        {Figure::DEFENSSOR, cell{3,5}, black_},
        {Figure::INTELLECTOR, cell{4,6}, black_},
        {Figure::DEFENSSOR, cell{5,5}, black_},
        {Figure::AGGRESSOR, cell{6,6}, black_},
        {Figure::LIERATOR, cell{7,5}, black_},
        {Figure::DOMINATOR, cell{8,6}, black_},


        {Figure::PROGRESSOR, cell{0,5}, black_},
        {Figure::PROGRESSOR, cell{2,5}, black_},
        {Figure::PROGRESSOR, cell{4,5}, black_},
        {Figure::PROGRESSOR, cell{6,5}, black_},
        {Figure::PROGRESSOR, cell{8,5}, black_}
};

board::board() {
    data_.resize(cols_);
    for (int w = 0; w < cols_; ++w)
        data_[w].assign(rows_ - w % 2, nullptr);
}