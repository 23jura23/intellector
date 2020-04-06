//
// Created by vsg on 22.02.2020.
//

#ifndef _PROJECT_GAME_HPP
#define _PROJECT_GAME_HPP

#include "Board.hpp"
#include "Game.hpp"
#include "ViewCurses.hpp"
#include "ViewModelBase.hpp"

class Controller {
   public:  // TODO reference to Bot in Controller? What for?
    Controller(std::shared_ptr<Game> game);
    void init();  // Запуск игры // do we need it? then it must be template <typename Viewtype>
    template <typename ViewType>
    inline void selectCell(const Cell& selected);

    //    template <typename ViewType>
    //    inline void unSelectCell();

    void makeMove(const SimpleMove& move);  // really void?
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
inline std::shared_ptr<ViewModelBase>& Controller::getViewModel<ViewCurses::viewCurses>() {
    static std::shared_ptr<ViewModelBase> model = std::dynamic_pointer_cast<ViewModelBase>(
        std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(),
                                                      game_->getColourCurrentPlayer()));
    return model;
}

template <typename ViewType>
inline void Controller::updateViewModel() {
}

template <>
inline void Controller::updateViewModel<ViewCurses::viewCurses>() {
    getViewModel<ViewCurses::viewCurses>() =
        std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(),
                                                      game_->getColourCurrentPlayer());
}

template <typename ViewType>
inline void Controller::selectCell(const Cell& selected) {
}

template <>
inline void Controller::selectCell<ViewCurses::viewCurses>(const Cell& selected) {
    auto steps = game_->allFigureMoves(selected.pos_);
    getViewModel<ViewCurses::viewCurses>() =
        std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(),
                                                      game_->getColourCurrentPlayer(),
                                                      steps);
}

//template <typename ViewType>
//inline void Controller::unSelectCell()
//{
//
//}
//
//template <>
//inline void Controller::unSelectCell<ViewCurses::viewCurses>()
//{
//    updateViewModel<ViewCurses::viewCurses>();
//}

#endif  //_PROJECT_GAME_HPP
