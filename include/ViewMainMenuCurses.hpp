#ifndef _VIEW_MAIN_MENU_CURSES_HPP_
#define _VIEW_MAIN_MENU_CURSES_HPP_

#include <string>
#include <vector>

#include "PictureCurses.hpp"
#include "ViewMenuCurses.hpp"

namespace viewCurses {

class MainMenuCurses final : MenuCurses {
   public:
    MainMenuCurses();
    void show() override;

   private:
    enum class BUTTON_STYLE { RECTANGLE, ZIGZAG };

    Picture wrapInButton_RECTANGLE(Picture pic);
    Picture wrapInButton_ZIGZAG(Picture pic);

    Picture wrapInButton(Picture, BUTTON_STYLE);

    void alignWidth(Picture&, size_t);
    void addButton(const Picture&);
    void showButton(const Picture&, std::pair<size_t, size_t> TL);  // top left angle

    int currentButtonIndex_;

    const std::vector<std::pair<std::string, BUTTON_STYLE>> buttonsFilenames = {
        {"resources/newgame.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/rules.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/contacts.btn", BUTTON_STYLE::RECTANGLE},
        {"resources/exit.btn", BUTTON_STYLE::RECTANGLE}
    };

    size_t maxButtonWidth;
    std::vector<Picture> buttons;
    const size_t topInitial = 5;  // y coordinate of top left angle, x is computed in runtime
    const size_t verticalInterval = 3;
};  // class MainMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MAIN_MENU_CURSES_HPP_
