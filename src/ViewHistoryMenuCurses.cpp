#include "ViewHistoryMenuCurses.hpp"

#include <assert.h>

#include <iostream>  // TODO delete
#include <sstream>

#include "ViewColorSchemeCurses.hpp"
#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {
HistoryMenuCurses::HistoryMenuCurses(std::shared_ptr<Controller> controller)
        : controller_{controller}
        , figureNotation{{FigureType::INTELLECTOR, "In"},
                         {FigureType::DOMINATOR, "Dm"},
                         {FigureType::AGGRESSOR, "A"},
                         {FigureType::DEFENSSOR, "De"},
                         {FigureType::LIBERATOR, "L"},
                         {FigureType::PROGRESSOR, "P"}}

{
    auto er = freopen("error.txt", "a", stderr);
    static_cast<void>(er);

    reloadModel();
}

RET_CODE HistoryMenuCurses::show(int c) {
    fetchModel();
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
            //        case 104:  // h
            //            rc = RET_CODE::HISTORY_MENU_;
            //            break;
        case -10:
            reloadModel();
            break;
        case 106:  // j
            // move selected history cell bottom
            break;
        case 107:  // k
            // move selected history cell upper
            break;
        case 111:  // o
            // undo to selected history cell
            // TODO is it needed?
            break;
    }
    return rc;
}

Picture HistoryMenuCurses::toASCIILetters(const std::string& str) const {
    // TODO
    auto pic = Picture{std::vector<std::string>{str}, "`"};
    return pic;
}

Picture HistoryMenuCurses::drawToNotation(const Move& move) const {
    std::stringstream notationStream;

    size_t fromPosW = move.from_.posW();
    size_t fromPosH = move.from_.posH() + 1;  // 0-indexed -> 1-indexed
    size_t toPosW = move.to_.posW();
    size_t toPosH = move.to_.posH() + 1;  // 0-indexed -> 1-indexed

    char fromWNotaion = 'a' + fromPosW;
    char toWNotaion = 'a' + toPosW;

    assert('a' <= fromWNotaion && fromWNotaion <= 'z');
    assert('a' <= toWNotaion && toWNotaion <= 'z');

    std::string fromFigureNotation = figureNotation.at(move.from_figure_old_.type_);

    notationStream << fromFigureNotation << "`";
    notationStream << fromWNotaion << fromPosH << "-";
    notationStream << toWNotaion << toPosH;

    std::cerr << "notationStream " << notationStream.str().length() << '`' << notationStream.str()
              << std::endl;

    return toASCIILetters(notationStream.str());
}

void HistoryMenuCurses::draw() {
    assert(getmaxx(stdscr) >= 0);
    size_t maxx = getmaxx(stdscr);
    assert(getmaxy(stdscr) >= 0);
    size_t maxy = getmaxy(stdscr);
    size_t xStartPos = maxx - cellWidth_;

    for (size_t i = 0; (i + 1) * cellHeight_ <= maxy; ++i) {
        //    for (size_t y = upperMargin; y + cellHeight_ <= maxy; y += cellHeight_) {
        size_t y = i * cellHeight_;
        move(y, xStartPos);

        if (i < board_->history_of_moves_.size()) {
            int out_i = board_->history_of_moves_.size() - 1 - i;
            Picture notation = drawToNotation(board_->history_of_moves_[out_i]);
            if (notation.maxWidth() >= cellWidth_)
                throw MenuException("Notation is too big (width) to be drawn");

            size_t yStartPos;
            if (notation.maxHeight() + 1 < cellHeight_) {
                yStartPos = y + cellHeight_ - 1 - notation.maxHeight();
            } else {
                throw MenuException("Notation is too big (height) to be drawn");
            }

            for (size_t j = 0; j < notation.maxHeight(); ++j) {
                bool spaceReached = 0;
                move(yStartPos + j, xStartPos);
                for (size_t u = 0; u < notation(j).size(); ++u) {
                    char c = notation(j, u);
                    if (!notation.isIgnoredChar(c)) {
                        if (!spaceReached) {
                            if (out_i % 2 == 0) {
                                attron(COLOR_PAIR(HISTORY_MENU_FIGURE_LETTER_WHITE));
                                addch(c);
                                attroff(COLOR_PAIR(HISTORY_MENU_FIGURE_LETTER_WHITE));
                            } else {
                                attron(COLOR_PAIR(HISTORY_MENU_FIGURE_LETTER_BLACK));
                                addch(c);
                                attroff(COLOR_PAIR(HISTORY_MENU_FIGURE_LETTER_BLACK));
                            }
                        } else {
                            addch(c);
                        }
                    } else {
                        move(yStartPos + j, xStartPos + u + 1);
                    }
                    if (c == '`') {
                        spaceReached = 1;
                    }
                }
            }
        }

        move(y + cellHeight_ - 1, xStartPos);
        for (size_t j = 0; j < cellWidth_; ++j) {
            attron(COLOR_PAIR(HISTORY_MENU_DELIMETER));
            addch('=');
            attroff(COLOR_PAIR(HISTORY_MENU_DELIMETER));
        }
    }
}

MENU_TYPE HistoryMenuCurses::type() const {
    return MENU_TYPE::HISTORY_MENU;
}

void HistoryMenuCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel) {
    board_ = newModel;
}

void HistoryMenuCurses::fetchModel() {
    updateModel(std::dynamic_pointer_cast<ViewModelCurses>(
        controller_->getViewModel<ViewGameMenuCurses>()));
}

void HistoryMenuCurses::reloadModel() {
    controller_->updateViewModel<ViewGameMenuCurses>();
    fetchModel();
}

}  // namespace viewCurses
