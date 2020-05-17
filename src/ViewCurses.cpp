#include "ViewCurses.hpp"

#include <assert.h>
#include <unistd.h>

#include <iostream>

#include "Board.hpp"
#include "Controller.hpp"
#include "Figure.hpp"
#include "ViewColorSchemeCurses.hpp"
#include "ViewInitCurses.hpp"
#include "ViewMainMenuCurses.hpp"
#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

using namespace std;

#define CENTER_ALIGN 1
// TODO add to config/settings

using namespace viewCurses;

void ViewCurses::calculateTL() {  // top left angle
    tlx = 0;
    tly = 0;
    maxy = getmaxy(stdscr);
    maxx = getmaxx(stdscr);

    if (CENTER_ALIGN) {
        size_t leny = 0;
        for (size_t i = 0; i < board_->viewBoard_.size(); ++i) {
            size_t j = board_->viewBoard_[i].size();
            leny = max(leny, getTL({i, j}).second);
        }
        size_t lenx = 0;
        if (board_->cols_ <= 0)
            throw ViewBaseException("Width of board must be positive");
        for (size_t j = 0; j < board_->viewBoard_[board_->cols_ - 1].size(); ++j) {
            lenx = max(lenx, getTL({board_->cols_, j}).first);
        }
        tlx = maxx / 2 - lenx / 2;
        tly = maxy / 2 - leny / 2;
    } else {
        tlx = d - 1;
        tly = 0;
    }
}

ViewCurses::ViewCurses(std::shared_ptr<Controller> controller)
        : controller_{controller}
        , tlx{0}
        , tly{0}
        , currentPos{-2, 3, 2}
        , currentPosStatus{CurrentPosStatus::UNSELECTED} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);
    // avoiding warning. May be harmful, but later there must be a well-done logging.

    initCurses();

    fetchModel();
    updateCellStatus(currentPos, 1);
    updateCellStatus(currentPos, 0);
}

ViewCurses::~ViewCurses() {
    terminateCurses();
}

MENU_TYPE ViewCurses::type() const {
    return MENU_TYPE::GAME_MENU;
}

void ViewCurses::updateCellStatus(const Position& pos, bool before) {
    if (inBoard(pos)) {
        if (before) {
            // update status_ before pointer moves
            if (currentPosStatus == CurrentPosStatus::SELECTED && currentPos == selectedPos)
                board_->get(pos).status_ = CellStatus::SELECTED;
            else if (board_->get(pos).inMoves_.size())
                board_->get(pos).status_ = CellStatus::ACTIVE;
            else
                board_->get(pos).status_ = CellStatus::INACTIVE;
        } else {
            // update status_ after pointer moves
            if (pos == previousFromPos)
                board_->get(pos).status_ = CellStatus::PREVIOUS_FROM;
            else if (pos == previousToPos)
                board_->get(pos).status_ = CellStatus::PREVIOUS_TO;
            else if (!(currentPosStatus == CurrentPosStatus::SELECTED && currentPos == selectedPos))
                board_->get(pos).status_ = CellStatus::CURRENT;
        }
    }
}

//void viewCurses::setCellStatus(ViewCellCurses& cell, const CellStatus& status_) {
//}
//
//void viewCurses::setCellStatus(const Position& pos, const CellStatus& status_) {
//    setCellStatus(board_->get(pos), status_);
//}

void ViewCurses::updatePositions(const Position& newPos) {
    if (inBoard(newPos)) {
        cerr << "newPos is inBoard!" << endl;
        updateCellStatus(currentPos, 1);
        currentPos = newPos;
        updateCellStatus(currentPos, 0);
        if (previousFromPos.has_value())
            updateCellStatus(previousFromPos.value(), 0);
        if (previousToPos.has_value())
            updateCellStatus(previousToPos.value(), 0);
    }
}

// TODO(23jura23) rename markSelection? and 0/1 for select/unselect. or markSelected?
void ViewCurses::selectPosition() {
    if (board_->get(currentPos).cell_.figure_.has_value() &&
        board_->get(currentPos).cell_.figure_->colour_ == controller_->getCurrentPlayer()) {
        cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was selected" << endl;
        // Cell with figure was selected

        currentPosStatus = CurrentPosStatus::SELECTED;
        selectedPos = currentPos;
        controller_->selectCell<viewCurses::ViewCurses>(board_->get(selectedPos).cell_);
        fetchModel();
        board_->get(selectedPos).status_ = CellStatus::SELECTED;
    } else {
        cerr << "Empty cell " << currentPos.posW() << ' ' << currentPos.posH()
             << " was tried to be selected (unsuccessfully)" << endl;
        // Empty cell was selected
    }
}

void ViewCurses::unselectPosition() {
    cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was unselected" << endl;
    // Cell was unselected

    reloadModel();
    board_->get(currentPos).status_ = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void ViewCurses::makeUniStep() {
    cerr << "UniStep " << currentPos.posW() << ' ' << currentPos.posH() << " was done" << endl;
    controller_->makeMove(board_->get(currentPos).inMoves_[0]);
    reloadModel();
    board_->get(currentPos).status_ = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void ViewCurses::makeMultiStep_TransformMove(std::vector<Move>& inMoves_) {
    cerr << "transform move" << endl;
    // TODO(23jura23) unneeded?
    //                                        updatePositions(newPos);
    vector<shared_ptr<Figure>> potentialFigures(inMoves_.size());
    for (size_t i = 0; i < inMoves_.size(); ++i)
        potentialFigures[i] = make_shared<Figure>(inMoves_[i].to_figure_new_);

    bool running_transform = 1;
    int currentIndex = 0;
    auto& currentCell = board_->viewBoard_[currentPos.posW()][currentPos.posH()];
    char c_transform;
    while (running_transform) {
        currentCell.cell_.figure_.emplace(*potentialFigures[currentIndex]);
        draw();
        c_transform = getch();  // TODO(23jura23) AAAAA. All getch must be in multiplexer
        //TODO(23jura23) blinking
        switch (c_transform) {
            case 'r':
                currentIndex = (currentIndex + 1) % inMoves_.size();
                break;
            case 'f':
                currentIndex = (currentIndex - 1 + inMoves_.size()) % inMoves_.size();
                break;
            case 32:
                // TODO(23jura23) function for local makeMove, lambda? function in run()?
                controller_->makeMove(board_->get(currentPos).inMoves_[currentIndex]);
                reloadModel();
                board_->get(currentPos).status_ = CellStatus::INACTIVE;
                currentPosStatus = CurrentPosStatus::UNSELECTED;
                running_transform = 0;
                break;
        };
    }
}

void ViewCurses::makeMultiStep() {
    cerr << "MultiStep " << currentPos.posW() << ' ' << currentPos.posH()
         << " was triedto be done (yet "
            "unsuccessfully)"
         << endl;
    auto& inMoves_ = board_->get(currentPos).inMoves_;
    cerr << "inMoves size: " << inMoves_.size() << endl;
    //TODO(23jura23) first-match choice of succeeded MultiSteps' checks
    constexpr auto transformMoveCheck = [](std::vector<Move>& inMoves) {
        bool result = 1;
        if (inMoves.empty())
            result = 0;
        for (auto& inMove : inMoves) {
            if (inMove.from_figure_old_ == inMove.to_figure_new_) {
                result = 0;
                break;
            }
        }
        return result;
    };
    cerr << "Check result: " << transformMoveCheck(inMoves_) << endl;
    if (transformMoveCheck(inMoves_)) {
        makeMultiStep_TransformMove(inMoves_);
    }
    // multiple steps to the same cell are
    // possible
}

RET_CODE ViewCurses::show(int c) {
    //    run();
    //    terminateCurses();
    //}
    //
    //void ViewCurses::run() {
    //    bool running = 1;
    //    while (running) {
    RET_CODE rc = RET_CODE::NOTHING;

    Position newPos = currentPos;
    draw();
    winner = controller_->getGameStatus();

    // !!! TODO(23jura23) move this bottom!

    if (winner != GameStatus::game_running_) {
        // but you need to make universal interface of multistep, where unistep is just multistep with only one possible move. And blinking will be just the implementation for TransformMove
        // TODO(23jura23) think about appearing sliding menu in left or right part of screen
        if (winner == GameStatus::game_over_white_win_) {
            clear();
            move(0, 0);
            printw("White win!");
            refresh();
            usleep(7000000);
            return RET_CODE::GAME_OVER_WHITE_WIN;
        } else if (winner == GameStatus::game_over_black_win_) {
            clear();
            move(0, 0);
            printw("Black win!");
            refresh();
            usleep(7000000);
            return RET_CODE::GAME_OVER_BLACK_WIN;
        } else {
            clear();
            move(0, 0);
            printw("Unexcepectedly, game finished!..");
            refresh();
            usleep(15000000);
            return RET_CODE::GAME_OVER_UNEXPECTEDLY;
        }
    }
    //    chtype c = getch();

    switch (c) {
        case 'x':
            rc = RET_CODE::GAME_EXIT;
            break;
        case 'h':
            if (!historyMenuEnabled) {
                rc = RET_CODE::HISTORY_MENU_ENABLE;
            } else {
                rc = RET_CODE::HISTORY_MENU_DISABLE;
            }
            historyMenuEnabled ^= 1;
            break;
        case -10:  // ask to reload
            reloadModel();
            break;
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
        case 'c':
            reloadModel();
            board_->get(currentPos).status_ = CellStatus::INACTIVE;
            currentPosStatus = CurrentPosStatus::UNSELECTED;
            break;
        case 'u':
            controller_->prevMove();
            reloadModel();
            //            rc = RET_CODE::DO_RELOAD_MODEL;
            // cancel move?
            // undo
            break;
        case 85:  // Shift-u
            controller_->nextMove();
            reloadModel();
            //            rc = RET_CODE::DO_RELOAD_MODEL;
            // redo
            break;
        case 27:
            return RET_CODE::GAME_EXIT;
            break;
        case 32:
            switch (currentPosStatus) {
                case CurrentPosStatus::UNSELECTED:
                    selectPosition();
                    break;
                case CurrentPosStatus::SELECTED:
                    cerr << "Trying to do smth with Cell " << currentPos.posW() << ' '
                         << currentPos.posH() << endl;
                    if (currentPos == selectedPos) {
                        unselectPosition();
                    } else {
                        if (board_->get(currentPos).inMoves_.size()) {
                            cerr << "Step " << currentPos.posW() << ' ' << currentPos.posH()
                                 << " was tried to be done" << endl;
                            if (board_->get(currentPos).inMoves_.size() == 1) {
                                makeUniStep();
                            } else {
                                makeMultiStep();
                            }
                            //                                previousFromPos = selectedPos;
                            //                                previousToPos = currentPos;
                        } else {
                            // Impossible move
                        }
                    }
                    break;
            }
            break;
        default:
            break;
    }
    cerr << "newPos: " << newPos.posW() << ' ' << newPos.posH() << endl;
    cerr << "truepos" << newPos.x_ << ' ' << newPos.y_ << ' ' << newPos.z_ << endl;
    updatePositions(newPos);
    draw();
    //        if (inBoard(newPos)) {
    //            currentPos = newPos;
    //            updateCellsStatus();
    //        }
    return rc;
}

void ViewCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel) {
    board_ = newModel;
}

void ViewCurses::fetchModel() {
    updateModel(
        std::dynamic_pointer_cast<ViewModelCurses>(controller_->getViewModel<ViewCurses>()));
}

void ViewCurses::reloadModel() {
    controller_->updateViewModel<ViewCurses>();
    fetchModel();
    if (board_->history_of_moves_.size() && board_->point_of_history_ > 0) {
        previousFromPos = board_->history_of_moves_[board_->point_of_history_ - 1].from_;
        previousToPos = board_->history_of_moves_[board_->point_of_history_ - 1].to_;
    }
    else {
        previousFromPos.reset();
        previousToPos.reset();
    }
}

void ViewCurses::draw() {
    //    clear();
    calculateTL();
    outBoard();
    refresh();
}

auto ViewCurses::getTL(pair corner) -> pair {
    return {tlx + corner.first / 2 * delta_right_up.first +
                (corner.first % 2) * delta_right_down.first - (d - 1),
            tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second};
    // TODO rewrite more beautiful
}

void ViewCurses::outBoard() {
    for (size_t x = 0; x < board_->viewBoard_.size(); ++x)
        for (size_t y = 0; y < board_->viewBoard_[x].size(); ++y) {
            size_t cor_x = x;
            size_t cor_y = board_->viewBoard_[x].size() - 1 - y;
            outCell(board_->viewBoard_[cor_x][cor_y], getTL({x, y}));
        }
}

void ViewCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL) {
    int FIGURE_COLOR = -1;
    int CELL_COLOR = -1;
    int LETTER_COLOR = -1;
    switch (cell.status_) {
        case CellStatus::INACTIVE:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE;
            else
                CELL_COLOR = CELL_BLACK;
            break;
        case CellStatus::ACTIVE:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_ACTIVE;
            else
                CELL_COLOR = CELL_BLACK_ACTIVE;
            break;
        case CellStatus::CURRENT:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_CURRENT;
            else
                CELL_COLOR = CELL_BLACK_CURRENT;
            break;
        case CellStatus::SELECTED:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_SELECTED;
            else
                CELL_COLOR = CELL_BLACK_SELECTED;
            break;
        case CellStatus::PREVIOUS_FROM:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_PREVIOUS_FROM;
            else
                CELL_COLOR = CELL_BLACK_PREVIOUS_FROM;
            break;
        case CellStatus::PREVIOUS_TO:
            if (cell.cell_.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_PREVIOUS_TO;
            else
                CELL_COLOR = CELL_BLACK_PREVIOUS_TO;
            break;
    }
    std::vector<const char*> draw;  // TODO(23jura23) move to files
    if (!cell.cell_.figure_.has_value()) {
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
        FigureType figureT = cell.cell_.figure_.value().type_;
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
                draw = {"````###########````",
                        "```# +   +   + #```",
                        "``#   + +++ +   #``",
                        "`#     +   +     #`",
                        "#     ++ D ++     #",
                        "`#     +   +     #`",
                        "``#   + +++ +   #``",
                        "```# +   +   + #```",
                        "````###########````"};
                break;
            case FigureType::AGGRESSOR:
                draw = {"````###########````",
                        "```#           #```",
                        "``# !!!!!!!!!!! #``",
                        "`#   !!     !!   #`",
                        "#     !! A !!     #",
                        "`#     !! !!     #`",
                        "``#     !!!     #``",
                        "```#     !     #```",
                        "````###########````"};
                break;
            case FigureType::DEFENSSOR:
                draw = {"````###########````",
                        "```#  !!!!!!!  #```",
                        "``#     !!!     #``",
                        "`#  !! !! !! !!  #`",
                        "#   !!!! d !!!!   #",
                        "`#  !! !! !! !!  #`",
                        "``#     !!!     #``",
                        "```#  !!!!!!!  #```",
                        "````###########````"};

                break;
            case FigureType::LIBERATOR:
                draw = {"````###########````",
                        "```#           #```",
                        "``#  !!!!!!!!!  #``",
                        "`#   !!!   !!!   #`",
                        "#    !!! L !!!    #",
                        "`#   !!!   !!!   #`",
                        "``#  !!!!!!!!!  #``",
                        "```#           #```",
                        "````###########````"};

                break;
            case FigureType::PROGRESSOR:
                draw = {"````###########````",
                        "```#     !     #```",
                        "``#     !!!     #``",
                        "`#    !!! !!!    #`",
                        "#    !!!   !!!    #",
                        "`#   !!! P !!!   #`",
                        "``#  !!!   !!!  #``",
                        "```# !!!!!!!!! #```",
                        "````###########````"};
                break;
        }
        if (cell.cell_.figure_->colour_ == PlayerColour::white_) {
            if (cell.cell_.colour_ == CellColour::WHITE) {
                FIGURE_COLOR = WOW;
            } else {
                FIGURE_COLOR = WOB;
            }
            LETTER_COLOR = LETTER_WHITE;
        } else {
            if (cell.cell_.colour_ == CellColour::WHITE) {
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
        //  if (cell.cell.figure_.has_value()
        //      && cell.cell.figure_->colour_ == PlayerColour::black_
        //      && cell.cell.figure_->type_ != FigureType::INTELLECTOR)
        //      draw_i = draw.size() - 1 - i;
        //  inverts black figures
        //  add as feature
        if (TL.second + i <= static_cast<size_t>(maxy) && TL.first <= static_cast<size_t>(maxx)) {
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
