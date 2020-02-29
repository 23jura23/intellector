#include "ViewCurses.hpp"
#include "Board.hpp"
#include "Figure.hpp"

#include <assert.h>

#include <iostream>
using namespace std;

using namespace Curses;

viewCurses::BoardFieldContainer::BoardFieldContainer(const BoardField& board)
    : board_ { board }
{
}

viewCurses::viewCurses(const BoardField& board)
    : container_ { std::make_unique<BoardFieldContainer>(board) }
    , maxy { getmaxy(stdscr) }
    , maxx { getmaxx(stdscr) }
    , tlx { d-1 }
    , tly { 0 }
//TODO center align

{
    freopen("error.txt", "w", stderr);
    initscr();
    keypad(stdscr, true);
    curs_set(0);
    noecho();

    refresh_view();
}

viewCurses::~viewCurses()
{
    endwin();
}

void viewCurses::update(const BoardField& newBoard)
{
    container_ = std::make_unique<BoardFieldContainer>(newBoard);
    outBoard();
}

void viewCurses::refresh_view()
{
    clear();
    outBoard();
    refresh();
}

auto viewCurses::getTL(pair corner) -> pair
{
    cerr << corner.first << ' ' << corner.second << " => " << tlx + corner.first / 2 * delta_right_up.first + (corner.first % 2) * delta_right_down.first - (d - 1) << ' ' << tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second << endl;
    return { tlx + corner.first / 2 * delta_right_up.first + (corner.first % 2) * delta_right_down.first - (d - 1), tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second };
    //TODO rewrite more beautiful}
}

void viewCurses::outBoard()
{
    for (size_t x = 0; x < container_->board_.size(); ++x)
        for (size_t y = 0; y < container_->board_[x].size(); ++y) {
            assert(container_->board_[x][y]);
            outFigure(*container_->board_[x][y], getTL({ x, y }));
        }
}
void viewCurses::outFigure(const Figure& figure, pair TL)
{
    std::vector<const char*> draw;
    FigureType figureT = figure.getType();
    switch (figureT) {
    case FigureType::INTELLECTOR:
        draw = {
            "    ###########    ",
            "   #    !!!    #   ",
            "  #    !! !!    #  ",
            " #      !!!      # ",
            "#    !!!!I!!!!    #",
            " #      !!!      # ",
            "  #     !!!     #  ",
            "   #    !!!    #   ",
            "    ###########    ",
        };
        break;
    case FigureType::DOMINATOR:
        draw = {
            "    ###########    ",
            "   # \\   |   / #   ",
            "  #   \\ +++ /   #  ",
            " #     +...+     # ",
            "#     +..D..+     #",
            " #     +...+     # ",
            "  #   / +++ \\   #  ",
            "   # /   |   \\ #   ",
            "    ###########    "
        };
        break;
    case FigureType::AGGRESSOR:
        draw = {
            "    ###########    ",
            "   #           #   ",
            "  # YYYYYYYYYYY #  ",
            " #   YY.....YY   # ",
            "#     YY.A.YY     #",
            " #     YY.YY     # ",
            "  #     YYY     #  ",
            "   #     Y     #   ",
            "    ###########    "
        };
        break;
    case FigureType::DEFENSSOR:
        draw = {
            "    ###########    ",
            "   #  NNNNNNN  #   ",
            "  #     NNN     #  ",
            " #  NN N...N NN  # ",
            "#   NNNN.d.NNNN   #",
            " #  NN N...N NN  # ",
            "  #     NNN     #  ",
            "   #  NNNNNNN  #   ",
            "    ###########    "
        };

        break;
    case FigureType::LIERATOR:
        draw = {
            "    ###########    ",
            "   #           #   ",
            "  #  WWWWWWWWW  #  ",
            " #   WWW...WWW   # ",
            "#    WWW.L.WWW    #",
            " #   WWW...WWW   # ",
            "  #  WWWWWWWWW  #  ",
            "   #           #   ",
            "    ###########    "
        };

        break;
    case FigureType::PROGRESSOR:
        draw = {
            "    ###########    ",
            "   #     H     #   ",
            "  #     HHH     #  ",
            " #    HHH HHH    # ",
            "#    HHH...HHH    #",
            " #   HHH.P.HHH   # ",
            "  #  HHH...HHH  #  ",
            "   # HHHHHHHHH #   ",
            "    ###########    "
        };

        break;
    case FigureType::NONE:
        draw = {
            "    ###########    ",
            "   #           #   ",
            "  #             #  ",
            " #               # ",
            "#                 #",
            " #               # ",
            "  #             #  ",
            "   #           #   ",
            "    ###########    ",
        };
        break;
    }

    move(TL.second, TL.first);
    cerr << TL.second << ' ' << TL.first << endl;
    for (size_t i = 0; i < draw.size(); ++i) {
        move(TL.second + i, TL.first);
        cerr << TL.second + i << ' ' << TL.first << endl;
        for (size_t j = 0; j < d - 1 + d + d - 1; ++j)
            if (draw[i][j] != ' ')
                addch(draw[i][j]);
            else
                move(TL.second + i, TL.first + j + 1);
    }
}
