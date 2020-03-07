#include <assert.h>
#include <iostream>
#include <unistd.h>

#include "Board.hpp"
#include "Figure.hpp"
#include "ViewCurses.hpp"

using namespace std;

using namespace ViewCurses;

viewCurses::ModelContainer::ModelContainer(ViewModelCurses& board)
    : board { board }
{
}

//TODO center align
viewCurses::viewCurses()
    : maxy { getmaxy(stdscr) }
    , maxx { getmaxx(stdscr) }
    , tlx { d - 1 }
    , tly { 0 }
{
    freopen("error.txt", "a", stderr);
    initscr();
    if (!has_colors())
    {
        endwin();
        throw ViewBaseException("Your terminal does not support colors");
    }
    start_color();
    keypad(stdscr, true);
    curs_set(0);
    noecho();
}

viewCurses::~viewCurses()
{
    use_default_colors();
    endwin();
}

void viewCurses::update(ViewModelCurses& newModel)
{
    container_ = std::make_unique<ModelContainer>(newModel);
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
//    cerr << corner.first << ' ' << corner.second << " => " << tlx + corner.first / 2 * delta_right_up.first + (corner.first % 2) * delta_right_down.first - (d - 1) << ' ' << tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second << endl;
    return { tlx + corner.first / 2 * delta_right_up.first + (corner.first % 2) * delta_right_down.first - (d - 1), tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second };
    //TODO rewrite more beautiful}
}

void viewCurses::outBoard()
{
    for (size_t x = 0; x < container_->board.viewBoard.size(); ++x)
        for (size_t y = 0; y < container_->board.viewBoard[x].size(); ++y) {
            outCell(container_->board.viewBoard[x][y], getTL({ x, y }));
        }
}
void viewCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL)
{
    std::vector<const char*> draw;
    if (!cell.cell.figure_.has_value()) {
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
    } else {
        FigureType figureT = cell.cell.figure_.value().type_;
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
        case FigureType::LIBERATOR:
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
        }
    }
    move(TL.second, TL.first);
    for (size_t i = 0; i < draw.size(); ++i) {
        if (0 <= TL.second + i && TL.second + i <= static_cast<size_t>(maxy) && 0 <= TL.first && TL.first <= static_cast<size_t>(maxx)) {
            move(TL.second + i, TL.first);
            for (size_t j = 0; j < d - 1 + d + d - 1; ++j)
                if (draw[i][j] != ' ') {
                    addch(draw[i][j]);
                } else {
                    move(TL.second + i, TL.first + j + 1);
                }
//            usleep(100000);
//            refresh();
        }
    }
}
