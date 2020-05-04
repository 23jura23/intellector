#include "ViewButtonCurses.hpp"

#include <assert.h>
#include <ncurses.h>

#include "ViewColorSchemeCurses.hpp"

//#include <iostream>
//using std::cerr, std::endl;

using std::string;
namespace viewCurses {

buttonColorScheme DEFAULT_SCHEME{BUTTON_DEFAULT_TEXT, BUTTON_DEFAULT_EMPTY, BUTTON_DEFAULT_BORDER};
buttonColorScheme SELECTED_SCHEME{BUTTON_SELECTED_TEXT,
                                  BUTTON_SELECTED_EMPTY,
                                  BUTTON_SELECTED_BORDER};

Button::Button(const Picture& pic)
        : buttonPicture{pic}
        , colorScheme{DEFAULT_SCHEME} {
}

const Picture& Button::getPicture() const {
    return buttonPicture;
}

void Button::setMode(BUTTON_MODE mode) {
    switch (mode) {
        case BUTTON_MODE::DEFAULT:
            colorScheme = DEFAULT_SCHEME;
            return;
        case BUTTON_MODE::SELECTED:
            colorScheme = SELECTED_SCHEME;
            return;
    }
    throw ButtonException("Incorrect button mode " + std::to_string(static_cast<int>(mode)));
}

ButtonRectangle::ButtonRectangle(const Picture& pic)
        : Button{pic} {
    char backgroundChar = pic.getBackgroundChars().at(0);
    buttonPicture.clearPictureContent();
    size_t upperLength = 1 + leftMargin + pic.maxWidth() + rightMargin + 1;
    string upper(upperLength, '_');
    buttonPicture.pushBackLine(upper);

    size_t upperBottomMarginLength = pic.maxWidth();
    for (size_t i = 0; i < upperMargin; ++i)
        buttonPicture.pushBackLine(std::string(upperBottomMarginLength, backgroundChar));

    for (size_t i = 0; i < pic.maxHeight(); ++i) buttonPicture.pushBackLine(pic(i));

    for (size_t i = 0; i < bottomMargin; ++i)
        buttonPicture.pushBackLine(std::string(upperBottomMarginLength, backgroundChar));

    size_t bottomLength = leftMargin + pic.maxWidth() + rightMargin;
    string bottom(bottomLength, '_');
    bottom = '|' + bottom + '|';
    buttonPicture.pushBackLine(bottom);

    for (size_t i = 1; i + 1 < buttonPicture.maxHeight(); ++i) {
        string prefix = "|" + string(leftMargin, backgroundChar);
        string suffix = string(rightMargin, backgroundChar) + '|';
        buttonPicture(i) = prefix + buttonPicture(i) + suffix;
    }
}

void ButtonRectangle::draw(std::pair<size_t, size_t> TL) const {
    assert(stdscr != 0);
    assert(initColorsDone);
    move(TL.second, TL.first);

    char c;

    if (buttonPicture.maxHeight()) {
        for (size_t j = 0; j < buttonPicture(0).size(); ++j) {
            c = buttonPicture(0, j);
            attron(COLOR_PAIR(colorScheme.border));
            addch(c);
            attroff(COLOR_PAIR(colorScheme.border));
        }
        TL.second++;
        move(TL.second, TL.first);

        for (size_t i = 1; i + 1 < buttonPicture.maxHeight(); ++i) {
            if (buttonPicture(i).size()) {
                c = buttonPicture(i, 0);
                attron(COLOR_PAIR(colorScheme.border));
                addch(c);
                attroff(COLOR_PAIR(colorScheme.border));
                for (size_t j = 1; j + 1 < buttonPicture(i).size(); ++j) {
                    c = buttonPicture(i, j);
                    if (buttonPicture.isIgnoredChar(c)) {
                        int cx = -1, cy = -1;
                        getyx(stdscr, cy, cx);
                        move(cy, cx + 1);
                    } else if (buttonPicture.isBackgroundChar(c)) {
                        attron(COLOR_PAIR(colorScheme.empty));
                        addch(' ');  // TODO is it always a space?
                        attroff(COLOR_PAIR(colorScheme.empty));
                    } else {
                        attron(COLOR_PAIR(colorScheme.text));
                        addch(c);
                        attroff(COLOR_PAIR(colorScheme.text));
                    }
                }
                c = buttonPicture(i, buttonPicture(i).size() - 1);
                attron(COLOR_PAIR(colorScheme.border));
                addch(c);
                attroff(COLOR_PAIR(colorScheme.border));
            }
            TL.second++;
            move(TL.second, TL.first);
        }

        size_t lastIndex = buttonPicture.maxHeight() - 1;
        for (size_t j = 0; j < buttonPicture(lastIndex).size(); ++j) {
            c = buttonPicture(lastIndex, j);
            attron(COLOR_PAIR(colorScheme.border));
            addch(c);
            attroff(COLOR_PAIR(colorScheme.border));
        }
    }
}

void ButtonZigZag::draw(std::pair<size_t, size_t>) const {
}

ButtonZigZag::ButtonZigZag(const Picture& pic)
        : Button{pic} {
}

std::shared_ptr<Button> ButtonFactory(const Picture& pic, BUTTON_STYLE style) {
    switch (style) {
        case BUTTON_STYLE::RECTANGLE:
            return std::make_unique<ButtonRectangle>(pic);
            break;
        case BUTTON_STYLE::ZIGZAG:
            return std::make_unique<ButtonZigZag>(pic);
            break;
    }
    throw ButtonException("ButtonFactory: unknown button style");
}

}  // namespace viewCurses
