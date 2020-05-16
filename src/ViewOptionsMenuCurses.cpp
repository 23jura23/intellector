#include "ViewOptionsMenuCurses.hpp"

#include <assert.h>

#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {

OptionsMenuCurses::OptionsMenuCurses()
        : MainMenuCurses{{{"resources/gameplay.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/appearance.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/back.btn", BUTTON_STYLE::RECTANGLE}}} {
    //TODO(23jura23) beatiful button for appearance
}

RET_CODE OptionsMenuCurses::show(int c) {
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
            break;
        case 32:
            // assuming correct buttons order:
            // new game
            // rules
            // contacts
            // options
            // exit
            switch (currentButtonIndex_) {
                case 0:  // gameplay
                    break;
                case 1:  // appearance
                    break;
                case 2:  // back
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

MENU_TYPE OptionsMenuCurses::type() const {
    return MENU_TYPE::OPTIONS_MENU;
}

};  // namespace viewCurses