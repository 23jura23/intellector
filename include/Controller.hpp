//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_GAME_HPP
#define _PROJECT_GAME_HPP

#include "Board.hpp"
#include "Game.hpp"

class Controller {
public: // TODO в Controller ссылка на бота
    void init(); // Запуск игры
    bool makeMove(Cell cell_from, Cell cell_to);

private:
    Board board_;
    PlayerColour turn_; // Чей ход
    // кто играет
    // история ходов
};

#endif //_PROJECT_GAME_HPP
