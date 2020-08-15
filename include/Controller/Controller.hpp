//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_GAME_HPP
#define _PROJECT_GAME_HPP

#include "Model/ModelImpl/Board.hpp"
#include "Model/ModelImpl/Game.hpp"
#include "View/Base/Model/ViewModelBase.hpp"
#include "View/Curses/Menu/Menus/Game/ViewGameMenuCurses.hpp"

class Controller {
   public:  // TODO reference to Bot in Controller? What for?
    Controller(std::shared_ptr<Game> game);
    void init();  // Запуск игры // do we need it? then it must be template <typename Viewtype>
    template <typename ViewType>
    inline void selectCell(const Cell& selected);

    //    template <typename ViewType>
    //    inline void unSelectCell();

    void makeMove(const Move& move);  // really void?
    bool makeBotMove(PlayerColour);
    void cancelMove();
    void nextMove();
    void prevMove();

    GameStatus getGameStatus();

    template <typename ViewType>
    inline void updateViewModel();

    template <typename ViewType>  //TODO ViewType::ModelType - inherited internal class
    inline std::shared_ptr<ViewModelBase>& getViewModel();

    PlayerColour getCurrentPlayer() const;

    void updateAll();

   private:
    std::shared_ptr<Game> game_;
    //    PlayerColour turn_; // Чей ход
    // кто играет
    // история ходов
};

template <typename ViewType>
inline std::shared_ptr<ViewModelBase>& Controller::getViewModel() {
    static std::shared_ptr<ViewModelBase> model;
    return model;
}

template <>
inline std::shared_ptr<ViewModelBase>& Controller::getViewModel<viewCurses::ViewGameMenuCurses>() {
    static std::shared_ptr<ViewModelBase> model = std::dynamic_pointer_cast<ViewModelBase>(
        std::make_shared<viewCurses::ViewModelCurses>(*game_));
    return model;
}

template <typename ViewType>
inline void Controller::updateViewModel() {
}

template <>
inline void Controller::updateViewModel<viewCurses::ViewGameMenuCurses>() {
    getViewModel<viewCurses::ViewGameMenuCurses>() =
        std::make_shared<viewCurses::ViewModelCurses>(*game_);
}

template <typename ViewType>
inline void Controller::selectCell(const Cell&) {
}

template <>
inline void Controller::selectCell<viewCurses::ViewGameMenuCurses>(const Cell& selected) {
    auto steps = game_->allFigureMoves(selected.pos_);
    getViewModel<viewCurses::ViewGameMenuCurses>() =
        std::make_shared<viewCurses::ViewModelCurses>(*game_,
                                                      steps);
}

//template <typename ViewType>
//inline void Controller::unSelectCell()
//{
//
//}
//
//template <>
//inline void Controller::unSelectCell<viewCurses::ViewGameMenuCurses>()
//{
//    updateViewModel<viewCurses::ViewGameMenuCurses>();
//}

#endif  //_PROJECT_GAME_HPP
