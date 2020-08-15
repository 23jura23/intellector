#ifndef _VIEW_HISTORY_MENU_CURSES_HPP_
#define _VIEW_HISTORY_MENU_CURSES_HPP_

#include <map>
#include <memory>
#include <string>

#include "Controller/Controller.hpp"
#include "Model/ModelImpl/Figure.hpp"
#include "View/Curses/Menu/ViewMenuCurses.hpp"
#include "View/Curses/Model/ViewModelCurses.hpp"

namespace viewCurses {

struct HistoryMenuCurses final : MenuCurses {
    HistoryMenuCurses(std::shared_ptr<Controller>);
    RET_CODE show(int c) override;
    MENU_TYPE type() const override;

   private:
    Picture toASCIILetters(const std::string&) const;
    Picture drawToNotation(const Move&) const;
    void draw();

    void updateModel(std::shared_ptr<ViewModelCurses>);
    void fetchModel();
    void reloadModel();

    std::shared_ptr<Controller> controller_;
    std::shared_ptr<ViewModelCurses> board_;

    size_t upperMargin = 0;
    size_t cellWidth_ = 15;
    size_t cellHeight_ = 4;

    std::map<FigureType, std::string> figureNotation;
};  // struct HistoryMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_HISTORY_MENU_CURSES_HPP_
