#ifndef _VIEW_OPTIONS_GAMEPLAY_MENU_CURSES_HPP_
#define _VIEW_OPTIONS_GAMEPLAY_MENU_CURSES_HPP_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Model/ModelImpl/GameSettings.hpp"
#include "View/Curses/Menu/ViewMenuCurses.hpp"
#include "View/Curses/Model/Button/ViewButtonCurses.hpp"

namespace viewCurses {
using buttonsVectorT = std::vector<std::pair<std::string, BUTTON_STYLE>>;

struct Options_Gameplay_MenuCurses final : MenuCurses {
    Options_Gameplay_MenuCurses(const GameSettings&);
    RET_CODE show(int) override;
    MENU_TYPE type() const override;
    GameSettings getRV() const;  // get Return Value

    ~Options_Gameplay_MenuCurses();

   private:
    std::vector<std::vector<std::shared_ptr<Button>>> buttons_;
    std::vector<std::vector<std::pair<std::string, BUTTON_STYLE>>> buttonsFilenames_;
    size_t currentButtonIndexY_;
    size_t currentButtonIndexX_;
    void buttonsStateUpdate();
    std::pair<size_t, size_t> getTL() const;
    void draw();
    void alignWidth(Picture& pic, size_t width);

    GameSettings settings_;

    const size_t topInitial_ = 5;
    const size_t verticalInterval_ = 5;
    const size_t horizontalInterval_ = 3;
    const size_t offsetBots = 2;

};  // class Options_Gameplay_MenuCurses

}  // namespace viewCurses

#endif  // _VIEW_OPTIONS_GAMEPLAY_MENU_CURSES_HPP_
