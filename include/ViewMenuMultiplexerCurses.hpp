#ifndef _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
#define _VIEW_MENU_MULTIPLEXER_CURSES_HPP_

#include <unordered_map>
#include <vector>

#include "ViewMenuCurses.hpp"

namespace viewCurses {

enum class RET_CODE {
    NOTHING,
    FAILURE,

    START_NEW_GAME,
    RULES_MENU,
    OPTIONS_MENU,
    EXIT, // TODO rename to START_MENU_EXIT
    BACK,

    GAME_OVER_WHITE_WIN,
    GAME_OVER_BLACK_WIN,
    GAME_OVER_UNEXPECTEDLY,
    GAME_EXIT
};

//enum class MULTIPLEXABLE_MENU { WELCOME_MENU, MAIN_MENU, GAME_MENU };

struct MenuWithRC {  // Menu with return code
    std::shared_ptr<MenuCurses> menu;
    RET_CODE rc;
    bool operator==(const MenuWithRC& other);
};

class MenuMultiplexerCurses final : public MenuCurses {
   public:
    MenuMultiplexerCurses();
    ~MenuMultiplexerCurses();
    RET_CODE show(int c = 0) override;

    MENU_TYPE type() const override;

   private:
    std::shared_ptr<MenuCurses> launchNewGame();

    //    template <MULTIPLEXABLE_MENU, typename... Args>
    //    std::shared_ptr<MenuCurses> createMenu(const Args&...);
    std::vector<MenuWithRC> aliveMenus;

    RET_CODE processWelcomeMenu(MenuWithRC&);
    RET_CODE processStartMenu(MenuWithRC&);
    RET_CODE processGameMenu(MenuWithRC&);
    RET_CODE processRulesMenu(MenuWithRC&);
    RET_CODE processOptionsMenu(MenuWithRC&);

};  // class MenuMultiplexerCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
