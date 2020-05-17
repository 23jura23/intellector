//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_BOARD_HPP
#define _PROJECT_BOARD_HPP

#include <vector>

#include "Cell.hpp"
#include "Figure.hpp"
#include "Position.hpp"

#pragma pack(push, 1)

class Board {
   public:
    Board();
    ~Board() = default;
    Board& operator=(const Board& other) {
        std::vector<std::vector<Cell>> data(other.data_);
        swap(data_, data);
        return *this;
    }
    Board(const Board& other);
    explicit Board(const std::vector<std::pair<Figure, Position>>& mas);

    [[nodiscard]] const Cell& operator[](Position pos) const;
    [[nodiscard]] Cell& operator[](Position pos);

    std::vector<std::vector<Cell>> data_;
    static constexpr int cols_ = 9, rows_ = 7;  // ширина и высота

    [[nodiscard]] bool inline operator==(const Board& other) const {
        return data_ == other.data_;
    }
};

#pragma pack(pop)

[[nodiscard]] inline bool inBoard(Position pos) {
    return (pos.posH() >= 0 && pos.posW() >= 0 && pos.posH() < Board::rows_ - pos.posW() % 2 &&
            pos.posW() < Board::cols_);
}

#endif  //_PROJECT_BOARD_HPP
