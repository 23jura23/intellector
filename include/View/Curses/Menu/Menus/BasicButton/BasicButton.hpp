#ifndef _VIEW_MAIN_MENU_CURSES_HPP_
#define _VIEW_MAIN_MENU_CURSES_HPP_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "View/Curses/Menu/Menu.hpp"
#include "View/Curses/Model/Button/Button.hpp"
#include "View/Curses/Model/ModelImpl/Picture/Picture.hpp"

namespace viewCurses {
using buttonsVectorT = std::vector<std::pair<std::string, BUTTON_STYLE>>;

class MainMenuCurses : public MenuCurses {
   public:
    MainMenuCurses(buttonsVectorT);
    ~MainMenuCurses();  // rule of 5?
//    /*virtual ? */ RET_CODE show(int) = 0;

    MENU_TYPE type() const override;

   protected:
    virtual void draw();
    virtual std::pair<size_t, size_t> getTL() const;
    //    int run();  // TODO class runner with its own state

    void alignWidth(Picture&, size_t);  // TODO separe it, but where to...
    void addButton(std::shared_ptr<Button>);
    void drawButton(std::pair<size_t, size_t> TL, const Picture&);  // top left angle

    void buttonsStateUpdate();

    int currentButtonIndex_;  // optional - allow to be unselected?

    size_t maxButtonWidth_, maxButtonHeight_;
    std::vector<std::shared_ptr<Button>> buttons_;  // need object Button
    const size_t topInitial_ = 5;  // y coordinate of top left angle, x is computed in runtime
    const size_t verticalInterval_ = 3;
    const size_t horizontalInterval_ = 3;
};  // class MainMenuCurses

}  // namespace viewCurses

#endif  // _VIEW_MAIN_MENU_CURSES_HPP_
