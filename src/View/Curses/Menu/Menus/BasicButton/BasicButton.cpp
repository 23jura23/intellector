#include "View/Curses/Menu/Menus/BasicButton/BasicButton.hpp"

#include <assert.h>
#include <ncurses.h>

#include <fstream>

#include "View/Curses/Menu/MenuTypes.hpp"
#include "View/Curses/Menu/Multiplexer/MenuMultiplexer.hpp"
#include "View/Curses/Model/ModelImpl/ColorScheme/ColorScheme.hpp"
#include "View/Curses/Model/ModelImpl/Init/Init.hpp"

namespace viewCurses {
using std::string;

MainMenuCurses::MainMenuCurses(buttonsVectorT buttonsFilenames_)
        : currentButtonIndex_{0} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);

    initCurses();

    // TODO common ncurses initializer, that initialize ncurses only 1 time
    // for now here is an assumption that ncurses is already initialized
    std::vector<std::pair<Picture, BUTTON_STYLE>> buttons_Buffer;
    for (auto [filename, style] : buttonsFilenames_) {
        auto is = std::ifstream(filename, std::ios::in);
        is.exceptions(std::ifstream::badbit);
        Picture read(is);
        buttons_Buffer.emplace_back(read, style);
        is.close();
    }

    maxButtonWidth_ = 0;
    maxButtonHeight_ = 0;
    for (const auto& [pic, style] : buttons_Buffer) {
        maxButtonWidth_ = std::max(maxButtonWidth_, pic.maxWidth());
        maxButtonHeight_ = std::max(maxButtonHeight_, pic.maxHeight());
    }
    std::cerr << "maxButtonWidth_: " << maxButtonWidth_ << std::endl;

    for (auto& [pic, style] : buttons_Buffer) {
        alignWidth(pic, maxButtonWidth_);
        std::shared_ptr<Button> buttonPtr = ButtonFactory(pic, style);
        assert(buttonPtr != nullptr);
        addButton(buttonPtr);
    }
}

MainMenuCurses::~MainMenuCurses() {
    terminateCurses();
}

MENU_TYPE MainMenuCurses::type() const {
    return MENU_TYPE::MAIN_MENU;
}

void MainMenuCurses::draw() {
    clear();
    std::pair<size_t, size_t> TL{getTL()};

    buttonsStateUpdate();

    for (const auto& buttonPtr : buttons_) {
        buttonPtr->draw(TL);
        TL.second += buttonPtr->getPicture().maxHeight() + verticalInterval_;
    }
}

std::pair<size_t, size_t> MainMenuCurses::getTL() const {
    int maxx = getmaxx(stdscr);
    return {maxx / 2 - maxButtonWidth_ / 2, topInitial_};
}

void MainMenuCurses::buttonsStateUpdate() {
    for (const auto& i : buttons_) i->setMode(BUTTON_MODE::DEFAULT);
    buttons_[currentButtonIndex_]->setMode(BUTTON_MODE::SELECTED);
}

// TODO put into Button class
void MainMenuCurses::alignWidth(Picture& pic, size_t width) {
    char anyBackgroundChar = pic.getBackgroundChars().at(0);
    size_t prevMaxWidth = pic.maxWidth();
    for (auto& line : pic) {
        assert(line.size() <= pic.maxWidth());
        line += string(pic.maxWidth() - line.size(), anyBackgroundChar);
    }
    for (auto& line : pic) {
        if (prevMaxWidth < width) {
            string prefix = string((width - prevMaxWidth) / 2, anyBackgroundChar);
            string suffix = string((width + 1 - prevMaxWidth) / 2, anyBackgroundChar);
            line = prefix + line + suffix;
        }
    }
}

void MainMenuCurses::addButton(std::shared_ptr<Button> pic) {
    assert(pic != nullptr);
    buttons_.push_back(pic);
}

}  // namespace viewCurses
