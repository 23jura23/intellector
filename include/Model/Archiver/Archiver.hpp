//
// Created by vsg on 18.05.2020.
//

#ifndef INTELLECTOR_ARCHIVER_HPP
#define INTELLECTOR_ARCHIVER_HPP

#include "Model/ModelImpl/Game.hpp"

namespace archiver
{

Figure getFigure(uint8_t storage);

std::pair<Figure, Position> getFigureAndPosition(uint16_t storage);

GameSettings getGameSettings(uint16_t storage);

Move getMove(uint16_t storage_figures, uint32_t storage_positions);

uint8_t archiveFigure(Figure figure);

uint16_t archiveFigureAndPosition(const std::pair<Figure, Position>& pair);

uint16_t archiveGameSettings(const GameSettings& settings);

std::pair<uint16_t, uint32_t> archiveMove(const Move& move);

} // end archiver

#endif  //INTELLECTOR_ARCHIVER_HPP
