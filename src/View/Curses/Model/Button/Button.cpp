#include "View/Curses/Model/Button/Button.hpp"

#include <assert.h>
#include <ncurses.h>

#include "View/Curses/Model/ModelImpl/ColorScheme/ColorScheme.hpp"

using std::string;
namespace viewCurses {

Button::Button(const Picture& pic)
        : buttonPicture{pic}
{
    setMode(BUTTON_MODE::DEFAULT);
}

const Picture& Button::getPicture() const {
    return buttonPicture;
}

void Button::setMode(BUTTON_MODE mode) {
    switch (mode) {
        case BUTTON_MODE::DEFAULT:
            colorScheme.text = globalColorScheme::scheme().BUTTON_DEFAULT_TEXT;
            colorScheme.empty = globalColorScheme::scheme().BUTTON_DEFAULT_EMPTY;
            colorScheme.border = globalColorScheme::scheme().BUTTON_DEFAULT_BORDER;
            return;
        case BUTTON_MODE::SELECTED:
            colorScheme.text = globalColorScheme::scheme().BUTTON_SELECTED_TEXT;
            colorScheme.empty = globalColorScheme::scheme().BUTTON_SELECTED_EMPTY;
            colorScheme.border = globalColorScheme::scheme().BUTTON_SELECTED_BORDER;
            return;
        case BUTTON_MODE::SET:
            colorScheme.text = globalColorScheme::scheme().BUTTON_SET_TEXT;
            colorScheme.empty = globalColorScheme::scheme().BUTTON_SET_EMPTY;
            colorScheme.border = globalColorScheme::scheme().BUTTON_SET_BORDER;
            return;
    }
    throw ButtonException("Incorrect button mode " + std::to_string(static_cast<int>(mode)));
}

ButtonNone::ButtonNone(const Picture& pic)
        : Button{pic} {
}

void ButtonNone::draw(std::pair<size_t, size_t> TL) const {
    assert(stdscr != 0);
    assert(initColorsDone);
    move(TL.second, TL.first);

    char c;

    if (buttonPicture.maxHeight()) {
        TL.second++;
        move(TL.second, TL.first);

        for (size_t i = 0; i < buttonPicture.maxHeight(); ++i) {
            if (buttonPicture(i).size()) {
                for (size_t j = 0; j < buttonPicture(i).size(); ++j) {
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
            }
            TL.second++;
            move(TL.second, TL.first);
        }
    }
}

ButtonRectangle::ButtonRectangle(const Picture& pic,
                                 size_t upperMargin_,
                                 size_t bottomMargin_,
                                 size_t leftMargin_,
                                 size_t rightMargin_)
        : Button{pic}
        , upperMargin{upperMargin_}
        , bottomMargin{bottomMargin_}
        , leftMargin{leftMargin_}
        , rightMargin{rightMargin_} {
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

}  // namespace viewCurses
