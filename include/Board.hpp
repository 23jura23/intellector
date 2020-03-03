//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_BOARD_HPP
#define _PROJECT_BOARD_HPP

#include <vector>
#include <memory>
#include "Figure.hpp"
#include "Cell.hpp"
#include "Position.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    Board &operator=(const Board &) = default;
    Board(const Board &other);

    bool move(Position of_pos, Position to_pos, PlayerColour turn);

    [[nodiscard]] const std::vector<std::vector<Cell>> &getBoard() const;

    [[nodiscard]] const Cell &getCell(Position pos) const;

private:
    Cell &operator[](Position pos);

    std::vector<std::vector<Cell>> data_;
    static constexpr int cols_ = 9, rows_ = 7; // ширина и высота
};

#endif //_PROJECT_BOARD_HPP
