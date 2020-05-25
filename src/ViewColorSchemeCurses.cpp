#include "ViewColorSchemeCurses.hpp"

namespace viewCurses {

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

        init_pair(WOW, COLOR_BLACK_FIGURE, COLOR_WHITE_FIGURE);
        init_pair(WOB, COLOR_BLACK_FIGURE, COLOR_WHITE_FIGURE);
        init_pair(BOW, COLOR_WHITE_FIGURE, COLOR_BLACK_FIGURE);
        init_pair(BOB, COLOR_WHITE_FIGURE, COLOR_BLACK_FIGURE);
        init_pair(CELL_WHITE, COLOR_WHITE_CELL, COLOR_WHITE_CELL);
        init_pair(CELL_BLACK, COLOR_BLACK_CELL, COLOR_BLACK_CELL);
        init_pair(CELL_WHITE_ACTIVE, COLOR_WHITE_ACTIVE, COLOR_WHITE_ACTIVE);
        init_pair(CELL_BLACK_ACTIVE, COLOR_BLACK_ACTIVE, COLOR_BLACK_ACTIVE);
        init_pair(CELL_WHITE_CURRENT, COLOR_WHITE_CURRENT, COLOR_WHITE_CURRENT);
        init_pair(CELL_BLACK_CURRENT, COLOR_BLACK_CURRENT, COLOR_BLACK_CURRENT);
        init_pair(CELL_WHITE_SELECTED, COLOR_WHITE_SELECTED, COLOR_WHITE_SELECTED);
        init_pair(CELL_BLACK_SELECTED, COLOR_BLACK_SELECTED, COLOR_BLACK_SELECTED);
        init_pair(CELL_WHITE_PREVIOUS_FROM, COLOR_WHITE_PREVIOUS_FROM, COLOR_WHITE_PREVIOUS_FROM);
        init_pair(CELL_BLACK_PREVIOUS_FROM, COLOR_BLACK_PREVIOUS_FROM, COLOR_BLACK_PREVIOUS_FROM);
        init_pair(CELL_WHITE_PREVIOUS_TO, COLOR_WHITE_PREVIOUS_TO, COLOR_WHITE_PREVIOUS_TO);
        init_pair(CELL_BLACK_PREVIOUS_TO, COLOR_BLACK_PREVIOUS_TO, COLOR_BLACK_PREVIOUS_TO);
        init_pair(CELL_BORDER, COLOR_FORE_BORDER, COLOR_BACK_BORDER);
        init_pair(LETTER_WHITE, COLOR_WHITE_LETTER, COLOR_WHITE_FIGURE);
        init_pair(LETTER_BLACK, COLOR_BLACK_LETTER, COLOR_BLACK_FIGURE);

        init_pair(BUTTON_DEFAULT_TEXT,
                  COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND,
                  COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND);
        init_pair(BUTTON_DEFAULT_EMPTY,
                  COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND,
                  COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND);
        init_pair(BUTTON_DEFAULT_BORDER,
                  COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND,
                  COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND);

        init_pair(BUTTON_SELECTED_TEXT,
                  COLOR_BUTTON_SELECTED_TEXT_FOREGROUND,
                  COLOR_BUTTON_SELECTED_TEXT_BACKGROUND);
        init_pair(BUTTON_SELECTED_EMPTY,
                  COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND,
                  COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND);
        init_pair(BUTTON_SELECTED_BORDER,
                  COLOR_BUTTON_SELECTED_BORDER_FOREGROUND,
                  COLOR_BUTTON_SELECTED_BORDER_BACKGROUND);

        init_pair(BUTTON_SET_TEXT,
                  COLOR_BUTTON_SET_TEXT_FOREGROUND,
                  COLOR_BUTTON_SET_TEXT_BACKGROUND);
        init_pair(BUTTON_SET_EMPTY,
                  COLOR_BUTTON_SET_EMPTY_FOREGROUND,
                  COLOR_BUTTON_SET_EMPTY_BACKGROUND);
        init_pair(BUTTON_SET_BORDER,
                  COLOR_BUTTON_SET_BORDER_FOREGROUND,
                  COLOR_BUTTON_SET_BORDER_BACKGROUND);

        init_pair(HISTORY_MENU_DELIMETER,
                  COLOR_HISTORY_MENU_DELIMETER,
                  COLOR_HISTORY_MENU_DELIMETER);

        // -1 stay for default background = transparent
        init_pair(HISTORY_MENU_FIGURE_LETTER_WHITE, COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE, -1);

        init_pair(HISTORY_MENU_FIGURE_LETTER_BLACK, COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK, -1);

        initColorsDone = 1;
    }
}

}  // namespace viewCurses
