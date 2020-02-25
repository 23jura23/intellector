//
// Created by vsg on 22.02.2020.
//

#ifndef PROJECT_BOARD_HPP
#define PROJECT_BOARD_HPP

#include <vector>
#include <cstdint>
#include "Cell.hpp"

enum player_colour {
    black_, white_
};

class board {
public:
    board();
    ~board();

    bool move(cell of_pos, cell to_pos);

private:
    class figure {
    public:
        virtual bool check_move(cell to_pos_);
        virtual bool move(cell to_pos_);
        virtual std::vector<cell>& all_moves();

    private:
        player_colour colour_;
        cell pos_;
    };

    class f_intellector : figure {

    };

    class f_dominator : figure {

    };

    class f_aggressor : figure {

    };

    class f_defenssor : figure {

    };

    class f_liberator : figure {

    };

    class f_progressor : figure {

    };

    std::vector<std::vector<figure*>> data_;
    std::vector<figure*> all_white_figures_;
    std::vector<figure*> all_black_figures_;
    int16_t cols = 9, rows = 7; // ширина и высота
};

#endif //PROJECT_BOARD_HPP
