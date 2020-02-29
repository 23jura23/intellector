//
// Created by vsg on 22.02.2020.
//

#include "Board.hpp"

Board::Board() {
    const std::vector<Triple> arrangement_{ // Надо именить на что-то нормальное
            {PlayerColour::white_, Cell{0, 0}, FigureType::DOMINATOR  },
            {PlayerColour::white_, Cell{1, 0}, FigureType::LIBERATOR   },
            {PlayerColour::white_, Cell{2, 0}, FigureType::AGGRESSOR  },
            {PlayerColour::white_, Cell{3, 0}, FigureType::DEFENSSOR  },
            {PlayerColour::white_, Cell{4, 0}, FigureType::INTELLECTOR},
            {PlayerColour::white_, Cell{5, 0}, FigureType::DEFENSSOR  },
            {PlayerColour::white_, Cell{6, 0}, FigureType::AGGRESSOR  },
            {PlayerColour::white_, Cell{7, 0}, FigureType::LIBERATOR   },
            {PlayerColour::white_, Cell{8, 0}, FigureType::DOMINATOR  },

            {PlayerColour::white_, Cell{0, 1}, FigureType::PROGRESSOR },
            {PlayerColour::white_, Cell{2, 1}, FigureType::PROGRESSOR },
            {PlayerColour::white_, Cell{4, 1}, FigureType::PROGRESSOR },
            {PlayerColour::white_, Cell{6, 1}, FigureType::PROGRESSOR },
            {PlayerColour::white_, Cell{8, 1}, FigureType::PROGRESSOR },


            {PlayerColour::black_, Cell{0, 6}, FigureType::DOMINATOR  },
            {PlayerColour::black_, Cell{1, 5}, FigureType::LIBERATOR   },
            {PlayerColour::black_, Cell{2, 6}, FigureType::AGGRESSOR  },
            {PlayerColour::black_, Cell{3, 5}, FigureType::DEFENSSOR  },
            {PlayerColour::black_, Cell{4, 6}, FigureType::INTELLECTOR},
            {PlayerColour::black_, Cell{5, 5}, FigureType::DEFENSSOR  },
            {PlayerColour::black_, Cell{6, 6}, FigureType::AGGRESSOR  },
            {PlayerColour::black_, Cell{7, 5}, FigureType::LIBERATOR   },
            {PlayerColour::black_, Cell{8, 6}, FigureType::DOMINATOR  },

            {PlayerColour::black_, Cell{0, 5}, FigureType::PROGRESSOR },
            {PlayerColour::black_, Cell{2, 5}, FigureType::PROGRESSOR },
            {PlayerColour::black_, Cell{4, 5}, FigureType::PROGRESSOR },
            {PlayerColour::black_, Cell{6, 5}, FigureType::PROGRESSOR },
            {PlayerColour::black_, Cell{8, 5}, FigureType::PROGRESSOR },
    };
    data_.resize(cols_);
    for (int w = 0; w < cols_; ++w)
        data_[w].resize(rows_ - w % 2);

    for (auto new_figure : arrangement_) {
        Cell pos = new_figure.pos_;
        data_[pos.posW()][pos.powH()] = Figure::create(new_figure);
    }

    for (int w = 0;w < cols_; ++w)
        for (int h = 0;h < data_[w].size();++h)
            if (!data_[w][h])
                data_[w][h] = Figure::create({PlayerColour::white_, Cell{w,h}, FigureType::NONE});
}

Board::Board(const Board &other) {
    if (&other == this)
        return;

    data_.resize(cols_);
    for (int w = 0; w < cols_; ++w) {
        data_[w].resize(rows_ - w % 2);
        for (unsigned int h = 0; h < data_[w].size(); ++h) {
            Triple new_figure = other.data_[w][h].get()->getTriple();
            data_[w][h] = Figure::create(new_figure);

        }
    }
}

bool Board::move(Cell of_pos, Cell to_pos, PlayerColour turn) {
    return false; // TODO
}

