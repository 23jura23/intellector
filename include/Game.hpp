//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_GAME_HPP
#define _PROJECT_GAME_HPP

#include "Board.hpp"

class game {
public:
    void init(); // Запуск игры
    bool makeMove(cell cell_from, cell cell_to, player_colour turn_);

private:
    board board_;
    player_colour turn_; // Чей ход
};

#endif //_PROJECT_GAME_HPP
