#include "ViewMenuCurses.hpp"

#include <utility>

namespace viewCurses {

Picture MenuCurses::readPicture(std::istream& is) {
    char haveConf{};
    is >> haveConf;
    if (haveConf != '#')
        throw PictureException("Bad picture");

    std::string ignoredChars;
    getline(is, ignoredChars);
    Picture newPicture(ignoredChars);
    
    std::string newLine;
    while (true)
    {
        getline(is, newLine);
        if (is.fail()) break;
        newPicture.pushBackLine(newLine);
    }
    return newPicture;
}

}  // namespace viewCurses
