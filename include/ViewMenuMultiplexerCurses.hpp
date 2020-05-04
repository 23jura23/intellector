#ifndef _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
#define _VIEW_MENU_MULTIPLEXER_CURSES_HPP_

#include "ViewMenuCurses.hpp"

namespace viewCurses {

enum class RET_CODE { NOTHING, FAILURE, START_NEW_GAME, EXIT };

class MenuMultiplexerCurses final : public MenuCurses {
   public:
    RET_CODE show() override;
   private:
    RET_CODE launchNewGame();
};  // class MenuMultiplexerCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
