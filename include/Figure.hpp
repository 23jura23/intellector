//
// Created by vsg on 28.02.2020.
//

#ifndef _MY_FOLDER_FIGURE_HPP
#define _MY_FOLDER_FIGURE_HPP

#include <optional>

enum class FigureType { INTELLECTOR, DOMINATOR, AGGRESSOR, DEFENSSOR, LIBERATOR, PROGRESSOR };

enum class PlayerColour { black_, white_, none_ };

class Figure {
   public:
    Figure(PlayerColour colour, FigureType type)
            : colour_(colour)
            , type_(type) {
    }
    Figure(const Figure&) = default;
    Figure& operator=(const Figure&) = default;

    bool inline operator==(const Figure& other) const {
        return colour_ == other.colour_ && type_ == other.type_;
    }

    bool inline operator!=(const Figure& other) const {
        return colour_ != other.colour_ || type_ != other.type_;
    }

    PlayerColour colour_;
    FigureType type_;
};

bool inline operator==(const std::optional<Figure>& a, const std::optional<Figure>& b) {
    if (a.has_value() != b.has_value())
        return false;
    if (a.has_value() == b.has_value() && !a.has_value())
        return true;

    return a->colour_ == b->colour_ && a->type_ == b->type_;
}

bool inline operator!=(const std::optional<Figure>& a, const std::optional<Figure>& b) {
    return !(a == b);
}

PlayerColour inline other_colour(PlayerColour colour) {
    if (colour == PlayerColour::black_)
        return PlayerColour::white_;
    else
        return PlayerColour::black_;
}

#endif  //MY_FOLDER_FIGURE_HPP
