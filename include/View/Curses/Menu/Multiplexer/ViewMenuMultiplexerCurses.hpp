#ifndef _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
#define _VIEW_MENU_MULTIPLEXER_CURSES_HPP_

#include <unordered_map>
#include <vector>

#include "Controller/Controller.hpp"
#include "Model/ModelImpl/GameSettings.hpp"
#include "View/Curses/Menu/ViewMenuCurses.hpp"

namespace viewCurses {

enum class RET_CODE {
    NOTHING,
    FAILURE,

    START_NEW_GAME,
    RULES_MENU,
    OPTIONS_MENU,
    EXIT,  // TODO rename to START_MENU_EXIT
    BACK,

    HISTORY_MENU_ENABLE,
    HISTORY_MENU_DISABLE,
    DO_RELOAD_MODEL,

    GAME_OVER_WHITE_WIN,
    GAME_OVER_BLACK_WIN,
    GAME_OVER_UNEXPECTEDLY,
    GAME_EXIT,

    OPTIONS_GAMEPLAY
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
    std::shared_ptr<Controller> getController();
    std::optional<std::shared_ptr<Controller>> controller__;
    std::shared_ptr<Game> getGame();
    std::optional<std::shared_ptr<Game>> game__;
    
    std::shared_ptr<MenuCurses> launchNewGame();
    GameSettings settings_;

    //    template <MULTIPLEXABLE_MENU, typename... Args>
    //    std::shared_ptr<MenuCurses> createMenu(const Args&...);
    std::vector<MenuWithRC> aliveMenus;

    bool forceRedraw = 0;

    RET_CODE processWelcomeMenu(MenuWithRC&);
    RET_CODE processStartMenu(MenuWithRC&);
    RET_CODE processGameMenu(MenuWithRC&);
    RET_CODE processRulesMenu(MenuWithRC&);
    RET_CODE processOptionsMenu(MenuWithRC&);
    RET_CODE processOptions_Gameplay_Menu(MenuWithRC&);
    RET_CODE processHistoryMenu(MenuWithRC&);
    RET_CODE processWinMenu(MenuWithRC&);

};  // class MenuMultiplexerCurses

}  // namespace viewCurses

#endif  // _VIEW_MENU_MULTIPLEXER_CURSES_HPP_
