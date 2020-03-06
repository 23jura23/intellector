//
// Created by vsg on 28.02.2020.
//

#ifndef _MY_FOLDER_FIGURE_HPP
#define _MY_FOLDER_FIGURE_HPP

#include <optional>

enum class FigureType {
    INTELLECTOR,
    DOMINATOR,
    AGGRESSOR,
    DEFENSSOR,
    LIBERATOR,
    PROGRESSOR
};

enum class PlayerColour {
    black_, white_
};

class Figure {
public:
    Figure(PlayerColour colour, FigureType type)
            : colour_(colour), type_(type) {}

    const PlayerColour colour_;
    const FigureType type_;
};

#endif //MY_FOLDER_FIGURE_HPP
