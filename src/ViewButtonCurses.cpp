#include "ViewButtonCurses.hpp"

#include <assert.h>
#include <ncurses.h>

#include "ViewColorSchemeCurses.hpp"

//#include <iostream>
//using std::cerr, std::endl;

using std::string;
namespace viewCurses {

Button::Button(const Picture& pic)
        : buttonPicture{pic} {
}

const Picture& Button::getPicture() const {
    return buttonPicture;
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

    //    buttonPicture.updateState();

    for (size_t i = 1; i + 1 < buttonPicture.maxHeight(); ++i) {
        string prefix = "|" + string(leftMargin, backgroundChar);
        string suffix = string(rightMargin, backgroundChar) + '|';
        buttonPicture(i) = prefix + buttonPicture(i) + suffix;
    }
    //    buttonPicture.updateState();
}

void ButtonRectangle::draw(std::pair<size_t, size_t> TL) const {
    //    cerr << "initColorsDone: " << initColorsDone << endl;
    //    cerr << "ignoredChars: " << pic.getIgnoredChars() << endl;
    //    cerr << "backgroundChars: " << pic.getBackgroundChars() << endl;
    assert(stdscr != 0);
    assert(initColorsDone);
    move(TL.second, TL.first);

    char c;

    if (buttonPicture.maxHeight()) {
        for (size_t j = 0; j < buttonPicture(0).size(); ++j) {
            c = buttonPicture(0, j);
            attron(COLOR_PAIR(BUTTON_BORDER));
            addch(c);
            attroff(COLOR_PAIR(BUTTON_BORDER));
        }
        TL.second++;
        move(TL.second, TL.first);

        for (size_t i = 1; i + 1 < buttonPicture.maxHeight(); ++i) {
            if (buttonPicture(i).size()) {
                c = buttonPicture(i, 0);
                attron(COLOR_PAIR(BUTTON_BORDER));
                addch(c);
                attroff(COLOR_PAIR(BUTTON_BORDER));
                for (size_t j = 1; j + 1 < buttonPicture(i).size(); ++j) {
                    c = buttonPicture(i, j);
                    if (buttonPicture.isIgnoredChar(c)) {
                        int cx = -1, cy = -1;
                        getyx(stdscr, cy, cx);
                        move(cy, cx + 1);
                    } else if (buttonPicture.isBackgroundChar(c)) {
                        attron(COLOR_PAIR(BUTTON_EMPTY));
                        addch(' ');
                        attroff(COLOR_PAIR(BUTTON_EMPTY));
                    } else {
                        attron(COLOR_PAIR(BUTTON_TEXT));
                        addch(c);
                        attroff(COLOR_PAIR(BUTTON_TEXT));
                    }
                }
                c = buttonPicture(i, buttonPicture(i).size() - 1);
                attron(COLOR_PAIR(BUTTON_BORDER));
                addch(c);
                attroff(COLOR_PAIR(BUTTON_BORDER));
            }
            TL.second++;
            move(TL.second, TL.first);
        }

        size_t lastIndex = buttonPicture.maxHeight() - 1;
        for (size_t j = 0; j < buttonPicture(lastIndex).size(); ++j) {
            c = buttonPicture(lastIndex, j);
            attron(COLOR_PAIR(BUTTON_BORDER));
            addch(c);
            attroff(COLOR_PAIR(BUTTON_BORDER));
        }
    }
}

void ButtonZigZag::draw(std::pair<size_t, size_t>) const {
}

ButtonZigZag::ButtonZigZag(const Picture& pic)
        : Button{pic} {
    //    buttonPicture.updateState();
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
