#ifndef _VIEW_HISTORY_MENU_CURSES_HPP_
#define _VIEW_HISTORY_MENU_CURSES_HPP_

#include <memory>

#include "Controller.hpp"
#include "ViewMenuCurses.hpp"
#include "ViewModelCurses.hpp"

namespace viewCurses {

struct HistoryMenuCurses final : MenuCurses {
    HistoryMenuCurses(std::shared_ptr<Controller>);
    RET_CODE show(int c) override;
    MENU_TYPE type() const override;

   private:
    void draw();

    void updateModel(std::shared_ptr<ViewModelCurses>);
    void fetchModel();
    void reloadModel();

    std::shared_ptr<Controller> controller_;
    std::shared_ptr<ViewModelCurses> board_;

    size_t upperMargin = 0;
    size_t cellWidth_ = 20;
    size_t cellHeight_ = 4;
};  // struct HistoryMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_HISTORY_MENU_CURSES_HPP_
