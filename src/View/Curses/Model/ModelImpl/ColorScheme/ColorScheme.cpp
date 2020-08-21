#include "View/Curses/Model/ModelImpl/ColorScheme/ColorScheme.hpp"

namespace viewCurses {

namespace {

    schemeImpl getScheme_BASE() {
        schemeImpl scheme;
        scheme.WOW = 100;
        scheme.WOB = 101;
        scheme.BOW = 102;
        scheme.BOB = 103;
        scheme.CELL_WHITE = 200;
        scheme.CELL_BLACK = 201;
        scheme.CELL_WHITE_ACTIVE = 202;
        scheme.CELL_BLACK_ACTIVE = 203;
        scheme.CELL_WHITE_CURRENT = 204;
        scheme.CELL_BLACK_CURRENT = 205;
        scheme.CELL_WHITE_SELECTED = 206;
        scheme.CELL_BLACK_SELECTED = 207;
        scheme.CELL_WHITE_PREVIOUS_FROM = 208;
        scheme.CELL_BLACK_PREVIOUS_FROM = 209;
        scheme.CELL_WHITE_PREVIOUS_TO = 210;
        scheme.CELL_BLACK_PREVIOUS_TO = 211;
        scheme.CELL_BORDER = 220;
        scheme.LETTER_BLACK = 221;
        scheme.LETTER_WHITE = 222;

        scheme.BUTTON_DEFAULT_TEXT = 131;
        scheme.BUTTON_DEFAULT_EMPTY = 132;
        scheme.BUTTON_DEFAULT_BORDER = 133;

        scheme.BUTTON_SELECTED_TEXT = 141;
        scheme.BUTTON_SELECTED_EMPTY = 142;
        scheme.BUTTON_SELECTED_BORDER = 143;

        scheme.BUTTON_SET_TEXT = 151;
        scheme.BUTTON_SET_EMPTY = 152;
        scheme.BUTTON_SET_BORDER = 153;

        scheme.HISTORY_MENU_DELIMETER = 161;
        scheme.HISTORY_MENU_FIGURE_LETTER_WHITE = 162;
        scheme.HISTORY_MENU_FIGURE_LETTER_BLACK = 163;
        return scheme;
    }

    schemeImpl getScheme_CLASSIC()
    {
        schemeImpl scheme = getScheme_BASE();
        scheme.COLOR_WHITE_CELL = 187;
        scheme.COLOR_BLACK_CELL = 137;
        scheme.COLOR_WHITE_FIGURE = 231;
        scheme.COLOR_BLACK_FIGURE = 0;
        scheme.COLOR_WHITE_ACTIVE = 82;
        scheme.COLOR_BLACK_ACTIVE = 70;
        scheme.COLOR_WHITE_CURRENT = 123;
        scheme.COLOR_BLACK_CURRENT = 111;
        scheme.COLOR_WHITE_SELECTED = 56;
        scheme.COLOR_BLACK_SELECTED = 55;
        scheme.COLOR_WHITE_PREVIOUS_FROM = 79;
        scheme.COLOR_BLACK_PREVIOUS_FROM = 77;
        scheme.COLOR_WHITE_PREVIOUS_TO = 83;
        scheme.COLOR_BLACK_PREVIOUS_TO = 84;
        scheme.COLOR_WHITE_LETTER = 196;
        scheme.COLOR_BLACK_LETTER = 226;
        scheme.COLOR_FORE_BORDER = 238;
        scheme.COLOR_BACK_BORDER = 241;

        scheme.COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND = 94;
        scheme.COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND = 144;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND = 144;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND = 144;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND = 137;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND = 137;

        scheme.COLOR_BUTTON_SELECTED_TEXT_FOREGROUND = 124;
        scheme.COLOR_BUTTON_SELECTED_TEXT_BACKGROUND = 143;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND = 143;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND = 143;
        scheme.COLOR_BUTTON_SELECTED_BORDER_FOREGROUND = 137;
        scheme.COLOR_BUTTON_SELECTED_BORDER_BACKGROUND = 137;

        scheme.COLOR_BUTTON_SET_TEXT_FOREGROUND = 124;
        scheme.COLOR_BUTTON_SET_TEXT_BACKGROUND = 100;
        scheme.COLOR_BUTTON_SET_EMPTY_FOREGROUND = 100;
        scheme.COLOR_BUTTON_SET_EMPTY_BACKGROUND = 100;
        scheme.COLOR_BUTTON_SET_BORDER_FOREGROUND = 137;
        scheme.COLOR_BUTTON_SET_BORDER_BACKGROUND = 137;

        scheme.COLOR_HISTORY_MENU_DELIMETER = 241;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE = 160;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK = 93;
        return scheme;
    }
    schemeImpl getScheme_DRACULA() {
        schemeImpl scheme = getScheme_BASE();
        scheme.COLOR_WHITE_CELL = 231;
        scheme.COLOR_BLACK_CELL = 237;
        scheme.COLOR_WHITE_FIGURE = 187;
        scheme.COLOR_BLACK_FIGURE = 137;
        scheme.COLOR_WHITE_ACTIVE = 88;
        scheme.COLOR_BLACK_ACTIVE = 88;
        scheme.COLOR_WHITE_CURRENT = 123;
        scheme.COLOR_BLACK_CURRENT = 111;
        scheme.COLOR_WHITE_SELECTED = 56;
        scheme.COLOR_BLACK_SELECTED = 55;
        scheme.COLOR_WHITE_PREVIOUS_FROM = 78;
        scheme.COLOR_BLACK_PREVIOUS_FROM = 76;
        scheme.COLOR_WHITE_PREVIOUS_TO = 79;
        scheme.COLOR_BLACK_PREVIOUS_TO = 77;
        scheme.COLOR_WHITE_LETTER = 196;
        scheme.COLOR_BLACK_LETTER = 226;
        scheme.COLOR_FORE_BORDER = 238;
        scheme.COLOR_BACK_BORDER = 241;

        scheme.COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND = 0;
        scheme.COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND = 255;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND = 255;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND = 255;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND = 52;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND = 52;

        scheme.COLOR_BUTTON_SELECTED_TEXT_FOREGROUND = 255;
        scheme.COLOR_BUTTON_SELECTED_TEXT_BACKGROUND = 237;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND = 237;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND = 237;
        scheme.COLOR_BUTTON_SELECTED_BORDER_FOREGROUND = 52;
        scheme.COLOR_BUTTON_SELECTED_BORDER_BACKGROUND = 52;

        scheme.COLOR_BUTTON_SET_TEXT_FOREGROUND = 255;
        scheme.COLOR_BUTTON_SET_TEXT_BACKGROUND = 88;
        scheme.COLOR_BUTTON_SET_EMPTY_FOREGROUND = 88;
        scheme.COLOR_BUTTON_SET_EMPTY_BACKGROUND = 88;
        scheme.COLOR_BUTTON_SET_BORDER_FOREGROUND = 52;
        scheme.COLOR_BUTTON_SET_BORDER_BACKGROUND = 52;

        scheme.COLOR_HISTORY_MENU_DELIMETER = 241;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE = 231;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK = 237;
        return scheme;
    }
    schemeImpl getScheme_SNOW_BLUE() {
        schemeImpl scheme = getScheme_BASE();
        scheme.COLOR_WHITE_CELL = 195;
        scheme.COLOR_BLACK_CELL = 117;
        scheme.COLOR_WHITE_FIGURE = 43;
        scheme.COLOR_BLACK_FIGURE = 0;
        scheme.COLOR_WHITE_ACTIVE = 215;
        scheme.COLOR_BLACK_ACTIVE = 215;
        scheme.COLOR_WHITE_CURRENT = 26;
        scheme.COLOR_BLACK_CURRENT = 25;
        scheme.COLOR_WHITE_SELECTED = 56;
        scheme.COLOR_BLACK_SELECTED = 55;
        scheme.COLOR_WHITE_PREVIOUS_FROM = 221;
        scheme.COLOR_BLACK_PREVIOUS_FROM = 222;
        scheme.COLOR_WHITE_PREVIOUS_TO = 221;
        scheme.COLOR_BLACK_PREVIOUS_TO = 222;
        scheme.COLOR_WHITE_LETTER = 196;
        scheme.COLOR_BLACK_LETTER = 226;
        scheme.COLOR_FORE_BORDER = 238;
        scheme.COLOR_BACK_BORDER = 241;

        scheme.COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND = 105;
        scheme.COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND = 195;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND = 195;
        scheme.COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND = 195;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND = 117;
        scheme.COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND = 117;

        scheme.COLOR_BUTTON_SELECTED_TEXT_FOREGROUND = 231;
        scheme.COLOR_BUTTON_SELECTED_TEXT_BACKGROUND = 25;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND = 25;
        scheme.COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND = 25;
        scheme.COLOR_BUTTON_SELECTED_BORDER_FOREGROUND = 117;
        scheme.COLOR_BUTTON_SELECTED_BORDER_BACKGROUND = 117;

        scheme.COLOR_BUTTON_SET_TEXT_FOREGROUND = 231;
        scheme.COLOR_BUTTON_SET_TEXT_BACKGROUND = 93;
        scheme.COLOR_BUTTON_SET_EMPTY_FOREGROUND = 93;
        scheme.COLOR_BUTTON_SET_EMPTY_BACKGROUND = 93;
        scheme.COLOR_BUTTON_SET_BORDER_FOREGROUND = 117;
        scheme.COLOR_BUTTON_SET_BORDER_BACKGROUND = 117;

        scheme.COLOR_HISTORY_MENU_DELIMETER = 241;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE = 187;
        scheme.COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK = 137;
        return scheme;
    }

    void initTheme() {
        const schemeImpl& s = globalColorScheme::scheme();

        init_pair(s.WOW, s.COLOR_BLACK_FIGURE, s.COLOR_WHITE_FIGURE);
        init_pair(s.WOB, s.COLOR_BLACK_FIGURE, s.COLOR_WHITE_FIGURE);
        init_pair(s.BOW, s.COLOR_WHITE_FIGURE, s.COLOR_BLACK_FIGURE);
        init_pair(s.BOB, s.COLOR_WHITE_FIGURE, s.COLOR_BLACK_FIGURE);
        init_pair(s.CELL_WHITE, s.COLOR_WHITE_CELL, s.COLOR_WHITE_CELL);
        init_pair(s.CELL_BLACK, s.COLOR_BLACK_CELL, s.COLOR_BLACK_CELL);
        init_pair(s.CELL_WHITE_ACTIVE, s.COLOR_WHITE_ACTIVE, s.COLOR_WHITE_ACTIVE);
        init_pair(s.CELL_BLACK_ACTIVE, s.COLOR_BLACK_ACTIVE, s.COLOR_BLACK_ACTIVE);
        init_pair(s.CELL_WHITE_CURRENT, s.COLOR_WHITE_CURRENT, s.COLOR_WHITE_CURRENT);
        init_pair(s.CELL_BLACK_CURRENT, s.COLOR_BLACK_CURRENT, s.COLOR_BLACK_CURRENT);
        init_pair(s.CELL_WHITE_SELECTED, s.COLOR_WHITE_SELECTED, s.COLOR_WHITE_SELECTED);
        init_pair(s.CELL_BLACK_SELECTED, s.COLOR_BLACK_SELECTED, s.COLOR_BLACK_SELECTED);
        init_pair(s.CELL_WHITE_PREVIOUS_FROM, s.COLOR_WHITE_PREVIOUS_FROM, s.COLOR_WHITE_PREVIOUS_FROM);
        init_pair(s.CELL_BLACK_PREVIOUS_FROM, s.COLOR_BLACK_PREVIOUS_FROM, s.COLOR_BLACK_PREVIOUS_FROM);
        init_pair(s.CELL_WHITE_PREVIOUS_TO, s.COLOR_WHITE_PREVIOUS_TO, s.COLOR_WHITE_PREVIOUS_TO);
        init_pair(s.CELL_BLACK_PREVIOUS_TO, s.COLOR_BLACK_PREVIOUS_TO, s.COLOR_BLACK_PREVIOUS_TO);
        init_pair(s.CELL_BORDER, s.COLOR_FORE_BORDER, s.COLOR_BACK_BORDER);
        init_pair(s.LETTER_WHITE, s.COLOR_WHITE_LETTER, s.COLOR_WHITE_FIGURE);
        init_pair(s.LETTER_BLACK, s.COLOR_BLACK_LETTER, s.COLOR_BLACK_FIGURE);

        init_pair(s.BUTTON_DEFAULT_TEXT,
                  s.COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND,
                  s.COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND);
        init_pair(s.BUTTON_DEFAULT_EMPTY,
                  s.COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND,
                  s.COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND);
        init_pair(s.BUTTON_DEFAULT_BORDER,
                  s.COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND,
                  s.COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND);

        init_pair(s.BUTTON_SELECTED_TEXT,
                  s.COLOR_BUTTON_SELECTED_TEXT_FOREGROUND,
                  s.COLOR_BUTTON_SELECTED_TEXT_BACKGROUND);
        init_pair(s.BUTTON_SELECTED_EMPTY,
                  s.COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND,
                  s.COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND);
        init_pair(s.BUTTON_SELECTED_BORDER,
                  s.COLOR_BUTTON_SELECTED_BORDER_FOREGROUND,
                  s.COLOR_BUTTON_SELECTED_BORDER_BACKGROUND);

        init_pair(s.BUTTON_SET_TEXT,
                  s.COLOR_BUTTON_SET_TEXT_FOREGROUND,
                  s.COLOR_BUTTON_SET_TEXT_BACKGROUND);
        init_pair(s.BUTTON_SET_EMPTY,
                  s.COLOR_BUTTON_SET_EMPTY_FOREGROUND,
                  s.COLOR_BUTTON_SET_EMPTY_BACKGROUND);
        init_pair(s.BUTTON_SET_BORDER,
                  s.COLOR_BUTTON_SET_BORDER_FOREGROUND,
                  s.COLOR_BUTTON_SET_BORDER_BACKGROUND);

        init_pair(s.HISTORY_MENU_DELIMETER,
                  s.COLOR_HISTORY_MENU_DELIMETER,
                  s.COLOR_HISTORY_MENU_DELIMETER);

        // -1 stay for default background = transparent
        init_pair(s.HISTORY_MENU_FIGURE_LETTER_WHITE, s.COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE, -1);

        init_pair(s.HISTORY_MENU_FIGURE_LETTER_BLACK, s.COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK, -1);

    }
}

schemeImpl globalColorScheme::scheme_;

schemeImpl globalColorScheme::scheme() {
    return scheme_;
}

void globalColorScheme::setScheme(globalColorSchemeType type) {
    switch (type) {
        case globalColorSchemeType::CLASSIC:
            scheme_ = getScheme_CLASSIC();
            break;
        case globalColorSchemeType::DRACULA:
            scheme_ = getScheme_DRACULA();
            break;
        case globalColorSchemeType::SNOW_BLUE:
            scheme_ = getScheme_SNOW_BLUE();
            break;
    }
    initTheme();
}

bool initColorsDone = 0;

void initColors() {
    assert(stdscr);
    if (!initColorsDone) {
        auto rv = freopen("error.txt", "a", stderr);
        static_cast<void>(rv);
        if (!has_colors()) {
            endwin();
            throw ViewBaseException("Your terminal does not support colors");
        }
        use_default_colors();
        start_color();
        cerr << "COLORS:" << COLORS << endl;

        globalColorScheme::setScheme(globalColorSchemeType::SNOW_BLUE);

        initColorsDone = 1;
    }
}

}  // namespace viewCurses
