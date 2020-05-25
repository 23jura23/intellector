#include "ViewMainMenuCurses.hpp"

#include <assert.h>
#include <ncurses.h>

#include <fstream>

#include "ViewColorSchemeCurses.hpp"
#include "ViewInitCurses.hpp"
#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {
using std::string;

MainMenuCurses::MainMenuCurses(buttonsVectorT buttonsFilenames_)
        : currentButtonIndex_{0} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);

    initCurses();

    // TODO common ncurses initializer, that initialize ncurses only 1 time
    // for now here is an assumption that ncurses is already initialized
    //    auto buttonsFilenames_ = getButtonFilenames();
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

//void MainMenuCurses::drawButton(std::pair<size_t, size_t> TL, const Picture& pic) {
//    cerr << "initColorsDone: " << initColorsDone << endl;
//    cerr << "ignoredChars: " << pic.getIgnoredChars() << endl;
//    cerr << "backgroundChars: " << pic.getBackgroundChars() << endl;
//    move(TL.second, TL.first);
//    for (const auto& line : pic) {
//        cerr << "line: " << line << endl;
//        for (chtype c : line) {
//            if (pic.isIgnoredChar(c)) {
//            } else if (pic.isBackgroundChar(c)) {
//                attron(COLOR_PAIR(BUTTON_EMPTY));
//                addch(' ');
//                attroff(COLOR_PAIR(BUTTON_EMPTY));
//            } else {
//                attron(COLOR_PAIR(BUTTON_TEXT));
//                addch(c);
//                attroff(COLOR_PAIR(BUTTON_TEXT));
//            }
//        }
//        TL.second++;
//        move(TL.second, TL.first);
//    }
//}

// TODO put into Button class
void MainMenuCurses::alignWidth(Picture& pic, size_t width) {
    //    pic.updateState();
    char anyBackgroundChar = pic.getBackgroundChars().at(0);
    size_t prevMaxWidth = pic.maxWidth();
    for (auto& line : pic) {
        assert(line.size() <= pic.maxWidth());
        //            throw PictureException("Internal error: Picture.maxWidth() calculated incorrectly");
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
