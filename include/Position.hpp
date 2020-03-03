//
// Created by vsg on 02.03.2020.
//

#ifndef _INTELLECTOR_POSITION_HPP
#define _INTELLECTOR_POSITION_HPP

#include <cmath>

class Position {
public:
    Position(int w, int h); // констуртор из прямоугольных координат

    Position(int x, int y, int z);  // конструктор с 3 переменными

    inline Position operator-(Position &other);

    inline Position operator+(Position &other);

    int posW();
    int posH();

    int x_, y_, z_;
};

[[nodiscard]] inline double abs(Position pos);

#endif //_INTELLECTOR_POSITION_HPP
