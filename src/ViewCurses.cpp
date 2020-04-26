
#include "ViewCurses.hpp"

#include <assert.h>
#include <unistd.h>

#include <iostream>

#include "Board.hpp"
#include "Controller.hpp"
#include "Figure.hpp"

using namespace std;

#define BLACK_AND_WHITE

#ifdef BLACK_AND_WHITE
    #define COLOR_WHITE_CELL          255
    #define COLOR_BLACK_CELL          237
    #define COLOR_WHITE_FIGURE        187
    #define COLOR_BLACK_FIGURE        137
    #define COLOR_WHITE_ACTIVE        88
    #define COLOR_BLACK_ACTIVE        88
    #define COLOR_WHITE_CURRENT       123
    #define COLOR_BLACK_CURRENT       111
    #define COLOR_WHITE_SELECTED      56
    #define COLOR_BLACK_SELECTED      55
    #define COLOR_WHITE_PREVIOUS_FROM 78
    #define COLOR_BLACK_PREVIOUS_FROM 76
    #define COLOR_WHITE_PREVIOUS_TO   79
    #define COLOR_BLACK_PREVIOUS_TO   77
    #define COLOR_WHITE_LETTER        196
    #define COLOR_BLACK_LETTER        226
    #define COLOR_FORE_BORDER         238
    #define COLOR_BACK_BORDER         241
#elif defined(CLASSIC)
    #define COLOR_WHITE_CELL          187
    #define COLOR_BLACK_CELL          137
    #define COLOR_WHITE_FIGURE        231
    #define COLOR_BLACK_FIGURE        0
    #define COLOR_WHITE_ACTIVE        82
    #define COLOR_BLACK_ACTIVE        70
    #define COLOR_WHITE_CURRENT       123
    #define COLOR_BLACK_CURRENT       111
    #define COLOR_WHITE_SELECTED      56
    #define COLOR_BLACK_SELECTED      55
    #define COLOR_WHITE_PREVIOUS_FROM 79
    #define COLOR_BLACK_PREVIOUS_FROM 77
    #define COLOR_WHITE_PREVIOUS_TO   83
    #define COLOR_BLACK_PREVIOUS_TO   84
    #define COLOR_WHITE_LETTER        196
    #define COLOR_BLACK_LETTER        226
    #define COLOR_FORE_BORDER         238
    #define COLOR_BACK_BORDER         241
#endif

#define WOW 100  // White On White
#define WOB 101  // White On Black
#define BOW 102  // Black On White
#define BOB 103  // Black On Black
// #define WOA 104  // White On Active
// #define BOA 105  // Black On Active
#define CELL_WHITE               200  // INACTIVE
#define CELL_BLACK               201  // INACTIVE
#define CELL_WHITE_ACTIVE        202  // ACTIVE
#define CELL_BLACK_ACTIVE        203  // ACTIVE
#define CELL_WHITE_CURRENT       204  // CURRENT
#define CELL_BLACK_CURRENT       205  // CURRENT
#define CELL_WHITE_SELECTED      206  // SELECTED
#define CELL_BLACK_SELECTED      207  // SELECTED
#define CELL_WHITE_PREVIOUS_FROM 208  // PREVIOUS_FROM
#define CELL_BLACK_PREVIOUS_FROM 209  // PREVIOUS_FROM
#define CELL_WHITE_PREVIOUS_TO   210  // PREVIOUS_TO
#define CELL_BLACK_PREVIOUS_TO   211  // PREVIOUS_TO
#define CELL_BORDER              220
#define LETTER_BLACK             221
#define LETTER_WHITE             222

#define CENTER_ALIGN 1
// TODO add to config/settings

using namespace ViewCurses;

void viewCurses::calculateTL() {
    tlx = 0;
    tly = 0;
    maxy = getmaxy(stdscr);
    maxx = getmaxx(stdscr);

    if (CENTER_ALIGN) {
        size_t leny = 0;
        for (size_t i = 0; i < board_->viewBoard.size(); ++i) {
            size_t j = board_->viewBoard[i].size();
            leny = max(leny, getTL({i, j}).second);
        }
        size_t lenx = 0;
        if (board_->cols <= 0)
            throw ViewBaseException("Width of board must be positive");
        for (size_t j = 0; j < board_->viewBoard[board_->cols - 1].size(); ++j) {
            lenx = max(lenx, getTL({board_->cols, j}).first);
        }
        tlx = maxx / 2 - lenx / 2;
        tly = maxy / 2 - leny / 2;
    } else {
        tlx = d - 1;
        tly = 0;
    }
}

viewCurses::viewCurses(std::shared_ptr<Controller> controller)
        : controller_{controller}
        , tlx{0}
        , tly{0}
        , currentPos{-2, 3, 2}
        , currentPosStatus{CurrentPosStatus::UNSELECTED} {
    freopen("error.txt", "a", stderr);

    fetchModel();
    updateCellStatus(currentPos, 1);
    updateCellStatus(currentPos, 0);

    initscr();
    calculateTL();

    if (!has_colors()) {
        endwin();
        throw ViewBaseException("Your terminal does not support colors");
    }
    use_default_colors();
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
    init_pair(CELL_WHITE_PREVIOUS_FROM, COLOR_WHITE_PREVIOUS_FROM, COLOR_WHITE_PREVIOUS_FROM);
    init_pair(CELL_BLACK_PREVIOUS_FROM, COLOR_BLACK_PREVIOUS_FROM, COLOR_BLACK_PREVIOUS_FROM);
    init_pair(CELL_WHITE_PREVIOUS_TO, COLOR_WHITE_PREVIOUS_TO, COLOR_WHITE_PREVIOUS_TO);
    init_pair(CELL_BLACK_PREVIOUS_TO, COLOR_BLACK_PREVIOUS_TO, COLOR_BLACK_PREVIOUS_TO);
    init_pair(CELL_BORDER, COLOR_FORE_BORDER, COLOR_BACK_BORDER);
    init_pair(LETTER_WHITE, COLOR_WHITE_LETTER, COLOR_WHITE_FIGURE);
    init_pair(LETTER_BLACK, COLOR_BLACK_LETTER, COLOR_BLACK_FIGURE);

    //    keypad(stdscr, true);
    //    otherwise ESC does not work, see
    //    https://www.daniweb.com/programming/software-development/threads/259439/keycode-of-esc-in-curses-h
    //    other solutions: nocbreak(); or timeout(0); or not using ESC to cancel
    curs_set(0);
    noecho();
}

viewCurses::~viewCurses() {
    use_default_colors();
    endwin();
}

void viewCurses::updateCellStatus(const Position& pos, bool before) {
    if (inBoard(pos)) {
        if (before) {
            // update status before pointer moves
            if (currentPosStatus == CurrentPosStatus::SELECTED && currentPos.equal<2>(selectedPos))
                board_->get(pos).status = CellStatus::SELECTED;
            else if (board_->get(pos).inMoves.size())
                board_->get(pos).status = CellStatus::ACTIVE;
            else
                board_->get(pos).status = CellStatus::INACTIVE;
        } else {
            // update status after pointer moves
            if (pos == previousFromPos)
                board_->get(pos).status = CellStatus::PREVIOUS_FROM;
            else if (pos == previousToPos)
                board_->get(pos).status = CellStatus::PREVIOUS_TO;
            else if (!(currentPosStatus == CurrentPosStatus::SELECTED &&
                       currentPos.equal<2>(selectedPos)))
                board_->get(pos).status = CellStatus::CURRENT;
        }
    }
}

void viewCurses::setCellStatus(ViewCellCurses& cell, const CellStatus& status) {
}

void viewCurses::setCellStatus(const Position& pos, const CellStatus& status) {
    setCellStatus(board_->get(pos), status);
}

void viewCurses::updatePositions(const Position& newPos) {
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
void viewCurses::selectPosition() {
    if (board_->get(currentPos).cell.figure_.has_value() &&
        board_->get(currentPos).cell.figure_->colour_ == controller_->getCurrentPlayer()) {
        cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was selected" << endl;
        // Cell with figure was selected

        currentPosStatus = CurrentPosStatus::SELECTED;
        selectedPos = currentPos;
        controller_->selectCell<ViewCurses::viewCurses>(board_->get(selectedPos).cell);
        fetchModel();
        board_->get(selectedPos).status = CellStatus::SELECTED;
    } else {
        cerr << "Empty cell " << currentPos.posW() << ' ' << currentPos.posH()
             << " was tried to be selected (unsuccessfully)" << endl;
        // Empty cell was selected
    }
}

void viewCurses::unselectPosition() {
    cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was unselected" << endl;
    // Cell was unselected

    reloadModel();
    board_->get(currentPos).status = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void viewCurses::makeUniStep() {
    cerr << "UniStep " << currentPos.posW() << ' ' << currentPos.posH() << " was done" << endl;
    controller_->makeMove(board_->get(currentPos).inMoves[0]);
    reloadModel();
    board_->get(currentPos).status = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void viewCurses::makeMultiStep_TransformMove(std::vector<Move>& inMoves) {
    cerr << "transform move" << endl;
    // TODO(23jura23) unneeded?
    //                                        updatePositions(newPos);
    vector<shared_ptr<Figure>> potentialFigures(inMoves.size());
    for (size_t i = 0; i < inMoves.size(); ++i)
        potentialFigures[i] = make_shared<Figure>(inMoves[i].to_figure_new_);

    bool running_transform = 1;
    int currentIndex = 0;
    auto& currentCell = board_->viewBoard[currentPos.posW()][currentPos.posH()];
    char c_transform;
    while (running_transform) {
        currentCell.cell.figure_.emplace(*potentialFigures[currentIndex]);
        refreshView();
        c_transform = getch();
        //TODO(23jura23) blinking
        switch (c_transform) {
            case 'r':
                currentIndex = (currentIndex + 1) % inMoves.size();
                break;
            case 'f':
                currentIndex = (currentIndex - 1 + inMoves.size()) % inMoves.size();
                break;
            case 32:
                // TODO(23jura23) function for local makeMove, lambda? function in run()?
                controller_->makeMove(board_->get(currentPos).inMoves[currentIndex]);
                reloadModel();
                board_->get(currentPos).status = CellStatus::INACTIVE;
                currentPosStatus = CurrentPosStatus::UNSELECTED;
                running_transform = 0;
                break;
        };
    }
}

void viewCurses::makeMultiStep() {
    cerr << "MultiStep " << currentPos.posW() << ' ' << currentPos.posH()
         << " was triedto be done (yet "
            "unsuccessfully)"
         << endl;
    auto& inMoves = board_->get(currentPos).inMoves;
    cerr << "inMoves size: " << inMoves.size() << endl;
    //TODO(23jura23) first-match choice of succeeded MultiSteps' checks
    constexpr auto transformMoveCheck = [](std::vector<Move>& inMoves_) {
        bool result = 1;
        if (inMoves_.empty())
            result = 0;
        for (auto& inMove : inMoves_) {
            if (inMove.from_figure_old_ == inMove.to_figure_new_) {
                result = 0;
                break;
            }
        }
        return result;
    };
    cerr << "Check result: " << transformMoveCheck(inMoves) << endl;
    if (transformMoveCheck(inMoves)) {
        makeMultiStep_TransformMove(inMoves);
    }
    // multiple steps to the same cell are
    // possible
}

void viewCurses::run() {
    GameStatus winner;
    bool running = 1;
    while (running) {
        Position newPos = currentPos;
        refreshView();
        winner = controller_->getGameStatus();
        if (winner != GameStatus::game_running_) {
            // but you need to make universal interface of multistep, where unistep is just multistep with only one possible move. And blinking will be just the implementation for TransformMove
            // TODO(23jura23) think about appearing sliding menu in left or right part of screen
            if (winner == GameStatus::game_over_white_win_) {
                clear();
                move(0, 0);
                printw("White win!");
                refresh();
                usleep(7000000);
                return;
            } else if (winner == GameStatus::game_over_black_win_) {
                clear();
                move(0, 0);
                printw("Black win!");
                refresh();
                usleep(7000000);
                return;
            } else {
                clear();
                move(0, 0);
                printw("Unexcepectedly, game finished!..");
                refresh();
                usleep(15000000);
                return;
            }
        }
        chtype c = getch();

        switch (c) {
            case 'x':
                running = 0;
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
            case 27:
                reloadModel();
                board_->get(currentPos).status = CellStatus::INACTIVE;
                currentPosStatus = CurrentPosStatus::UNSELECTED;
                break;
            case 32:
                switch (currentPosStatus) {
                    case CurrentPosStatus::UNSELECTED:
                        selectPosition();
                        break;
                    case CurrentPosStatus::SELECTED:
                        cerr << "Trying to do smth with Cell " << currentPos.posW() << ' '
                             << currentPos.posH() << endl;
                        if (currentPos.equal<2>(selectedPos)) {
                            unselectPosition();
                        } else {
                            if (board_->get(currentPos).inMoves.size()) {
                                cerr << "Step " << currentPos.posW() << ' ' << currentPos.posH()
                                     << " was tried to be done" << endl;
                                if (board_->get(currentPos).inMoves.size() == 1) {
                                    makeUniStep();
                                } else {
                                    makeMultiStep();
                                }
                                previousFromPos = selectedPos;
                                previousToPos = currentPos;
                            } else {
                                // Impossible move
                            }
                        }
                        break;
                }
                break;
        }
        cerr << "newPos: " << newPos.posW() << ' ' << newPos.posH() << endl;
        cerr << "truepos" << newPos.x_ << ' ' << newPos.y_ << ' ' << newPos.z_ << endl;
        updatePositions(newPos);
        //        if (inBoard(newPos)) {
        //            currentPos = newPos;
        //            updateCellsStatus();
        //        }
    }
}

void viewCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel) {
    board_ = newModel;
}

void viewCurses::fetchModel() {
    updateModel(
        std::dynamic_pointer_cast<ViewModelCurses>(controller_->getViewModel<viewCurses>()));
}

void viewCurses::reloadModel() {
    controller_->updateViewModel<viewCurses>();
    fetchModel();
}

void viewCurses::refreshView() {
    clear();
    calculateTL();
    outBoard();
    refresh();
}

auto viewCurses::getTL(pair corner) -> pair {
    return {tlx + corner.first / 2 * delta_right_up.first +
                (corner.first % 2) * delta_right_down.first - (d - 1),
            tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second};
    // TODO rewrite more beautiful
}

void viewCurses::outBoard() {
    for (size_t x = 0; x < board_->viewBoard.size(); ++x)
        for (size_t y = 0; y < board_->viewBoard[x].size(); ++y) {
            size_t cor_x = x;
            size_t cor_y = board_->viewBoard[x].size() - 1 - y;
            outCell(board_->viewBoard[cor_x][cor_y], getTL({x, y}));
        }
}

void viewCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL) {
    int FIGURE_COLOR = -1;
    int CELL_COLOR = -1;
    int LETTER_COLOR = -1;
    switch (cell.status) {
        case CellStatus::INACTIVE:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE;
            else
                CELL_COLOR = CELL_BLACK;
            break;
        case CellStatus::ACTIVE:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_ACTIVE;
            else
                CELL_COLOR = CELL_BLACK_ACTIVE;
            break;
        case CellStatus::CURRENT:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_CURRENT;
            else
                CELL_COLOR = CELL_BLACK_CURRENT;
            break;
        case CellStatus::SELECTED:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_SELECTED;
            else
                CELL_COLOR = CELL_BLACK_SELECTED;
            break;
        case CellStatus::PREVIOUS_FROM:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_PREVIOUS_FROM;
            else
                CELL_COLOR = CELL_BLACK_PREVIOUS_FROM;
            break;
        case CellStatus::PREVIOUS_TO:
            if (cell.cell.colour_ == CellColour::WHITE)
                CELL_COLOR = CELL_WHITE_PREVIOUS_TO;
            else
                CELL_COLOR = CELL_BLACK_PREVIOUS_TO;
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
