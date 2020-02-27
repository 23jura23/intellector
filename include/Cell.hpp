//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_CELL_HPP
#define _PROJECT_CELL_HPP

class cell {
public:
    cell(int w, int h) {
        y_ = 2 * h + w % 2;
        z_ = (w - y_) / 2;
        x_ = z_ - w;
    }; // констуртор из прямоугольных координат
    cell(int x, int y, int z) : x_{x}, y_{y}, z_{z} {}; // конструктор с 3 переменными

    int pos_w() { return -x_ + z_; }; // Для массива.
    int pos_h() { return (x_ + 2 * y_ + z_) / 2; };

    int x_, y_, z_;
};


#endif //_PROJECT_CELL_HPP
