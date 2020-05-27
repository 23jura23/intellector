#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include <memory.h>
#include <ncurses.h>

#include <string>
#include <utility>
#include <vector>

#include "ViewBase.hpp"
#include "ViewMenuCurses.hpp"
#include "ViewModelCurses.hpp"

class Controller;

namespace viewCurses {

class ViewGameMenuCurses : public viewBase, public MenuCurses {
    using pair = std::pair<size_t, size_t>;

   public:
    RET_CODE show(int) override;

    explicit ViewGameMenuCurses(std::shared_ptr<Controller>);
    ~ViewGameMenuCurses();  // rule of 5?

    MENU_TYPE type() const override;

   private:
    void run();
    void fetchModel();
    void reloadModel();
    void updatePositions(const Position&);
    void updateCellStatus(const Position& pos, bool before);
    void setCellStatus(ViewCellCurses& cell, const CellStatus& status);
    void setCellStatus(const Position& pos, const CellStatus& status);
    void updateModel(std::shared_ptr<ViewModelCurses>);
    void draw();

    std::shared_ptr<ViewModelCurses> board_;
    std::shared_ptr<Controller> controller_;

    void outBoard();
    void outCell(const ViewModelCurses::ViewCellCurses&, pair);

    static constexpr size_t d = 7;
    static constexpr pair delta_down = {0, 2 * (d - 3)};
    static constexpr pair delta_right_down = {(d + 3) + (d - 3), d - 3};
    static constexpr pair delta_right_up = {2 * (d + 3) + 2 * (d - 3), 0};

    int maxy, maxx;
    size_t tlx, tly;  //top left x y
    void calculateTL();

    pair getTL(pair);  //get top left corner coordinates of cell

    Position currentPos;
    enum class CurrentPosStatus { UNSELECTED, SELECTED } currentPosStatus;
    Position selectedPos;
    std::optional<Position> previousFromPos;
    std::optional<Position> previousToPos;
    
    GameStatus status;

    bool historyMenuEnabled = 0;

    // just decomposition functions
    void selectPosition();
    void unselectPosition();
    void makeUniStep();
    void makeMultiStep();
    void makeMultiStep_TransformMove(std::vector<Move>&);
};

}  // namespace viewCurses

#endif
