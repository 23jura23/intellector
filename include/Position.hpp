//
// Created by vsg on 02.03.2020.
//

#ifndef _INTELLECTOR_POSITION_HPP
#define _INTELLECTOR_POSITION_HPP

#include <cmath>

class Position {
public:
    Position(int w, int h) {  // констуртор из прямоугольных координат
        y_ = 2 * h + w % 2;
        z_ = (w - y_) / 2;
        x_ = z_ - w;
    };

    Position(int x, int y, int z)  // конструктор с 3 переменными
            : x_{x}, y_{y}, z_{z} {}

    Position operator-(const Position &other) const {
        return Position(x_ - other.x_, y_ - other.y_, z_ - other.z_);
    }

    Position operator+(const Position &other) const {
        return Position(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    [[nodiscard]] int posW() const { return -x_ + z_; }
    [[nodiscard]] int posH() const { return (x_ + 2 * y_ + z_) / 2; }

    int x_, y_, z_;
};

[[nodiscard]] inline double abs(Position pos) {
    return sqrt(pos.x_ * pos.x_ + pos.y_ * pos.y_ + pos.z_ * pos.z_);
}

#endif //_INTELLECTOR_POSITION_HPP
