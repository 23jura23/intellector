//
// Created by vsg on 18.05.2020.
//

#include "Model/Archiver/Archiver.hpp"

static uint32_t cut(uint64_t storage, unsigned char pos, unsigned char size) {
    return (storage >> pos) & ((1 << size) - 1);
}

namespace archiver {

Figure getFigure(uint8_t storage) {
    uint8_t tmp;
    PlayerColour colour;
    FigureType type = FigureType::INTELLECTOR;
    tmp = storage >> 3;
    colour = tmp == 1 ? PlayerColour::white_ : PlayerColour::black_;
    tmp = storage & ((1 << 3) - 1);
    switch (tmp) {
        case 0:
            type = FigureType::INTELLECTOR;
            break;
        case 1:
            type = FigureType::DOMINATOR;
            break;
        case 2:
            type = FigureType::AGGRESSOR;
            break;
        case 3:
            type = FigureType::DEFENSSOR;
            break;
        case 4:
            type = FigureType::LIBERATOR;
            break;
        case 5:
            type = FigureType::PROGRESSOR;
            break;
    }
    return {colour, type};
}

std::pair<Figure, Position> getFigureAndPosition(uint16_t storage) {
    uint8_t tmp;
    int pos_x, pos_y;

    tmp = cut(storage, 12, 4);
    Figure figure = getFigure(tmp);

    pos_x = cut(storage, 6, 6);
    pos_y = cut(storage, 0, 6);

    return {figure, {pos_x, pos_y}};
}

GameSettings getGameSettings(uint16_t storage) {
    int difficulty_white;
    int difficulty_black;
    bool first_player;
    bool second_player;

    first_player = cut(storage, 14, 1);
    second_player = cut(storage, 13, 1);

    difficulty_white = cut(storage, 6, 6);
    difficulty_black = cut(storage, 0, 6);
    return {difficulty_white, difficulty_black, first_player, second_player};
}

Move getMove(uint16_t storage_figures, uint64_t storage_positions) {
    Figure from_old = getFigure(cut(storage_figures, 12, 4));
    Figure to_new = getFigure(cut(storage_figures, 8, 4));
    std::optional<Figure> from_new = {};
    std::optional<Figure> to_old = {};
    Position from, to;
    std::size_t point_of_history;
    bool optional_from, optional_to;

    point_of_history = cut(storage_positions, 32, 32);
    optional_from = cut(storage_positions, 31, 1);
    optional_to = cut(storage_positions, 30, 1);
    if (optional_from)
        from_new = getFigure(cut(storage_figures, 4, 4));
    if (optional_to)
        to_old = getFigure(cut(storage_figures, 0, 4));

    uint8_t x, y;
    x = cut(storage_positions, 23, 7);
    y = cut(storage_positions, 16, 7);
    from = Position(x, y);

    x = cut(storage_positions, 8, 8);
    y = cut(storage_positions, 0, 8);
    to = Position(x, y);
    return {from, to, point_of_history, from_old, to_old, to_new, from_new};
}

uint8_t archiveFigure(Figure figure) {
    uint8_t res = 0;
    if (figure.colour_ == PlayerColour::white_)
        res += 1 << 3;

    switch (figure.type_) {
        case FigureType::INTELLECTOR:
            break;
        case FigureType::DOMINATOR:
            res += 1;
            break;
        case FigureType::AGGRESSOR:
            res += 2;
            break;
        case FigureType::DEFENSSOR:
            res += 3;
            break;
        case FigureType::LIBERATOR:
            res += 4;
            break;
        case FigureType::PROGRESSOR:
            res += 5;
            break;
    }
    return res;
}

uint16_t archiveFigureAndPosition(const std::pair<Figure, Position>& pair) {
    uint16_t res = 0;
    Figure figure = pair.first;
    Position pos = pair.second;

    res += archiveFigure(figure) << 12;
    res += pos.posW() << 6;
    res += pos.posH();
    return res;
}

uint16_t archiveGameSettings(const GameSettings& settings) {
    uint16_t res = 0;

    res += settings.first_player() << 14;
    res += settings.second_player() << 13;
    res += settings.difficulty_white() << 6;
    res += settings.difficulty_black() << 0;
    return res;
}

std::pair<uint16_t, uint64_t> archiveMove(const Move& move) {
    uint16_t storage_figures = 0;
    uint64_t storage_positions = 0;

    storage_figures += archiveFigure(move.from_figure_old_) << 12;
    storage_figures += archiveFigure(move.to_figure_new_) << 8;
    if (move.from_figure_new_.has_value()) {
        storage_figures += archiveFigure(*move.from_figure_new_) << 4;
        storage_positions += 1 << 31;
    }
    if (move.to_figure_old_.has_value()) {
        storage_figures += archiveFigure(*move.to_figure_old_);
        storage_positions += 1 << 30;
    }
    storage_positions += move.point_of_history_ << 32;
    storage_positions += (move.from_.posW() & ((1 << 7) - 1)) << 23;
    storage_positions += (move.from_.posH() & ((1 << 7) - 1)) << 16;
    storage_positions += move.to_.posW() << 8;
    storage_positions += move.to_.posH();
    return {storage_figures, storage_positions};
}

}  // namespace archiver
