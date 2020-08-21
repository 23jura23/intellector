#include "View/Curses/Menu/Menus/Options/Appearance/Options_Appearance_Menu.hpp"

#include <assert.h>

#include "View/Curses/Menu/MenuTypes.hpp"
#include "View/Curses/Menu/Multiplexer/MenuMultiplexer.hpp"
#include "View/Curses/Model/ModelImpl/ColorScheme/ColorScheme.hpp"

namespace viewCurses {

Options_Appearance_MenuCurses::Options_Appearance_MenuCurses()
    : MainMenuCurses{{{"resources/classic.btn", BUTTON_STYLE::RECTANGLE},
                      {"resources/dracula.btn", BUTTON_STYLE::RECTANGLE},
                      {"resources/snow_blue.btn", BUTTON_STYLE::RECTANGLE},
                      {"resources/back.btn", BUTTON_STYLE::RECTANGLE}}} {
}

RET_CODE Options_Appearance_MenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
        case 'w':
        case KEY_UP:
            if (buttons_.size() > 0) {
                currentButtonIndex_ = (currentButtonIndex_ - 1 + buttons_.size()) % buttons_.size();
                draw();
            }
            break;
        case 's':
        case KEY_DOWN:
            if (buttons_.size() > 0) {
                currentButtonIndex_ = (currentButtonIndex_ + 1) % buttons_.size();
                draw();
            }
            break;
        case 27:  // ESC
            rc = RET_CODE::BACK;
            break;
        case 32:
            // assuming correct buttons order:
            // classic
            // dracula
            // snow blue
            switch (currentButtonIndex_) {
                case 0:  // classic
                    globalColorScheme::setScheme(globalColorSchemeType::CLASSIC);
                    rc = RET_CODE::NOTHING;
                    break;
                case 1:  // dracula
                    globalColorScheme::setScheme(globalColorSchemeType::DRACULA);
                    rc = RET_CODE::NOTHING;
                    break;
                case 2:  // snow blue
                    globalColorScheme::setScheme(globalColorSchemeType::SNOW_BLUE);
                    rc = RET_CODE::NOTHING;
                    break;
                case 3:  // back
                    rc = RET_CODE::BACK;
                    break;
                default:
                    assert(0);
            }
            break;
        default:
            // do nothing
            break;
    }
    return rc;
}

MENU_TYPE Options_Appearance_MenuCurses::type() const {
    return MENU_TYPE::OPTIONS_APPEARANCE_MENU;
}

};  // namespace viewCurses
