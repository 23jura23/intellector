#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include <memory.h>
#include <ncurses.h>

#include <string>
#include <vector>

#include "ViewBase.hpp"
#include "ViewModelCurses.hpp"

class Controller;

namespace ViewCurses {

class viewCurses : public viewBase {
    using pair = std::pair<size_t, size_t>;

   public:
    viewCurses(std::shared_ptr<Controller>);
    ~viewCurses();

    void run();
    void fetchModel();
    void reloadModel();
    void updatePositions(Position&);
    void updateModel(std::shared_ptr<ViewModelCurses>);
    void refreshView();

   private:
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

    // just decomposition functions
    void selectPosition();
    void unselectPosition();
    void makeUniStep();
    void makeMultiStep();
    void makeMultiStep_TransformMove(std::vector<std::shared_ptr<SimpleMove>>&);
};

}  // namespace ViewCurses

#endif
