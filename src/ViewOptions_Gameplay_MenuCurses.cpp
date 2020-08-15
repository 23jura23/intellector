#include "ViewOptions_Gameplay_MenuCurses.hpp"

#include <assert.h>

#include <fstream>

#include "ViewInitCurses.hpp"
#include "ViewMenuMultiplexerCurses.hpp"
#include "ViewMenuTypes.hpp"

namespace viewCurses {

Options_Gameplay_MenuCurses::Options_Gameplay_MenuCurses(const GameSettings& settings)
        : buttonsFilenames_{ 
                            { // anti-autoformat :)
                                {"resources/gameplay_white_bot.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_-.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_0.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_1.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_2.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_3.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_4.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_5.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_6.btn", BUTTON_STYLE::RECTANGLE}
                            },
                            {
                                {"resources/gameplay_black_bot.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_-.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_0.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_1.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_2.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_3.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_4.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_5.btn", BUTTON_STYLE::RECTANGLE},
                                {"resources/gameplay_6.btn", BUTTON_STYLE::RECTANGLE},

                            },
                            { //
                                {"resources/back.btn", BUTTON_STYLE::RECTANGLE}
                            } //
        }
        , currentButtonIndexY_{0}
        , currentButtonIndexX_{0}
        , settings_{settings} {
    auto rv = freopen("error.txt", "a", stderr);
    static_cast<void>(rv);

    initCurses();

    // TODO common ncurses initializer, that initialize ncurses only 1 time
    // for now here is an assumption that ncurses is already initialized
    std::vector<std::vector<std::pair<Picture, BUTTON_STYLE>>> buttons_Buffer;
    for (const auto& vec : buttonsFilenames_) {
        buttons_Buffer.push_back({});
        for (auto [filename, style] : vec) {
            auto is = std::ifstream(filename, std::ios::in);
            is.exceptions(std::ifstream::badbit);
            Picture pic(is);
            buttons_Buffer.rbegin()->push_back({pic, style});
            is.close();
        }
    }

    size_t maxWidth = 0;
    for (const auto& vec : buttons_Buffer)
        if (vec.size())
            maxWidth = std::max(maxWidth, vec[0].first.maxWidth());

    for (auto& vec : buttons_Buffer)
        if (vec.size())
            alignWidth(vec[0].first, maxWidth);

    for (const auto& vec : buttons_Buffer) {
        buttons_.push_back({});
        for (const auto& [pic, style] : vec) {
            std::shared_ptr<Button> buttonPtr = ButtonFactory(pic, style, 1, 1, 1, 1);
            assert(buttonPtr != nullptr);
            buttons_.rbegin()->push_back(buttonPtr);
        }
    }
}

Options_Gameplay_MenuCurses::~Options_Gameplay_MenuCurses() {
    terminateCurses();
}

RET_CODE Options_Gameplay_MenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    if (buttons_.size() == 0)
        return rc;
    size_t maxY = buttons_.size();
    size_t maxX = buttons_.at(currentButtonIndexY_).size();
    switch (c) {
        case 'w':
        case KEY_UP: {
            currentButtonIndexY_ = (currentButtonIndexY_ - 1 + maxY) % maxY;
            draw();
            break;
        }
        case 's':
        case KEY_DOWN: {
            currentButtonIndexY_ = (currentButtonIndexY_ + 1) % maxY;
            draw();
            break;
        }
        case 'a':
        case KEY_LEFT: {
            currentButtonIndexX_ = (currentButtonIndexX_ - 1 + maxX) % maxX;
            draw();
            break;
        }
        case 'd':
        case KEY_RIGHT: {
            currentButtonIndexX_ = (currentButtonIndexX_ + 1) % maxX;
            draw();
            break;
        }
        case 27:  // ESC
            rc = RET_CODE::BACK;
            break;
        case 32:
            // assuming correct buttons order:
            // white bot (?)
            // black bot (?)
            // inside (?):
            // -
            // 0
            // 1
            // 2
            // 3
            // 4
            // 5
            // 6

            // back
            switch (currentButtonIndexY_) {
                case 0:  // white bot
                case 1:  // black bot
                    switch (currentButtonIndexX_) {
                        case 0:
                            break;
                        case 1:
                            if (currentButtonIndexY_ == 0) {  // white bot
                                settings_.set_first_player(0);
                            } else {  // black bot
                                settings_.set_second_player(0);
                            }
                            break;
                        default: {
                            int difficulty = currentButtonIndexX_ - 2;
                            // bot - 0 1 2 etc, offsetBots = 2
                            if (currentButtonIndexY_ == 0) {  // white bot
                                settings_.set_first_player(1);
                                settings_.set_difficulty_white(difficulty);
                            } else {  // black bot
                                settings_.set_second_player(1);
                                settings_.set_difficulty_black(difficulty);
                            }
                            break;
                        }
                    }
                    break;
                case 2:  // back
                    rc = RET_CODE::BACK;
                    break;
                default:
                    assert(0);
            }
            break;
        default:
            // do nothing
            break;
    }
    draw();
    return rc;
}

void Options_Gameplay_MenuCurses::draw() {
    clear();
    std::pair<size_t, size_t> TL{getTL()};
    std::pair<size_t, size_t> initTL{TL};

    buttonsStateUpdate();

    for (size_t i = 0; i < buttons_.size(); ++i) {
        size_t maxHeight = 0;
        for (size_t j = 0; j < buttons_[i].size(); ++j) {
            const auto& buttonPtr = buttons_[i][j];

            buttonPtr->draw(TL);

            TL.first += buttonPtr->getPicture().maxWidth() + horizontalInterval_;
            maxHeight =
                std::max(maxHeight, buttonPtr->getPicture().maxHeight() + verticalInterval_);
        }
        TL.second += maxHeight + verticalInterval_;
        TL.first = initTL.first;
    }
}

std::pair<size_t, size_t> Options_Gameplay_MenuCurses::getTL() const {
    int maxx = getmaxx(stdscr);
    return {maxx / 7, topInitial_};
}

void Options_Gameplay_MenuCurses::buttonsStateUpdate() {
    for (auto& vec : buttons_) {
        for (auto& i : vec) {
            i->setMode(BUTTON_MODE::DEFAULT);
        }
    }

    if (buttons_.at(currentButtonIndexY_).size() > 0) {
        size_t currentButtonIndexX_Correct =
            std::min(buttons_.at(currentButtonIndexY_).size() - 1, currentButtonIndexX_);
        buttons_.at(currentButtonIndexY_)
            .at(currentButtonIndexX_Correct)
            ->setMode(BUTTON_MODE::SELECTED);
    }


    if (settings_.first_player()) {
        buttons_.at(0).at(offsetBots+settings_.difficulty_white())->setMode(BUTTON_MODE::SET);
    }
    else {
        buttons_.at(0).at(1)->setMode(BUTTON_MODE::SET);
    }

    if (settings_.second_player()) {
        buttons_.at(1).at(offsetBots+settings_.difficulty_black())->setMode(BUTTON_MODE::SET);
    }
    else {
        buttons_.at(1).at(1)->setMode(BUTTON_MODE::SET);
    }
}

void Options_Gameplay_MenuCurses::alignWidth(Picture& pic, size_t width) {
    char anyBackgroundChar = pic.getBackgroundChars().at(0);
    size_t prevMaxWidth = pic.maxWidth();
    for (auto& line : pic) {
        assert(line.size() <= pic.maxWidth());
        line += std::string(pic.maxWidth() - line.size(), anyBackgroundChar);
    }
    for (auto& line : pic) {
        if (prevMaxWidth < width) {
            std::string prefix = std::string((width - prevMaxWidth) / 2, anyBackgroundChar);
            std::string suffix = std::string((width + 1 - prevMaxWidth) / 2, anyBackgroundChar);
            line = prefix + line + suffix;
        }
    }
}

GameSettings Options_Gameplay_MenuCurses::getRV() const {
    return settings_;
}

MENU_TYPE Options_Gameplay_MenuCurses::type() const {
    return MENU_TYPE::OPTIONS_GAMEPLAY_MENU;
}
};  // namespace viewCurses
