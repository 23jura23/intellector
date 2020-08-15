#ifndef _VIEW_CURSES_HPP_
#define _VIEW_CURSES_HPP_

#include <memory.h>
#include <ncurses.h>

#include <string>
#include <utility>
#include <vector>

#include "View/Base/Base.hpp"
#include "View/Curses/Menu/Menu.hpp"
#include "View/Curses/Model/Model.hpp"
#include "View/Curses/Model/ModelImpl/Picture/Picture.hpp"

class Controller;

namespace viewCurses {

enum DrawCellType {
    EMPTY,
    INTELLECTOR,
    DOMINATOR,
    AGGRESSOR,
    DEFENSSOR,
    LIBERATOR,
    PROGRESSOR
};

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

    std::vector<std::pair<DrawCellType, std::string>> cellPicturesFilenames_;
    std::unordered_map<DrawCellType, Picture> cellPictures_;
    
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
