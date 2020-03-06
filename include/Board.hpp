//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_BOARD_HPP
#define _PROJECT_BOARD_HPP

#include <vector>
#include "Figure.hpp"
#include "Cell.hpp"
#include "Position.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    Board& operator=(const Board&) = default;
    Board(const Board& other);

    [[nodiscard]] const Cell& operator[](Position pos) const;
    [[nodiscard]] Cell& operator[](Position pos);

    std::vector<std::vector<Cell>> data_;
    static constexpr int cols_ = 9, rows_ = 7; // ширина и высота
};

[[nodiscard]] inline bool inBoard(Position pos) {
    return (pos.posH() >= 0 && pos.posW() >= 0 &&
            pos.posH() < Board::cols_ - pos.posW() % 2 && pos.posW() < Board::rows_);
}

#endif //_PROJECT_BOARD_HPP
