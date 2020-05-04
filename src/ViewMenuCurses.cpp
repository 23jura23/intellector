#include "ViewMenuCurses.hpp"

#include <iostream>
#include <utility>
using std::cerr, std::endl;

namespace viewCurses {

// Menu, not the picture, reads the stream, because the could possibly be another format
Picture MenuCurses::readPicture(std::istream& is) {
    auto os = freopen("error.txt", "a", stderr);
    static_cast<void>(os);

    std::string newLine;

    std::string ignoredChars;
    std::string backgroundChars;
    char haveConf{};
    haveConf = is.peek();
    if (haveConf == '#') {
        getline(is, ignoredChars);
        if (ignoredChars.length())
            ignoredChars = ignoredChars.substr(1, ignoredChars.length() - 1);

        haveConf = is.peek();
        if (haveConf == '#') {
            getline(is, backgroundChars);
            if (backgroundChars.length())
                backgroundChars = backgroundChars.substr(1, backgroundChars.length() - 1);
        }
    }
    if (ignoredChars.empty())
        ignoredChars = "\x1E";
    if (backgroundChars.empty())
        backgroundChars = "\x1F";

    cerr << "ig and bk: " << ignoredChars << " | " << backgroundChars << endl;

    Picture newPicture(ignoredChars, backgroundChars);

    while (true) {
        getline(is, newLine);
        if (is.fail())
            break;
        newPicture.pushBackLine(newLine);
    }
    return newPicture;
}

}  // namespace viewCurses
