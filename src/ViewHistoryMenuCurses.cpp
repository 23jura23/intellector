#include "ViewHistoryMenuCurses.hpp"

#include <assert.h>

#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {
HistoryMenuCurses::HistoryMenuCurses(std::shared_ptr<Controller> controller)
        : controller_{controller} {
}

RET_CODE HistoryMenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
            //        case 104:  // h
            //            rc = RET_CODE::HISTORY_MENU_;
            //            break;
        case 117:  // u
            controller_->prevMove();
            reloadModel();
            rc = RET_CODE::DO_RELOAD_MODEL;
            // cancel move?
            // undo
            break;
        case 85:  // Shift-u
            controller_->nextMove();
            reloadModel();
            rc = RET_CODE::DO_RELOAD_MODEL;
            // redo
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
            
        }

        move(y + cellHeight_ - 1, xStartPos);
        for (size_t j = 0; j < cellWidth_; ++j) {
            addch('=');
        }
    }

    move(5, 5);
    addch('!');
}

MENU_TYPE HistoryMenuCurses::type() const {
    return MENU_TYPE::HISTORY_MENU;
}

void HistoryMenuCurses::updateModel(std::shared_ptr<ViewModelCurses> newModel) {
    board_ = newModel;
}

void HistoryMenuCurses::fetchModel() {
    updateModel(
        std::dynamic_pointer_cast<ViewModelCurses>(controller_->getViewModel<ViewCurses>()));
}

void HistoryMenuCurses::reloadModel() {
    controller_->updateViewModel<ViewCurses>();
    fetchModel();
}

}  // namespace viewCurses
