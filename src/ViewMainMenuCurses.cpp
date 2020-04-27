#include "ViewMainMenuCurses.hpp"

#include <ncurses.h>

#include <fstream>
#include <iostream>  // TODO delete

namespace viewCurses {
using std::string;

MainMenuCurses::MainMenuCurses()
        : currentButtonIndex_{0} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);
    std::vector<std::pair<Picture, BUTTON_STYLE>> buttonsBuffer;
    for (auto [filename, style] : buttonsFilenames) {
        auto is = std::ifstream(filename, std::ios::in);
        is.exceptions(std::ifstream::badbit);
        Picture read = readPicture(is);
        buttonsBuffer.emplace_back(read, style);
        is.close();
    }

    maxButtonWidth = 0;
    for (const auto& [button, style] : buttonsBuffer)
        maxButtonWidth = std::max(maxButtonWidth, button.maxWidth());
    std::cerr << "maxButtonWidth: " << maxButtonWidth << std::endl;

    for (auto& [button, style] : buttonsBuffer) {
        alignWidth(button, maxButtonWidth);
        addButton(wrapInButton(button, style));
    }
}

void MainMenuCurses::show() {
    clear();
    int maxx = getmaxx(stdscr);
    std::pair<size_t, size_t> TL{maxx / 2 - maxButtonWidth / 2, topInitial};

    for (const auto& button : buttons) {
        showButton(button, TL);
        TL.second += button.maxHeight() + verticalInterval;
    }
}

void MainMenuCurses::showButton(const Picture& pic, std::pair<size_t, size_t> TL) {
    move(TL.second, TL.first);
    for (const auto& line : pic) {
        for (chtype c : line) {
            // TODO ignore chars
            addch(c);
        }
        TL.second++;
        move(TL.second, TL.first);
    }
}

Picture MainMenuCurses::wrapInButton_RECTANGLE(Picture pic) {
    const size_t upperMargin = 0;
    const size_t bottomMargin = 0;
    const size_t leftMargin = 0; // TODO align here
    const size_t rightMargin = 0; // TODO align here

    Picture newPic(pic, 1);
    std::cerr << pic.maxWidth() << std::endl;
    string upper(leftMargin + pic.maxWidth() + rightMargin, '_');
    newPic.pushBackLine(upper);

    for (size_t i = 0; i < upperMargin; ++i) newPic.pushBackLine("");

    for (size_t i = 0; i < pic.maxHeight(); ++i) newPic.pushBackLine(pic(i));

    for (size_t i = 0; i < bottomMargin; ++i) newPic.pushBackLine("");

    string bottom = upper;
    newPic.pushBackLine(bottom);

    newPic.updateState();

    for (size_t i = 0; i < newPic.maxHeight(); ++i) {
        string prefix = "|" + string(leftMargin, ' ');
        string suffix = string(rightMargin, ' ') + '|';
        newPic(i) = prefix + newPic(i) + suffix;
    }
    return newPic;
}

Picture MainMenuCurses::wrapInButton_ZIGZAG(Picture pic) {
    // WIP
    return pic;
}

Picture MainMenuCurses::wrapInButton(Picture pic, BUTTON_STYLE style) {
    switch (style) {
        case BUTTON_STYLE::RECTANGLE:
            return wrapInButton_RECTANGLE(pic);
            break;
        case BUTTON_STYLE::ZIGZAG:
            return wrapInButton_ZIGZAG(pic);
            break;
    }
    throw PictureException("Unknown button style");  // TODO MainMenuException?
}

void MainMenuCurses::alignWidth(Picture& pic, size_t width) {
    pic.updateState();
    for (auto& line : pic) {
        if (pic.maxWidth() < line.size())
            throw PictureException("Internal error: Picture.maxWidth() calculated incorrectly");
        line += string(pic.maxWidth() - line.size(), ' ');
    }
    for (auto& line : pic) {
        if (pic.maxWidth() < width) {
            string prefix = string((width - pic.maxWidth()) / 2, ' ');
            string suffix = string((width + 1 - pic.maxWidth()) / 2, ' ');
            line = prefix + line + suffix;
        }
    }
}

void MainMenuCurses::addButton(const Picture& pic) {
    buttons.push_back(pic);
}

}  // namespace viewCurses
