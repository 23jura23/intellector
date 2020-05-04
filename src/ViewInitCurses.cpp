#include "ViewInitCurses.hpp"

#include <ncurses.h>

#include "ViewColorSchemeCurses.hpp"

namespace viewCurses {
int initCursesDone = 0;

void initCurses() {
    if (!initCursesDone) {
        initscr();
        initColors();  // ViewColorSchemeCurses
        curs_set(0);
        noecho();

        keypad(stdscr, true);
        //    UPD: makes ESC work only if pressed twice. if one comments the line above, then arrow keys will not work
        //    otherwise ESC does not work, see
        //    https://www.daniweb.com/programming/software-development/threads/259439/keycode-of-esc-in-curses-h
        //    other solutions: nocbreak(); or timeout(0); or not using ESC to cancel
    }
    initCursesDone++;
}

void terminateCurses() {
    if (initCursesDone == 1) {
        use_default_colors();
        endwin();
        initCursesDone = 0;
    } else if (initCursesDone <= 0) {
        assert(0);  // TODO own exception?
    } else {
        initCursesDone--;
    }
}

}  // namespace viewCurses
