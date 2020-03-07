#include <assert.h>
#include <iostream>
#include <unistd.h>

#include "Board.hpp"
#include "Figure.hpp"
#include "ViewCurses.hpp"

using namespace std;

#ifdef BW
#define COLOR_WHITE_CELL 255
#define COLOR_BLACK_CELL 237
#define COLOR_WHITE_FIGURE 187
#define COLOR_BLACK_FIGURE 137
#else
#define COLOR_WHITE_CELL 187
#define COLOR_BLACK_CELL 137
#define COLOR_WHITE_FIGURE 231
#define COLOR_BLACK_FIGURE 0
#endif

#define WOW 100 // White On White
#define WOB 101 // White On Black
#define BOW 110 // Black On White
#define BOB 111 // Black On Black
#define CELL_WHITE 200
#define CELL_BLACK 201
#define CELL_BORDER 202
#define LETTER_BLACK 203
#define LETTER_WHITE 204

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
    if (!has_colors()) {
        endwin();
        throw ViewBaseException("Your terminal does not support colors");
    }
    start_color();
    cerr << "COLORS:" << COLORS << endl;

    init_pair(WOW, 0, 231);
    init_pair(WOB, 0, 231);
    init_pair(BOW, 231, 0);
    init_pair(BOB, 231, 0);
    init_pair(CELL_WHITE, COLOR_WHITE_CELL, COLOR_WHITE_CELL);
    init_pair(CELL_BLACK, COLOR_BLACK_CELL, COLOR_BLACK_CELL);
    init_pair(CELL_BORDER, 238, 241);
    init_pair(LETTER_WHITE, 196, COLOR_WHITE_CELL);
    init_pair(LETTER_BLACK, 165, COLOR_BLACK_CELL);

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
            size_t cor_x = container_->board.viewBoard.size() - 1 - x;
            size_t cor_y = container_->board.viewBoard[x].size() - 1 - y;
            outCell(container_->board.viewBoard[cor_x][cor_y], getTL({ cor_x, cor_y }));
        }
}

void viewCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL)
{
    int FIGURE_COLOR = -1;
    int CELL_COLOR = -1;
    int LETTER_COLOR = -1;
    if (cell.cell.colour_ == CellColour::WHITE)
        CELL_COLOR = CELL_WHITE;
    else
        CELL_COLOR = CELL_BLACK;
    std::vector<const char*> draw;
    if (!cell.cell.figure_.has_value()) {
        draw = {
            "````###########````",
            "```#           #```",
            "``#             #``",
            "`#               #`",
            "#                 #",
            "`#               #`",
            "``#             #``",
            "```#           #```",
            "````###########````",
        };
    } else {
        FigureType figureT = cell.cell.figure_.value().type_;
        switch (figureT) {
        case FigureType::INTELLECTOR:
            draw = {
                "````###########````",
                "```#    !!!    #```",
                "``#    !! !!    #``",
                "`#      !!!      #`",
                "#    !!!!I!!!!    #",
                "`#      !!!      #`",
                "``#     !!!     #``",
                "```#    !!!    #```",
                "````###########````",
            };
            break;
        case FigureType::DOMINATOR:
            draw = {
                "````###########````",
                "```# +   +   + #```",
                "``#   + +++ +   #``",
                "`#     +   +     #`",
                "#     ++ D ++     #",
                "`#     +   +     #`",
                "``#   + +++ +   #``",
                "```# +   +   + #```",
                "````###########````"
            };
            break;
        case FigureType::AGGRESSOR:
            draw = {
                "````###########````",
                "```#           #```",
                "``# !!!!!!!!!!! #``",
                "`#   !!     !!   #`",
                "#     !! A !!     #",
                "`#     !! !!     #`",
                "``#     !!!     #``",
                "```#     !     #```",
                "````###########````"
            };
            break;
        case FigureType::DEFENSSOR:
            draw = {
                "````###########````",
                "```#  !!!!!!!  #```",
                "``#     !!!     #``",
                "`#  !! !! !! !!  #`",
                "#   !!!! d !!!!   #",
                "`#  !! !! !! !!  #`",
                "``#     !!!     #``",
                "```#  !!!!!!!  #```",
                "````###########````"
            };

            break;
        case FigureType::LIBERATOR:
            draw = {
                "````###########````",
                "```#           #```",
                "``#  !!!!!!!!!  #``",
                "`#   !!!   !!!   #`",
                "#    !!! L !!!    #",
                "`#   !!!   !!!   #`",
                "``#  !!!!!!!!!  #``",
                "```#           #```",
                "````###########````"
            };

            break;
        case FigureType::PROGRESSOR:
            draw = {
                "````###########````",
                "```#     !     #```",
                "``#     !!!     #``",
                "`#    !!! !!!    #`",
                "#    !!!   !!!    #",
                "`#   !!! P !!!   #`",
                "``#  !!!   !!!  #``",
                "```# !!!!!!!!! #```",
                "````###########````"
            };
            break;
        }
        if (cell.cell.figure_->colour_ == PlayerColour::white_) {
            if (cell.cell.colour_ == CellColour::WHITE) {
                FIGURE_COLOR = WOW;
            } else {
                FIGURE_COLOR = WOB;
            }
            LETTER_COLOR = LETTER_WHITE;
        } else {
            if (cell.cell.colour_ == CellColour::WHITE) {
                FIGURE_COLOR = BOW;
            } else {
                FIGURE_COLOR = BOB;
            }
            LETTER_COLOR = LETTER_BLACK;
        }
    }
    move(TL.second, TL.first);
    for (size_t i = 0; i < draw.size(); ++i) {
        if (0 <= TL.second + i && TL.second + i <= static_cast<size_t>(maxy) && 0 <= TL.first && TL.first <= static_cast<size_t>(maxx)) {
            move(TL.second + i, TL.first);
            for (size_t j = 0; j < d - 1 + d + d - 1; ++j) {
                switch (draw[i][j]) {
                case '`':
                    move(TL.second + i, TL.first + j + 1);
                    break;
                case ' ':
                    attron(COLOR_PAIR(CELL_COLOR));
                    addch(draw[i][j]);
                    attroff(COLOR_PAIR(CELL_COLOR));
                    break;
                case '#':
                    attron(COLOR_PAIR(CELL_BORDER));
                    addch(draw[i][j]);
                    attroff(COLOR_PAIR(CELL_BORDER));
                    break;
                case 'D':
                case 'L':
                case 'A':
                case 'd':
                case 'I':
                case 'P':
                    attron(COLOR_PAIR(LETTER_COLOR));
                    addch(draw[i][j]);
                    attroff(COLOR_PAIR(LETTER_COLOR));
                    break;
                default:
                    attron(COLOR_PAIR(FIGURE_COLOR));
                    addch(draw[i][j]);
                    attroff(COLOR_PAIR(FIGURE_COLOR));
                    break;
                }
            }
        }
    }
    //            usleep(100000);
    //            refresh();
}
