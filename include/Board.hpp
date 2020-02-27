//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_BOARD_HPP
#define _PROJECT_BOARD_HPP

#include <vector>
#include "Cell.hpp"

enum class Figure {
    INTELLECTOR,
    DOMINATOR,
    AGGRESSOR,
    DEFENSSOR,
    LIERATOR,
    PROGRESSOR
};

enum player_colour {
    black_, white_
};

struct triple {
    Figure type_;
    cell pos_;
    player_colour colour_;
    triple(Figure type, cell pos, player_colour colour)
    : type_(type), pos_(pos), colour_(colour) {};
};

class board {
private: // Интерфейс фигуры----------------------------------------------------------------------
    class figure {
    public:
        figure(cell pos, player_colour colour) : pos_(pos), colour_(colour) {}
        virtual ~figure() = default;

        virtual bool checkMove(cell to_pos_);
        virtual bool move(cell to_pos_);
        virtual std::vector<cell>& allMoves();

    private:
        player_colour colour_;
        cell pos_;
    };

public: // Функции класса-------------------------------------------------------------------------
    board();
    ~board();

    bool move(cell of_pos, cell to_pos);
    const std::vector<std::vector<figure*>>& getBoard() {return data_; }

private: // Все фигуры----------------------------------------------------------------------------
    class fIntellector : public figure {
    public:
        fIntellector(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fIntellector() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;
    };

    class fDominator : public figure {
    public:
        fDominator(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fDominator() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;
    };

    class fAggressor : public figure {
    public:
        fAggressor(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fAggressor() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;

    };

    class fDefenssor : public figure {
    public:
        fDefenssor(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fDefenssor() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;
    };

    class fLiberator : public figure {
    public:
        fLiberator(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fLiberator() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;
    };

    class fProgressor : public figure {
    public:
        fProgressor(cell pos, player_colour colour) : figure(pos, colour) {};
        ~fProgressor() override = default;

        bool checkMove(cell to_pos_) override;
        bool move(cell to_pos_) override;
        std::vector<cell>& allMoves() override;
    };

    // Поля доски---------------------------------------------------------------------------------
    std::vector<std::vector<figure*>> data_;
    std::vector<figure*> all_white_figures_;
    std::vector<figure*> all_black_figures_;
    int cols_ = 9, rows_ = 7; // ширина и высота

    const std::vector<triple> arrangement_; // Расположение фигур

};

#endif //_PROJECT_BOARD_HPP
