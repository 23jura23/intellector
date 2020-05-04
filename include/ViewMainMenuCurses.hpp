#ifndef _VIEW_MAIN_MENU_CURSES_HPP_
#define _VIEW_MAIN_MENU_CURSES_HPP_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ViewButtonCurses.hpp"
#include "ViewMenuCurses.hpp"
#include "ViewPictureCurses.hpp"

namespace viewCurses {

class MainMenuCurses final : MenuCurses {
   public:
    MainMenuCurses();
    void show() override;

   private:
    void draw();
    void run();  // TODO class runner with its own state

    void alignWidth(Picture&, size_t);  // TODO separe it, but where to...
    void addButton(std::shared_ptr<Button>);
    void drawButton(std::pair<size_t, size_t> TL, const Picture&);  // top left angle

    void buttonsStateUpdate();

    int currentButtonIndex_;  // optional - allow to be unselected?

    const std::vector<std::pair<std::string, BUTTON_STYLE>> buttonsFilenames_ = {
        {"resources/newgame.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/rules.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/contacts.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/exit.btn", BUTTON_STYLE::RECTANGLE}};

    size_t maxButtonWidth_;
    std::vector<std::shared_ptr<Button>> buttons_;  // need object Button
    const size_t topInitial_ = 5;  // y coordinate of top left angle, x is computed in runtime
    const size_t verticalInterval_ = 3;
};  // class MainMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MAIN_MENU_CURSES_HPP_
