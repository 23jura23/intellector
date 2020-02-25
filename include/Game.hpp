//
// Created by vsg on 22.02.2020.
//

#ifndef PROJECT_GAME_HPP
#define PROJECT_GAME_HPP

#include "Board.hpp"
#include "Cell.hpp"

class game {
public:
    void init(); // Запуск игры
    bool make_move(cell cell_from, cell cell_to);

private:
    board board_;
    int turn; // Чей ход
};

#endif //PROJECT_GAME_HPP
