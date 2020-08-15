cmake_minimum_required(VERSION 3.10)
project(intellector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra -Wshadow")

project(Intellector)

set(TARGET intellector)
set(TEST test_${TARGET})

include_directories(include)

set(BASE_SOURCES
        include/Bot/AlphaBetaBot/AlphaBetaBot.hpp
        include/Bot/Test/AlphaBetaBotTest.hpp
        include/Model/Archiver/Archiver.hpp
        include/Model/ModelImpl/Board.hpp
        include/Bot/Bot.hpp
        include/Bot/BotFactory/BotFactory.hpp
        include/Model/ModelImpl/Cell.hpp
        include/Controller/Controller.hpp
        include/doctest.h
        include/Bot/AlphaBetaBot/Evaluate/EvalGame.hpp
        include/Bot/AlphaBetaBot/Evaluate/Evaluate.hpp
        include/Model/ModelImpl/Figure.hpp
        include/Bot/AlphaBetaBot/FigureKeeper/FigureKeeper.hpp
        include/Bot/Test/FigureKeeperTest.hpp
        include/Model/ModelImpl/FigureMoveValidator.hpp
        include/Bot/AlphaBetaBot/Evaluate/FunctionSet/FunctionSet.hpp
        include/Model/ModelImpl/Game.hpp
        include/Model/ModelImpl/GameSettings.hpp
        include/Bot/GreedyBot/GreedyBot.hpp
        include/Model/ModelImpl/MoveTypes.hpp
        include/Bot/AlphaBetaBot/OptimizedAlphaBetaBot.hpp
        include/Model/ModelImpl/Position.hpp
        include/Bot/RandomBot/RandomBot.hpp
        include/Bot/Test/TestBotFactory.hpp
        include/View/Base/ViewBase.hpp
        include/View/Curses/Model/Button/ViewButtonCurses.hpp
        include/View/Curses/Model/ModelImpl/ColorScheme/ViewColorSchemeCurses.hpp
        include/View/Curses/Menu/Menus/Game/ViewGameMenuCurses.hpp
        include/View/Curses/Menu/Menus/History/ViewHistoryMenuCurses.hpp
        include/View/Curses/Model/ModelImpl/Init/ViewInitCurses.hpp
        include/View/Curses/Menu/Menus/BasicButton/ViewMainMenuCurses.hpp
        include/View/Curses/Menu/ViewMenuCurses.hpp
        include/View/Curses/Menu/Multiplexer/ViewMenuMultiplexerCurses.hpp
        include/View/Curses/Menu/ViewMenuTypes.hpp
        include/View/Base/Model/ViewModelBase.hpp
        include/View/Curses/Model/ViewModelCurses.hpp
        include/View/Curses/Menu/Menus/Options/Gameplay/ViewOptions_Gameplay_MenuCurses.hpp
        include/View/Curses/Menu/Menus/Options/ViewOptionsMenuCurses.hpp
        include/View/Curses/Model/ModelImpl/Picture/ViewPictureCurses.hpp
        include/View/Curses/Menu/Menus/Preview/ViewPreviewMenuCurses.hpp
        include/View/Curses/Menu/Menus/Rules/ViewRulesMenuCurses.hpp
        include/View/Curses/Menu/Menus/Start/ViewStartMenuCurses.hpp
        include/View/Curses/Menu/Menus/GameOver/ViewWinMenuCurses.hpp
        src/Bot/AlphaBetaBot/AlphaBetaBot.cpp
        src/Model/Archiver/Archiver.cpp
        src/Model/ModelImpl/Board.cpp
        src/Bot/BotFactory/BotFactory.cpp
        src/Model/ModelImpl/Cell.cpp
        src/Controller/Controller.cpp
        src/Bot/AlphaBetaBot/Evaluate/Evaluate.cpp
        src/Bot/AlphaBetaBot/FigureKeeper/FigureKeeper.cpp
        src/Model/ModelImpl/FigureMoveValidator.cpp
        src/Bot/AlphaBetaBot/Evaluate/FunctionSet/FunctionSet.cpp
        src/Model/ModelImpl/Game.cpp
        src/Bot/GreedyBot/GreedyBot.cpp
        src/Model/ModelImpl/MoveTypes.cpp
        src/Bot/AlphaBetaBot/OptimizedAlphaBetaBot.cpp
        src/Bot/RandomBot/RandomBot.cpp
        src/View/Base/ViewBase.cpp
        src/View/Curses/Model/Button/ViewButtonCurses.cpp
        src/View/Curses/Model/ModelImpl/ColorScheme/ViewColorSchemeCurses.cpp
        src/View/Curses/Menu/Menus/Game/ViewGameMenuCurses.cpp
        src/View/Curses/Menu/Menus/History/ViewHistoryMenuCurses.cpp
        src/View/Curses/Model/ModelImpl/Init/ViewInitCurses.cpp
        src/View/Curses/Menu/Menus/BasicButton/ViewMainMenuCurses.cpp
        src/View/Curses/Menu/ViewMenuCurses.cpp
        src/View/Curses/Menu/Multiplexer/ViewMenuMultiplexerCurses.cpp
        src/View/Curses/Model/ViewModelCurses.cpp
        src/View/Curses/Menu/Menus/Options/Gameplay/ViewOptions_Gameplay_MenuCurses.cpp
        src/View/Curses/Menu/Menus/Options/ViewOptionsMenuCurses.cpp
        src/View/Curses/Model/ModelImpl/Picture/ViewPictureCurses.cpp
        src/View/Curses/Menu/Menus/Rules/ViewRulesMenuCurses.cpp
        src/View/Curses/Menu/Menus/Start/ViewStartMenuCurses.cpp
        src/View/Curses/Menu/Menus/GameOver/ViewWinMenuCurses.cpp)

set(TEST_SOURCES
        test/TestMain.cpp
        test/TestBotFactory.cpp)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

add_executable(${TARGET} ${BASE_SOURCES} src/main.cpp)
add_executable(${TEST} ${BASE_SOURCES} ${TEST_SOURCES})

target_include_directories(${TARGET} PRIVATE
        ${CURSES_INCLUDE_DIR})
target_include_directories(${TEST} PRIVATE
        ${CURSES_INCLUDE_DIR})

target_link_libraries(${TARGET}
        ${CURSES_LIBRARIES}
        Threads::Threads)
target_link_libraries(${TEST}
        ${CURSES_LIBRARIES}
        Threads::Threads)
