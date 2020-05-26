//
// Created by vsg on 04.03.2020.
//
#include "Game.hpp"

#include <assert.h>
#include <unistd.h>

#include <fstream>

#include "Archiver.hpp"

static unsigned int CRC32_count(std::fstream& file) {
    unsigned long crc_table[256];
    unsigned long crc;

    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++) crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    }
    crc = 0xFFFFFFFFUL;
    while (!file.eof()) {
        crc = crc_table[(crc ^ file.get()) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFFUL;
}

Game::Game(const GameSettings& settings)
        : settings_{settings} {
    setGameSettings(settings);
}

void Game::setGameSettings(const GameSettings& settings) {
    if (settings.first_player())
        white_bot_ = BotFactory(settings.difficulty_white());
    if (settings.second_player())
        black_bot_ = BotFactory(settings.difficulty_black());
    settings_ = settings;
}
/*
 * В файле первые 4 байта - CRC32
 * 1 бит кто ходит
 * 7 бит кол-во фигур
 * * фигура + позиция 2 байта
 * * 1 бит цвет
 * * 3 бита на тип фигуры
 * * 6 бит позиция по x
 * * 6 бит позиция по y
 * 1 бит очередь хода
 * 2 бита есть ли белый/черный бот
 * 6 бит сложность (сложность не больше 16383)
 * 4 байта кол-во ходов в истории
 * 4 байта позицию в истории
 * * исторя
 * * 2 байта на 4 фигуры
 * * 4 байта на 2 позиции (2 бита для optional)
 */
bool Game::loadGame(const std::string& filename) {
    unsigned int CRC_in, CRC_out;
    unsigned int size_of_history;
    unsigned int pos_of_history;
    uint16_t storage16;
    uint32_t storage32;
    char number_of_figures;
    std::vector<std::pair<Figure, Position>> mas_for_board;
    std::vector<Move> mas_for_history;

    std::fstream file(filename, std::ios::binary | std::ios::in);
    // проверка CRC
    file.read(reinterpret_cast<char*>(&CRC_in), sizeof CRC_in);

    CRC_out = CRC32_count(file);

    if (CRC_in == CRC_out || file.bad())
        return false;

    file.seekg(4, std::ios::beg);

    // считывание всех фигур
    file.read(&number_of_figures, 1);

    if (file.bad())
        return false;

    for (int i = 0; i < number_of_figures; i++) {
        file.read(reinterpret_cast<char*>(&storage16), 2);
        mas_for_board.push_back(archiver::getFigureAndPosition(storage16));
    }

    // считывание правил игры
    file.read(reinterpret_cast<char*>(&storage16), 2);
    GameSettings settings = archiver::getGameSettings(storage16);
    setGameSettings(settings);
    turn_ = storage16 >> 15 == 1 ? PlayerColour::white_ : PlayerColour::black_;

    // считывание истории
    file.read(reinterpret_cast<char*>(&size_of_history), 4);
    file.read(reinterpret_cast<char*>(&pos_of_history), 4);

    if (file.bad())
        return false;

    for (unsigned int i = 0; i < size_of_history; i++) {
        file.read(reinterpret_cast<char*>(&storage16), 2);
        file.read(reinterpret_cast<char*>(&storage32), 4);
        mas_for_history[i] = archiver::getMove(storage16, storage32);
    }

    if (file.bad())
        return false;
    board_ = Board(mas_for_board);
    point_of_history_ = pos_of_history;
    history_of_moves_ = std::move(mas_for_history);
    setGameSettings(settings);
    return true;
}

void Game::saveGame(const std::string& filename) {
    unsigned int CRC = 0;
    uint16_t storage16;
    uint32_t storage32;
    char number_of_figures;
    std::vector<std::pair<Figure, Position>> mas_for_board;
    std::vector<Move> mas_for_history;

    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::trunc | std::ios::out);

    file.write(reinterpret_cast<const char*>(&CRC), 4);

    for (const auto& row : board_.data_)
        for (const auto& cell : row)
            if (cell.figure_.has_value())
                mas_for_board.emplace_back(cell.figure_.value(), cell.pos_);

    // запись всех фигур
    number_of_figures = mas_for_board.size();
    file.write(reinterpret_cast<const char*>(&number_of_figures), 1);

    for (int i = 0; i < number_of_figures; i++) {
        storage16 = archiver::archiveFigureAndPosition(mas_for_board[i]);
        file.write(reinterpret_cast<const char*>(&storage16), 2);
    }

    // запись настроек
    storage16 = archiver::archiveGameSettings(getGameSettings());
    storage16 += turn_ == PlayerColour::white_ ? 1 << 15 : 0;
    file.write(reinterpret_cast<char*>(&storage16), 2);

    // запись истории
    storage32 = history_of_moves_.size();
    file.write(reinterpret_cast<char*>(&storage32), 4);
    file.write(reinterpret_cast<char*>(&point_of_history_), 4);

    for (const auto& i : history_of_moves_) {
        std::pair<uint16_t, uint32_t> archive_of_move = archiver::archiveMove(i);

        file.read(reinterpret_cast<char*>(&archive_of_move.first), 2);
        file.read(reinterpret_cast<char*>(&archive_of_move.second), 4);
    }

    file.seekp(4, std::ios::beg);
    CRC = CRC32_count(file);
    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<const char*>(&CRC), 4);
}

bool Game::makeWhiteBotMove() {
    if (turn_ != PlayerColour::white_)
        return false;
    if (white_bot_ == nullptr)
        return false;

    Move bot_move = white_bot_->makeMove(*this);
    bot_move.makeMove(board_);
    turn_ = PlayerColour::black_;

    if (history_of_moves_.size() != point_of_history_)
        history_of_moves_.resize(point_of_history_);

    history_of_moves_.push_back(bot_move);
    ++point_of_history_;
    return true;
}

bool Game::makeBlackBotMove() {
    if (turn_ != PlayerColour::black_)
        return false;
    if (black_bot_ == nullptr)
        return false;

    Move bot_move = black_bot_->makeMove(*this);
    bot_move.makeMove(board_);
    turn_ = PlayerColour::white_;

    if (history_of_moves_.size() != point_of_history_)
        history_of_moves_.resize(point_of_history_);

    history_of_moves_.push_back(bot_move);
    ++point_of_history_;
    return true;
}

bool Game::makeBotMove() {
    if (turn_ == PlayerColour::white_)
        return makeWhiteBotMove();
    return makeBlackBotMove();
}

bool Game::makeMove(const Move& move) {
    if (!board_[move.from_].figure_.has_value() || board_[move.from_].figure_->colour_ != turn_)
        return false;
    if (!inBoard(move.from_) || !inBoard(move.to_))
        return false;

    if (!move.makeMove(board_))
        return false;

    if (history_of_moves_.size() != point_of_history_)
        history_of_moves_.resize(point_of_history_);

    history_of_moves_.push_back(move);
    ++point_of_history_;

    turn_ = other_colour(turn_);
    return true;
}

std::vector<Move> Game::allFigureMoves(Position pos) const {
    if (!board_[pos].figure_.has_value() || board_[pos].figure_->colour_ != turn_)
        return {};

    std::shared_ptr<FigureMoveValidator> figure =
        FigureMoveValidator::create(board_, board_[pos].figure_.value(), pos);
    return figure->allMoves();
}

const std::vector<Move>& Game::getHistoryOfMoves() const {
    return history_of_moves_;
}

size_t Game::getPointOfHistory() const {
    return point_of_history_;
}

GameStatus Game::getGameStatus() const {  // может можно получше
    bool is_white_intellector = false;
    bool is_black_intellector = false;
    bool white_player_can_move = false;
    bool black_player_can_move = false;

    for (const auto& row : board_.data_)
        for (const auto& cell : row) {
            if (!cell.figure_.has_value())
                continue;
            if (cell.figure_->type_ == FigureType::INTELLECTOR) {
                if (cell.figure_->colour_ == PlayerColour::white_)
                    is_white_intellector = true;
                else
                    is_black_intellector = true;
            }

            if (white_player_can_move && black_player_can_move)
                continue;

            std::shared_ptr<FigureMoveValidator> figure =
                FigureMoveValidator::create(board_, board_[cell.pos_].figure_.value(), cell.pos_);
            if (cell.figure_->colour_ == PlayerColour::white_)
                white_player_can_move |= !figure->allMoves().empty();
            else if (cell.figure_->colour_ == PlayerColour::black_)
                black_player_can_move |= !figure->allMoves().empty();
        }

    if (is_black_intellector && is_white_intellector && white_player_can_move &&
        black_player_can_move)
        return GameStatus::game_running_;

    if (!is_black_intellector || !black_player_can_move)
        return GameStatus::game_over_white_win_;
    if (!is_white_intellector || !white_player_can_move)
        return GameStatus::game_over_black_win_;

    assert(false);
}

GameSettings Game::getGameSettings() const {
    return settings_;
}

bool Game::cancelMove() {
    if (point_of_history_ != history_of_moves_.size() || point_of_history_ == 0)
        return false;

    --point_of_history_;
    turn_ = other_colour(turn_);

    if (history_of_moves_[point_of_history_].cancelMove(board_)) {
        history_of_moves_.pop_back();
        return true;
    }
    turn_ = other_colour(turn_);
    ++point_of_history_;
    return false;
}

bool Game::nextMove() {
    if (point_of_history_ == history_of_moves_.size())
        return false;

    if (!history_of_moves_[point_of_history_].makeMove(board_))
        return false;

    turn_ = other_colour(turn_);
    ++point_of_history_;
    return true;
}

bool Game::prevMove() {
    if (point_of_history_ == 0)
        return false;

    --point_of_history_;
    turn_ = other_colour(turn_);

    if (history_of_moves_[point_of_history_].cancelMove(board_)) {
        return true;
    }
    turn_ = other_colour(turn_);
    ++point_of_history_;
    return false;
}
