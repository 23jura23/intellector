//
// Created by vsg on 03.03.2020.
//

#include <Position.hpp>

Position::Position(int w, int h) {
    y_ = 2 * h + w % 2;
    z_ = (w - y_) / 2;
    x_ = z_ - w;
};

Position::Position(int x, int y, int z)  : x_{x}, y_{y}, z_{z} {}

Position Position::operator-(Position &other) {
    return Position(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Position Position::operator+(Position &other) {
    return Position(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

int Position::posW() {
    return -x_ + z_;
}

int Position::posH() {
    return (x_ + 2 * y_ + z_) / 2;
}

double abs(Position pos) {
    return sqrt(pos.x_ * pos.x_ + pos.y_ * pos.y_ + pos.z_ * pos.z_);
}
