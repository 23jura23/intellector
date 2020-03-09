#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

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
    void updateModel(std::shared_ptr<ViewModelCurses>); 
    void refreshView();

private:
//    struct ModelContainer {
//        ModelContainer(ViewModelCurses&);
//        ViewModelCurses& board;
//    };

//    std::unique_ptr<ModelContainer> container_;

    std::shared_ptr<ViewModelCurses> board_;
    std::shared_ptr<Controller> controller_;

    void outBoard();
    void outCell(const ViewModelCurses::ViewCellCurses&, pair);

    static constexpr size_t d = 7;
    static constexpr pair delta_down = { 0, 2 * (d - 3) };
    static constexpr pair delta_right_down = { (d + 3) + (d - 3), d - 3 };
    static constexpr pair delta_right_up = { 2 * (d + 3) + 2 * (d - 3), 0 };

    const int maxy, maxx;
    size_t tlx = d - 1, tly = 0; //top left x y

    pair getTL(pair); //get top left corner coordinates of cell

    Position currentPos;
    enum class CurrentPosStatus {
        UNSELECTED,
        SELECTED
    } currentPosStatus;
    Position selectedPos;
};

}

#endif
