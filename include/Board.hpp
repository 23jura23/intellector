//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_BOARD_HPP
#define _PROJECT_BOARD_HPP

#include <vector>
#include <memory>
#include "Types.hpp"
#include "Figure.hpp"
#include "Cell.hpp"

class Board {
public: // Функции доски-------------------------------------------------------------------------
    Board();
    ~Board() = default;
    Board& operator= (const Board&) = default;
    Board(const Board& other);


    bool move(Cell of_pos, Cell to_pos, PlayerColour turn_);
    const std::vector<std::vector<std::unique_ptr<Figure>>>& getBoard() {return data_; } // Спросить что за подсказка


private: // Поля доски----------------------------------------------------------------------------
    std::vector<std::vector<std::unique_ptr<Figure>>> data_;
//    std::vector<const figure*> all_white_figures_;
//    std::vector<const figure*> all_black_figures_;
    static constexpr int cols_ = 9, rows_ = 7; // ширина и высота
};

#endif //_PROJECT_BOARD_HPP
