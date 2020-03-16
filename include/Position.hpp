//
// Created by vsg on 02.03.2020.
//

#ifndef _INTELLECTOR_POSITION_HPP
#define _INTELLECTOR_POSITION_HPP

#include <cmath>

class Position {
public:
    Position() : x_{0}, y_{0}, z_{0} {};
    Position(const Position&) = default;
    Position& operator=(const Position&) = default;
    ~Position() = default;

    Position(int w, int h) {  // констуртор из прямоугольных координат
        y_ = 2 * h + w % 2;
        z_ = (w - y_) / 2;
        x_ = z_ - w;
    };

    Position(int x, int y, int z)  // конструктор с 3 переменными
            : x_{x}, y_{y}, z_{z} {}

    Position operator-(const Position& right) const {
        return Position(x_ - right.x_, y_ - right.y_, z_ - right.z_);
    }

    Position operator-=(const Position& right) {
        return *this = *this - right;
    }

    Position operator+(const Position& right) const {
        return Position(x_ + right.x_, y_ + right.y_, z_ + right.z_);
    }

    Position operator+=(const Position& right) {
        return *this = *this + right;
    }

    Position operator*(int val) const {
        return Position(x_ * val, y_ * val, z_ * val);
    }

    [[nodiscard]] Position makeX() const {
        Position null(1, -1, 1);
        return *this - (null * x_);
    }

    [[nodiscard]] Position makeY() const {
        Position null(1, -1, 1);
        return *this + (null * y_);
    }

    [[nodiscard]] Position makeZ() const {
        Position null(1, -1, 1);
        return *this - (null * z_);
    }

    Position makeSum() {
        int sum = x_ + y_ + z_;
        x_ -= sum;
        y_ += sum;
        z_ -= sum;
        return *this;
    }

    [[nodiscard]] bool operator==(const Position& other) const {
        return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
    }

    [[nodiscard]] bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    [[nodiscard]] int posW() const { return -x_ + z_; }

    [[nodiscard]] int posH() const { return floor((x_ + 2 * y_ + z_) / 2.0); } // -3 1 2 -> -3 0 2

    int x_, y_, z_;
};

#endif //_INTELLECTOR_POSITION_HPP
