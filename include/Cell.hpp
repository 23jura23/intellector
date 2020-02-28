//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_CELL_HPP
#define _PROJECT_CELL_HPP

class Cell {
public:
    Cell(int w, int h) {
        y_ = 2 * h + w % 2;
        z_ = (w - y_) / 2;
        x_ = z_ - w;
    }; // констуртор из прямоугольных координат
    Cell(int x, int y, int z) : x_{x}, y_{y}, z_{z} {}; // конструктор с 3 переменными

    int posW() { return -x_ + z_; }; // Для массива.
    int powH() { return (x_ + 2 * y_ + z_) / 2; };

    int x_, y_, z_;
};


#endif //_PROJECT_CELL_HPP
