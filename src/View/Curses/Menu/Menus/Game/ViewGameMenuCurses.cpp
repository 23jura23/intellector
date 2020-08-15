#include "View/Curses/Menu/Menus/Game/ViewGameMenuCurses.hpp"

#include <assert.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

#include "Controller/Controller.hpp"
#include "Model/ModelImpl/Board.hpp"
#include "Model/ModelImpl/Figure.hpp"
#include "View/Curses/Menu/Menus/BasicButton/ViewMainMenuCurses.hpp"
#include "View/Curses/Menu/Multiplexer/ViewMenuMultiplexerCurses.hpp"
#include "View/Curses/Menu/ViewMenuTypes.hpp"
#include "View/Curses/Model/ModelImpl/ColorScheme/ViewColorSchemeCurses.hpp"
#include "View/Curses/Model/ModelImpl/Init/ViewInitCurses.hpp"

using namespace std;

#define CENTER_ALIGN 1
// TODO add to config/settings

using namespace viewCurses;

void ViewGameMenuCurses::calculateTL() {  // top left angle
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

ViewGameMenuCurses::ViewGameMenuCurses(std::shared_ptr<Controller> controller)
        : controller_{controller}
        , cellPicturesFilenames_{{DrawCellType::EMPTY, "resources/cellEmpty.btn"},
                                 {DrawCellType::INTELLECTOR, "resources/cellIntellector.btn"},
                                 {DrawCellType::DOMINATOR, "resources/cellDominator.btn"},
                                 {DrawCellType::AGGRESSOR, "resources/cellAggressor.btn"},
                                 {DrawCellType::DEFENSSOR, "resources/cellDeffenssor.btn"},
                                 {DrawCellType::LIBERATOR, "resources/cellLiberator.btn"},
                                 {DrawCellType::PROGRESSOR, "resources/cellProgressor.btn"}}
        , tlx{0}
        , tly{0}
        , currentPos{-2, 3, 2}
        , currentPosStatus{CurrentPosStatus::UNSELECTED} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);
    // avoiding warning. May be harmful, but later there must be a well-done logging.

    for (const auto& [type, filename] : cellPicturesFilenames_) {
        auto is = std::ifstream(filename, std::ios::in);
        is.exceptions(std::ifstream::badbit);
        cellPictures_[type] = Picture{is};
        is.close();
    }

    initCurses();

    fetchModel();
    updateCellStatus(currentPos, 1);
    updateCellStatus(currentPos, 0);
}

ViewGameMenuCurses::~ViewGameMenuCurses() {
    terminateCurses();
}

MENU_TYPE ViewGameMenuCurses::type() const {
    return MENU_TYPE::GAME_MENU;
}

void ViewGameMenuCurses::updateCellStatus(const Position& pos, bool before) {
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

void ViewGameMenuCurses::updatePositions(const Position& newPos) {
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
void ViewGameMenuCurses::selectPosition() {
    if (board_->get(currentPos).cell_.figure_.has_value() &&
        board_->get(currentPos).cell_.figure_->colour_ == controller_->getCurrentPlayer()) {
        cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was selected" << endl;
        // Cell with figure was selected

        currentPosStatus = CurrentPosStatus::SELECTED;
        selectedPos = currentPos;
        controller_->selectCell<viewCurses::ViewGameMenuCurses>(board_->get(selectedPos).cell_);
        fetchModel();
        board_->get(selectedPos).status_ = CellStatus::SELECTED;
    } else {
        cerr << "Empty cell " << currentPos.posW() << ' ' << currentPos.posH()
             << " was tried to be selected (unsuccessfully)" << endl;
        // Empty cell was selected
    }
}

void ViewGameMenuCurses::unselectPosition() {
    cerr << "Cell " << currentPos.posW() << ' ' << currentPos.posH() << " was unselected" << endl;
    // Cell was unselected

    reloadModel();
    board_->get(currentPos).status_ = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void ViewGameMenuCurses::makeUniStep() {
    cerr << "UniStep " << currentPos.posW() << ' ' << currentPos.posH() << " was done" << endl;
    controller_->makeMove(board_->get(currentPos).inMoves_[0]);
    reloadModel();
    board_->get(currentPos).status_ = CellStatus::INACTIVE;
    currentPosStatus = CurrentPosStatus::UNSELECTED;
}

void ViewGameMenuCurses::makeMultiStep_TransformMove(std::vector<Move>& inMoves_) {
    cerr << "transform move" << endl;
    // TODO(23jura23) unneeded?
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

void ViewGameMenuCurses::makeMultiStep() {
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

RET_CODE ViewGameMenuCurses::show(int c) {
    RET_CODE rc = RET_CODE::NOTHING;

    cerr << "PlayerTurn: " << board_->playerTurn << endl;
    cerr << "turn_: " << (board_->turn_ == PlayerColour::white_ ? "white" : "black") << endl;

    if (status == GameStatus::game_running_) {
        if (board_->point_of_history_ == board_->history_of_moves_.size()) {
            if (board_->turn_ == PlayerColour::white_ && board_->settings.first_player()) {
                bool finished = controller_->makeBotMove(PlayerColour::white_);
                if (finished) {
                    reloadModel();
                }
            } else if (board_->turn_ == PlayerColour::black_ && board_->settings.second_player()) {
                bool finished = controller_->makeBotMove(PlayerColour::black_);
                if (finished) {
                    reloadModel();
                }
            }
        }
    }

    Position newPos = currentPos;
    draw();
    status = controller_->getGameStatus();

    // !!! TODO(23jura23) move this bottom!

    if (c != -1) {
        if (status != GameStatus::game_running_) {
            // but you need to make universal interface of multistep, where unistep is just multistep with only one possible move. And blinking will be just the implementation for TransformMove
            // TODO(23jura23) think about appearing sliding menu in left or right part of screen
            if (status == GameStatus::game_over_white_win_) {
                return RET_CODE::GAME_OVER_WHITE_WIN;
            } else if (status == GameStatus::game_over_black_win_) {
                return RET_CODE::GAME_OVER_BLACK_WIN;
            } else {
                return RET_CODE::GAME_OVER_UNEXPECTEDLY;
            }
        }
    }

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
            board_->get(currentPos).status_ = CellStatus::INACTIVE;
            currentPosStatus = CurrentPosStatus::UNSELECTED;
            // undo
            break;
        case 85:  // Shift-u
            controller_->nextMove();
            reloadModel();
            board_->get(currentPos).status_ = CellStatus::INACTIVE;
            currentPosStatus = CurrentPosStatus::UNSELECTED;
            // redo
            break;
        case 27:
            return RET_CODE::GAME_EXIT;
            break;
        case 32:
            if (board_->playerTurn && status == GameStatus::game_running_) {
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
                            } else {
                                // Impossible move
                            }
                        }
                        break;
                }
                break;
            }
        default:
            break;
    }
    cerr << "newPos: " << newPos.posW() << ' ' << newPos.posH() << endl;
    cerr << "truepos" << newPos.x_ << ' ' << newPos.y_ << ' ' << newPos.z_ << endl;
    updatePositions(newPos);
    draw();
    return rc;
}

void ViewGameMenuCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel) {
    board_ = newModel;
}

void ViewGameMenuCurses::fetchModel() {
    updateModel(std::dynamic_pointer_cast<ViewModelCurses>(
        controller_->getViewModel<ViewGameMenuCurses>()));
}

void ViewGameMenuCurses::reloadModel() {
    controller_->updateViewModel<ViewGameMenuCurses>();
    fetchModel();
    if (board_->history_of_moves_.size() && board_->point_of_history_ > 0) {
        previousFromPos = board_->history_of_moves_[board_->point_of_history_ - 1].from_;
        previousToPos = board_->history_of_moves_[board_->point_of_history_ - 1].to_;
    } else {
        previousFromPos.reset();
        previousToPos.reset();
    }
}

void ViewGameMenuCurses::draw() {
    //    clear();
    calculateTL();
    outBoard();
    refresh();
}

auto ViewGameMenuCurses::getTL(pair corner) -> pair {
    return {tlx + corner.first / 2 * delta_right_up.first +
                (corner.first % 2) * delta_right_down.first - (d - 1),
            tly + corner.second * delta_down.second + (corner.first % 2) * delta_right_down.second};
    // TODO rewrite more beautiful
}

void ViewGameMenuCurses::outBoard() {
    for (size_t x = 0; x < board_->viewBoard_.size(); ++x)
        for (size_t y = 0; y < board_->viewBoard_[x].size(); ++y) {
            size_t cor_x = x;
            size_t cor_y = board_->viewBoard_[x].size() - 1 - y;
            outCell(board_->viewBoard_[cor_x][cor_y], getTL({x, y}));
        }
}

void ViewGameMenuCurses::outCell(const ViewModelCurses::ViewCellCurses& cell, pair TL) {
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
    Picture draw;  // TODO(23jura23) move to files
    if (!cell.cell_.figure_.has_value()) {
        draw = cellPictures_.at(DrawCellType::EMPTY);
    } else {
        FigureType figureT = cell.cell_.figure_.value().type_;
        switch (figureT) {
            case FigureType::INTELLECTOR:
                draw = cellPictures_.at(DrawCellType::INTELLECTOR);
                break;
            case FigureType::DOMINATOR:
                draw = cellPictures_.at(DrawCellType::DOMINATOR);
                break;
            case FigureType::AGGRESSOR:
                draw = cellPictures_.at(DrawCellType::AGGRESSOR);
                break;
            case FigureType::DEFENSSOR:
                draw = cellPictures_.at(DrawCellType::DEFENSSOR);
                break;
            case FigureType::LIBERATOR:
                draw = cellPictures_.at(DrawCellType::LIBERATOR);
                break;
            case FigureType::PROGRESSOR:
                draw = cellPictures_.at(DrawCellType::PROGRESSOR);
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
    for (size_t i = 0; i < draw.maxHeight(); ++i) {
        size_t draw_i = i;
        //  if (cell.cell.figure_.has_value()
        //      && cell.cell.figure_->colour_ == PlayerColour::black_
        //      && cell.cell.figure_->type_ != FigureType::INTELLECTOR)
        //      draw_i = draw.size() - 1 - i;
        //  inverts black figures
        //  TODO(23jura23) add as feature
        if (TL.second + i <= static_cast<size_t>(maxy) && TL.first <= static_cast<size_t>(maxx)) {
            move(TL.second + i, TL.first);
            for (size_t j = 0; j < d - 1 + d + d - 1; ++j) {
                if (draw.isIgnoredChar(draw(draw_i, j))) {
                    move(TL.second + i, TL.first + j + 1);
                } else {
                    switch (draw(draw_i, j)) {
                        case ' ':
                            attron(COLOR_PAIR(CELL_COLOR));
                            addch(draw(draw_i, j));
                            attroff(COLOR_PAIR(CELL_COLOR));
                            break;
                        case '#':
                            attron(COLOR_PAIR(CELL_BORDER));
                            addch(draw(draw_i, j));
                            attroff(COLOR_PAIR(CELL_BORDER));
                            break;
                        case 'D':
                        case 'L':
                        case 'A':
                        case 'd':
                        case 'I':
                        case 'P':
                            attron(COLOR_PAIR(LETTER_COLOR));
                            addch(draw(draw_i, j));
                            attroff(COLOR_PAIR(LETTER_COLOR));
                            break;
                        default:
                            attron(COLOR_PAIR(FIGURE_COLOR));
                            addch(draw(draw_i, j));
                            attroff(COLOR_PAIR(FIGURE_COLOR));
                            break;
                    }
                }
            }
        }
    }
}
