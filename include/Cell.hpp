//
// Created by vsg on 22.02.2020.
//

#ifndef PROJECT_CELL_HPP
#define PROJECT_CELL_HPP

#include <cstdint>

class cell {
public:
    cell(int16_t w, int16_t h) : w_(w), h_(h) {}; // констуртор из прямоугольных координат
    cell(int16_t x, int16_t y, int16_t z) : w_(-x + z), h_((x + 2 * y + z) / 2) {}; // конструктор с 3 переменными

    int16_t pos_x() { return w_ };
    int16_t pos_y() { return h_ };

private:
    int16_t w_, h_;
};


#endif //PROJECT_CELL_HPP
