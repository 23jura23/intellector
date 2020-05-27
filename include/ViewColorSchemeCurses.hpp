#ifndef _VIEW_COLOR_SCHEME_CURSES_HPP_
#define _VIEW_COLOR_SCHEME_CURSES_HPP_

#include <assert.h>
#include <ncurses.h>

#include <iostream>

#include "ViewBase.hpp"
using std::cerr, std::endl;

namespace viewCurses {

// a little bit strange: defines inside namepsace :)

#define CLASSIC   0
#define DRACULA   1
#define SNOW_BLUE 2

#define COLOR_MODE CLASSIC

//#define CLASSIC
//#define BLACK_AND_WHITE
//#define SNOW_BLUE

#if COLOR_MODE == CLASSIC
    #define COLOR_WHITE_CELL          187
    #define COLOR_BLACK_CELL          137
    #define COLOR_WHITE_FIGURE        231
    #define COLOR_BLACK_FIGURE        0
    #define COLOR_WHITE_ACTIVE        82
    #define COLOR_BLACK_ACTIVE        70
    #define COLOR_WHITE_CURRENT       123
    #define COLOR_BLACK_CURRENT       111
    #define COLOR_WHITE_SELECTED      56
    #define COLOR_BLACK_SELECTED      55
    #define COLOR_WHITE_PREVIOUS_FROM 79
    #define COLOR_BLACK_PREVIOUS_FROM 77
    #define COLOR_WHITE_PREVIOUS_TO   83
    #define COLOR_BLACK_PREVIOUS_TO   84
    #define COLOR_WHITE_LETTER        196
    #define COLOR_BLACK_LETTER        226
    #define COLOR_FORE_BORDER         238
    #define COLOR_BACK_BORDER         241

    #define COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND   94
    #define COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND   144
    #define COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND  144
    #define COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND  144
    #define COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND 137
    #define COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND 137

    #define COLOR_BUTTON_SELECTED_TEXT_FOREGROUND   124
    #define COLOR_BUTTON_SELECTED_TEXT_BACKGROUND   143
    #define COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND  143
    #define COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND  143
    #define COLOR_BUTTON_SELECTED_BORDER_FOREGROUND 137
    #define COLOR_BUTTON_SELECTED_BORDER_BACKGROUND 137

    #define COLOR_BUTTON_SET_TEXT_FOREGROUND   124
    #define COLOR_BUTTON_SET_TEXT_BACKGROUND   100
    #define COLOR_BUTTON_SET_EMPTY_FOREGROUND  100
    #define COLOR_BUTTON_SET_EMPTY_BACKGROUND  100
    #define COLOR_BUTTON_SET_BORDER_FOREGROUND 137
    #define COLOR_BUTTON_SET_BORDER_BACKGROUND 137

    #define COLOR_HISTORY_MENU_DELIMETER 241
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE 160
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK 93
#elif COLOR_MODE == DRACULA
    #define COLOR_WHITE_CELL          231
    #define COLOR_BLACK_CELL          237
    #define COLOR_WHITE_FIGURE        187
    #define COLOR_BLACK_FIGURE        137
    #define COLOR_WHITE_ACTIVE        88
    #define COLOR_BLACK_ACTIVE        88
    #define COLOR_WHITE_CURRENT       123
    #define COLOR_BLACK_CURRENT       111
    #define COLOR_WHITE_SELECTED      56
    #define COLOR_BLACK_SELECTED      55
    #define COLOR_WHITE_PREVIOUS_FROM 78
    #define COLOR_BLACK_PREVIOUS_FROM 76
    #define COLOR_WHITE_PREVIOUS_TO   79
    #define COLOR_BLACK_PREVIOUS_TO   77
    #define COLOR_WHITE_LETTER        196
    #define COLOR_BLACK_LETTER        226
    #define COLOR_FORE_BORDER         238
    #define COLOR_BACK_BORDER         241

    #define COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND   0
    #define COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND   255
    #define COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND  255
    #define COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND  255
    #define COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND 52
    #define COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND 52

    #define COLOR_BUTTON_SELECTED_TEXT_FOREGROUND   255
    #define COLOR_BUTTON_SELECTED_TEXT_BACKGROUND   237
    #define COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND  237
    #define COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND  237
    #define COLOR_BUTTON_SELECTED_BORDER_FOREGROUND 52
    #define COLOR_BUTTON_SELECTED_BORDER_BACKGROUND 52
    
    #define COLOR_BUTTON_SET_TEXT_FOREGROUND   255
    #define COLOR_BUTTON_SET_TEXT_BACKGROUND   88
    #define COLOR_BUTTON_SET_EMPTY_FOREGROUND  88
    #define COLOR_BUTTON_SET_EMPTY_BACKGROUND  88
    #define COLOR_BUTTON_SET_BORDER_FOREGROUND 52
    #define COLOR_BUTTON_SET_BORDER_BACKGROUND 52

    #define COLOR_HISTORY_MENU_DELIMETER 241
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE 231
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK 237
#elif COLOR_MODE == SNOW_BLUE
    #define COLOR_WHITE_CELL          187
    #define COLOR_BLACK_CELL          137
    #define COLOR_WHITE_FIGURE        231
    #define COLOR_BLACK_FIGURE        0
    #define COLOR_WHITE_ACTIVE        82
    #define COLOR_BLACK_ACTIVE        70
    #define COLOR_WHITE_CURRENT       123
    #define COLOR_BLACK_CURRENT       111
    #define COLOR_WHITE_SELECTED      56
    #define COLOR_BLACK_SELECTED      55
    #define COLOR_WHITE_PREVIOUS_FROM 79
    #define COLOR_BLACK_PREVIOUS_FROM 77
    #define COLOR_WHITE_PREVIOUS_TO   83
    #define COLOR_BLACK_PREVIOUS_TO   84
    #define COLOR_WHITE_LETTER        196
    #define COLOR_BLACK_LETTER        226
    #define COLOR_FORE_BORDER         238
    #define COLOR_BACK_BORDER         241

    #define COLOR_BUTTON_DEFAULT_TEXT_FOREGROUND   105
    #define COLOR_BUTTON_DEFAULT_TEXT_BACKGROUND   195
    #define COLOR_BUTTON_DEFAULT_EMPTY_FOREGROUND  195
    #define COLOR_BUTTON_DEFAULT_EMPTY_BACKGROUND  195
    #define COLOR_BUTTON_DEFAULT_BORDER_FOREGROUND 117
    #define COLOR_BUTTON_DEFAULT_BORDER_BACKGROUND 117

    #define COLOR_BUTTON_SELECTED_TEXT_FOREGROUND   231
    #define COLOR_BUTTON_SELECTED_TEXT_BACKGROUND   25
    #define COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND  25
    #define COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND  25
    #define COLOR_BUTTON_SELECTED_BORDER_FOREGROUND 117
    #define COLOR_BUTTON_SELECTED_BORDER_BACKGROUND 117
    
    #define COLOR_BUTTON_SELECTED_TEXT_FOREGROUND   231
    #define COLOR_BUTTON_SELECTED_TEXT_BACKGROUND   93
    #define COLOR_BUTTON_SELECTED_EMPTY_FOREGROUND  93
    #define COLOR_BUTTON_SELECTED_EMPTY_BACKGROUND  93
    #define COLOR_BUTTON_SELECTED_BORDER_FOREGROUND 117
    #define COLOR_BUTTON_SELECTED_BORDER_BACKGROUND 117

    #define COLOR_HISTORY_MENU_DELIMETER 241
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_WHITE 187
    #define COLOR_HISTORY_MENU_FIGURE_LETTER_BLACK 137
#endif

#define WOW 100  // White On White
#define WOB 101  // White On Black
#define BOW 102  // Black On White
#define BOB 103  // Black On Black
// #define WOA 104  // White On Active
// #define BOA 105  // Black On Active
#define CELL_WHITE               200  // INACTIVE
#define CELL_BLACK               201  // INACTIVE
#define CELL_WHITE_ACTIVE        202  // ACTIVE
#define CELL_BLACK_ACTIVE        203  // ACTIVE
#define CELL_WHITE_CURRENT       204  // CURRENT
#define CELL_BLACK_CURRENT       205  // CURRENT
#define CELL_WHITE_SELECTED      206  // SELECTED
#define CELL_BLACK_SELECTED      207  // SELECTED
#define CELL_WHITE_PREVIOUS_FROM 208  // PREVIOUS_FROM
#define CELL_BLACK_PREVIOUS_FROM 209  // PREVIOUS_FROM
#define CELL_WHITE_PREVIOUS_TO   210  // PREVIOUS_TO
#define CELL_BLACK_PREVIOUS_TO   211  // PREVIOUS_TO
#define CELL_BORDER              220
#define LETTER_BLACK             221
#define LETTER_WHITE             222

#define BUTTON_DEFAULT_TEXT   131
#define BUTTON_DEFAULT_EMPTY  132
#define BUTTON_DEFAULT_BORDER 133

#define BUTTON_SELECTED_TEXT   141
#define BUTTON_SELECTED_EMPTY  142
#define BUTTON_SELECTED_BORDER 143

#define BUTTON_SET_TEXT   151
#define BUTTON_SET_EMPTY  152
#define BUTTON_SET_BORDER 153

#define HISTORY_MENU_DELIMETER 161
#define HISTORY_MENU_FIGURE_LETTER_WHITE 162
#define HISTORY_MENU_FIGURE_LETTER_BLACK 163

extern bool initColorsDone;
void initColors();

}  // namespace viewCurses

#endif
