#include <assert.h>
#include <iostream>
#include <unistd.h>

#include "Board.hpp"
#include "Controller.hpp"
#include "Figure.hpp"
#include "ViewCurses.hpp"

using namespace std;

#ifdef BW
#define COLOR_WHITE_CELL 255
#define COLOR_BLACK_CELL 237
#define COLOR_WHITE_FIGURE 187
#define COLOR_BLACK_FIGURE 137
#define COLOR_WHITE_ACTIVE 82
#define COLOR_BLACK_ACTIVE 70
#define COLOR_WHITE_CURRENT 123
#define COLOR_BLACK_CURRENT 111
#define COLOR_WHITE_LETTER 196
#define COLOR_BLACK_LETTER 226
#define COLOR_FORE_BORDER 238
#define COLOR_BACK_BORDER 241
#else
#define COLOR_WHITE_CELL 187
#define COLOR_BLACK_CELL 137
#define COLOR_WHITE_FIGURE 231
#define COLOR_BLACK_FIGURE 0
#define COLOR_WHITE_ACTIVE 82
#define COLOR_BLACK_ACTIVE 70
#define COLOR_WHITE_CURRENT 123
#define COLOR_BLACK_CURRENT 111
#define COLOR_WHITE_SELECTED 56
#define COLOR_BLACK_SELECTED 55
#define COLOR_WHITE_LETTER 196
#define COLOR_BLACK_LETTER 226
#define COLOR_FORE_BORDER 238
#define COLOR_BACK_BORDER 241
#endif

#define WOW 100 // White On White
#define WOB 101 // White On Black
#define BOW 102 // Black On White
#define BOB 103 // Black On Black
//#define WOA 104 // White On Active
//#define BOA 105 // Black On Active
#define CELL_WHITE 200          // INACTIVE
#define CELL_BLACK 201          // INACTIVE
#define CELL_WHITE_ACTIVE 202   // ACTIVE
#define CELL_BLACK_ACTIVE 203   // ACTIVE
#define CELL_WHITE_CURRENT 204  // CURRENT
#define CELL_BLACK_CURRENT 205  // CURRENT
#define CELL_WHITE_SELECTED 206 // SELECTED
#define CELL_BLACK_SELECTED 207 // SELECTED
#define CELL_BORDER 220
#define LETTER_BLACK 221
#define LETTER_WHITE 222

//TODO
//DONE Highlight current cell
//Do not select opponent cell
//Fix downside coordinate bug
//DONE operator[] ViewBoard

using namespace ViewCurses;

//TODO center align
viewCurses::viewCurses(std::shared_ptr<Controller> controller)
    : controller_ { controller }
    , maxy { getmaxy(stdscr) }
    , maxx { getmaxx(stdscr) }
    , tlx { d - 1 }
    , tly { 0 }
    , currentPos { -2, 3, 2 }
    , currentPosStatus { CurrentPosStatus::UNSELECTED }
{
    freopen("error.txt", "a", stderr);

    fetchModel();

    initscr();
    if (!has_colors()) {
        endwin();
        throw ViewBaseException("Your terminal does not support colors");
    }
    start_color();
    cerr << "COLORS:" << COLORS << endl;

    init_pair(WOW, COLOR_BLACK_FIGURE, COLOR_WHITE_FIGURE);
    init_pair(WOB, COLOR_BLACK_FIGURE, COLOR_WHITE_FIGURE);
    init_pair(BOW, COLOR_WHITE_FIGURE, COLOR_BLACK_FIGURE);
    init_pair(BOB, COLOR_WHITE_FIGURE, COLOR_BLACK_FIGURE);
    init_pair(CELL_WHITE, COLOR_WHITE_CELL, COLOR_WHITE_CELL);
    init_pair(CELL_BLACK, COLOR_BLACK_CELL, COLOR_BLACK_CELL);
    init_pair(CELL_WHITE_ACTIVE, COLOR_WHITE_ACTIVE, COLOR_WHITE_ACTIVE);
    init_pair(CELL_BLACK_ACTIVE, COLOR_BLACK_ACTIVE, COLOR_BLACK_ACTIVE);
    init_pair(CELL_WHITE_CURRENT, COLOR_WHITE_CURRENT, COLOR_WHITE_CURRENT);
    init_pair(CELL_BLACK_CURRENT, COLOR_BLACK_CURRENT, COLOR_BLACK_CURRENT);
    init_pair(CELL_WHITE_SELECTED, COLOR_WHITE_SELECTED, COLOR_WHITE_SELECTED);
    init_pair(CELL_BLACK_SELECTED, COLOR_BLACK_SELECTED, COLOR_BLACK_SELECTED);
    init_pair(CELL_BORDER, COLOR_FORE_BORDER, COLOR_BACK_BORDER);
    init_pair(LETTER_WHITE, COLOR_WHITE_LETTER, COLOR_WHITE_FIGURE);
    init_pair(LETTER_BLACK, COLOR_BLACK_LETTER, COLOR_BLACK_FIGURE);

    keypad(stdscr, true);
    curs_set(0);
    noecho();
}

viewCurses::~viewCurses()
{
    use_default_colors();
    endwin();
}

void viewCurses::run()
{
    while (1) {
        refreshView();
        chtype c = getch();

        Position newPos = currentPos;

        switch (c) {
        case 'w':
            newPos.y_ += 1;
            break;
        case 's':
            newPos.y_ -= 1;
            break;
        case 'a':
            newPos.z_ -= 1;
            break;
        case 'e':
            newPos.z_ += 1;
            break;
        case 'd':
            newPos.x_ -= 1;
            break;
        case 'q':
            newPos.x_ += 1;
            break;
            //        case 'W':
            //            newPos.y_ += 3;
            //            break;
            //        case 'S':
            //            newPos.y_ -= 3;
            //            break;
            //        case 'A':
            //            newPos.x_ += 1;
            //            newPos.z_ -= 1;
            //            break;
            //        case 'E':
            //            newPos.x_ -= 1;
            //            newPos.z_ += 1;
            //            break;
            //        case 'D':
            //            newPos.x_ -= 1;
            //            break;
            //        case 'Q':
            //            newPos.x_ += 1;
            //            break;
        case 32:
            switch (currentPosStatus) {
            case CurrentPosStatus::UNSELECTED:
                if ((*board_)[currentPos].cell.figure_.has_value()) {
                    cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was selected" << endl;
                    // Cell with figure was selected
                    //                    if (currentSelectedCell)
                    //                        throw ViewBaseException("Figure selected, but it was already selected");
                    currentPosStatus = CurrentPosStatus::SELECTED;
                    selectedPos = currentPos;
                    //                    currentSelectedCell = &((*board_)[currentPos]);
                    //                    cerr << "Selecting " << currentSelectedCell << endl;
                    //                    cerr << (*board_)[currentPos].cell.pos_.posW() << endl;
                    //                    cerr << currentSelectedCell->cell.pos_.posW() << endl;
                    controller_->selectCell<ViewCurses::viewCurses>((*board_)[selectedPos].cell);
                    fetchModel();
                    (*board_)[selectedPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::SELECTED;
                } else {
                    cerr << "Empty cell " << currentPos.posW() << ' ' << currentPos.posH() << " was tried to be selected (unsuccessfully)" << endl;
                    // Empty cell was selected
                }

                break;
            case CurrentPosStatus::SELECTED:
                cerr << "Trying to do smth with Cell " << currentPos.posW() << ' ' << currentPos.posH() << endl;
                //                cerr << "currentSelectedCell " << currentSelectedCell << endl;
                //                cerr << currentSelectedCell->cell.pos_.posW() << endl;
                if (currentPos.posW() == selectedPos.posW() && currentPos.posH() == selectedPos.posH()) {
                    cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was unselected" << endl;
                    // Cell was unselected
                    reloadModel();
                    //                    controller_->unSelectCell<ViewCurses::viewCurses>();
                    (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::INACTIVE;
                    currentPosStatus = CurrentPosStatus::UNSELECTED;
                } else {
                    if ((*board_)[currentPos].inMoves.size()) {
                        cerr << "Step " << currentPos.posW() << ' ' << currentPos.posH() << " was tried to be done" << endl;
                        if ((*board_)[currentPos].inMoves.size() == 1) {
                            cerr << "UniStep " << currentPos.posW() << ' ' << currentPos.posH() << " was done" << endl;
                            controller_->makeMove(*(*board_)[currentPos].inMoves[0]);
                            reloadModel();
                            (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::INACTIVE;
                            currentPosStatus = CurrentPosStatus::UNSELECTED;
                        } else {
                            cerr << "MultiStep " << currentPos.posW() << ' ' << currentPos.posH() << " was triedto be done (yet unsuccessfully)" << endl;
                            // multiple steps to the same cell are possible
                        }
                    } else {
                        // Impossible move
                    }
                }
                break;
            }
            break;
        }
//        newPos.makeSum();
        cerr << c << endl;
        cerr << "newPos: " << newPos.posW() << ' ' << newPos.posH() << endl;
        cerr << "truepos" << newPos.x_ << ' ' << newPos.y_ << ' ' << newPos.z_ << endl;
        if (inBoard(newPos)) {
            if (currentPosStatus == CurrentPosStatus::SELECTED && currentPos.posW() == selectedPos.posW() && currentPos.posH() == selectedPos.posH())
                (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::SELECTED;
            else if ((*board_)[currentPos].inMoves.size())
                (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::ACTIVE;
            else
                (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::INACTIVE;
            currentPos = newPos;
            if (!(currentPosStatus == CurrentPosStatus::SELECTED && currentPos.posW() == selectedPos.posW() && currentPos.posH() == selectedPos.posH()))
                (*board_)[currentPos].status = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::CURRENT;
        }
    }
}

void viewCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel)
{
    board_ = newModel;
}

void viewCurses::fetchModel()
{
    updateModel(std::dynamic_pointer_cast<ViewModelCurses>(controller_->getViewModel<viewCurses>()));
}

void viewCurses::reloadModel()
{
    controller_->updateViewModel<viewCurses>();
    fetchModel();
}

void viewCurses::refreshView()
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
    for (size_t x = 0; x < board_->viewBoard.size(); ++x)
        for (size_t y = 0; y < board_->viewBoard[x].size(); ++y) {
            //            size_t cor_x = board_->viewBoard.size() - 1 - x;
            size_t cor_x = x;
            size_t cor_y = board_->viewBoard[x].size() - 1 - y;
            //            size_t cor_y = y;
            outCell(board_->viewBoard[cor_x][cor_y], getTL({ x, y }));
        }
}

void viewCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL)
{
    int FIGURE_COLOR = -1;
    int CELL_COLOR = -1;
    int LETTER_COLOR = -1;
    switch (cell.status) {
    case ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::INACTIVE:
        if (cell.cell.colour_ == CellColour::WHITE)
            CELL_COLOR = CELL_WHITE;
        else
            CELL_COLOR = CELL_BLACK;
        break;
    case ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::ACTIVE:
        if (cell.cell.colour_ == CellColour::WHITE)
            CELL_COLOR = CELL_WHITE_ACTIVE;
        else
            CELL_COLOR = CELL_BLACK_ACTIVE;
        break;
    case ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::CURRENT:
        if (cell.cell.colour_ == CellColour::WHITE)
            CELL_COLOR = CELL_WHITE_CURRENT;
        else
            CELL_COLOR = CELL_BLACK_CURRENT;
        break;
    case ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::SELECTED:
        if (cell.cell.colour_ == CellColour::WHITE)
            CELL_COLOR = CELL_WHITE_SELECTED;
        else
            CELL_COLOR = CELL_BLACK_SELECTED;
        break;
    }
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
        size_t draw_i = i;
        if (cell.cell.figure_.has_value()
            && cell.cell.figure_->colour_ == PlayerColour::black_
            && cell.cell.figure_->type_ != FigureType::INTELLECTOR)
            draw_i = draw.size() - 1 - i;
        if (0 <= TL.second + i && TL.second + i <= static_cast<size_t>(maxy) && 0 <= TL.first && TL.first <= static_cast<size_t>(maxx)) {
            move(TL.second + i, TL.first);
            for (size_t j = 0; j < d - 1 + d + d - 1; ++j) {
                switch (draw[draw_i][j]) {
                case '`':
                    move(TL.second + i, TL.first + j + 1);
                    break;
                case ' ':
                    attron(COLOR_PAIR(CELL_COLOR));
                    addch(draw[draw_i][j]);
                    attroff(COLOR_PAIR(CELL_COLOR));
                    break;
                case '#':
                    attron(COLOR_PAIR(CELL_BORDER));
                    addch(draw[draw_i][j]);
                    attroff(COLOR_PAIR(CELL_BORDER));
                    break;
                case 'D':
                case 'L':
                case 'A':
                case 'd':
                case 'I':
                case 'P':
                    attron(COLOR_PAIR(LETTER_COLOR));
                    addch(draw[draw_i][j]);
                    attroff(COLOR_PAIR(LETTER_COLOR));
                    break;
                default:
                    attron(COLOR_PAIR(FIGURE_COLOR));
                    addch(draw[draw_i][j]);
                    attroff(COLOR_PAIR(FIGURE_COLOR));
                    break;
                }
            }
            //                usleep(10000);
            //                refresh();
        }
    }
}
