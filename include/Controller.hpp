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
public: // TODO reference to Bot in Controller? What for?
    Controller(std::shared_ptr<Game> game);
    void init(); // Запуск игры // do we need it? then it must be template <typename Viewtype>
    template <typename ViewType>
    inline void selectCell(const Cell& selected);

//    template <typename ViewType>
//    inline void unSelectCell();

    void makeMove(const SimpleMove& move); // really void?

    template <typename ViewType>
    inline void updateViewModel();

    template <typename ViewType> //TODO ViewType::ModelType - inherited internal class
    inline std::shared_ptr<ViewModelBase>& getViewModel();

    void updateAll();

private:
    std::shared_ptr<Game> game_;
    //    PlayerColour turn_; // Чей ход
    // кто играет
    // история ходов
};

template <typename ViewType>
inline std::shared_ptr<ViewModelBase>& Controller::getViewModel()
{
    static std::shared_ptr<ViewModelBase> model;
    return model;
}

template <>
inline std::shared_ptr<ViewModelBase>& Controller::getViewModel<ViewCurses::viewCurses>()
{
    static std::shared_ptr<ViewModelBase> model = std::dynamic_pointer_cast<ViewModelBase>(std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(), game_->getColourCurrentPlayer()));
    return model;
}

template <typename ViewType>
inline void Controller::updateViewModel()
{
}

template <>
inline void Controller::updateViewModel<ViewCurses::viewCurses>()
{
    getViewModel<ViewCurses::viewCurses>() = std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(), game_->getColourCurrentPlayer());
}
    
template <typename ViewType>
inline void Controller::selectCell(const Cell& selected)
{
}

#include <iostream>
using namespace std;

template <>
inline void Controller::selectCell<ViewCurses::viewCurses>(const Cell& selected)
{
    auto steps = game_->allFigureMoves(selected.pos_, game_->getColourCurrentPlayer()); // TODO something strange: why game_ is getting its own field through its own getter?
    freopen("error.txt","a",stderr);
    cerr << "steps.size(): " << steps.size() << endl;
    getViewModel<ViewCurses::viewCurses>() = std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(), game_->getColourCurrentPlayer(), steps);
//    auto& bb = std::dynamic_pointer_cast<ViewCurses::ViewModelCurses>(getViewModel<ViewCurses::viewCurses>())->viewBoard;
//    std::dynamic_pointer_cast<ViewCurses::ViewModelCurses>(getViewModel<ViewCurses::viewCurses>())->viewBoard[3][1].status = ViewCurses::ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::ACTIVE;
//    bb[4][2].status = ViewCurses::ViewModelCurses::ViewCellCurses::ViewCellCursesStatus::ACTIVE;
//    auto bb3 = std::dynamic_pointer_cast<ViewCurses::ViewModelCurses>(getViewModel<ViewCurses::viewCurses>())->viewBoard;
//    auto bb2 = std::make_shared<ViewCurses::ViewModelCurses>(game_->getBoard(), game_->getColourCurrentPlayer(), steps)->viewBoard;
//    cerr << "size table" << endl;
//    for (size_t i = 0;i < bb.size(); ++i)
//    {
//        for (size_t j = 0;j < bb[i].size(); ++j)
//            cerr << bb[i][j].inMoves.size() << ' ';
//        cerr << endl;
//    }
//    cerr << "size table 2" << endl;
//    for (size_t i = 0;i < bb2.size(); ++i)
//    {
//        for (size_t j = 0;j < bb2[i].size(); ++j)
//            cerr << bb2[i][j].inMoves.size() << ' ';
//        cerr << endl;
//    }
//    cerr << "size table 3" << endl;
//    for (size_t i = 0;i < bb3.size(); ++i)
//    {
//        for (size_t j = 0;j < bb3[i].size(); ++j)
//            cerr << bb3[i][j].inMoves.size() << ' ';
//        cerr << endl;
//    }
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


#endif //_PROJECT_GAME_HPP
