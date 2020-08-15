#ifndef _VIEW_INIT_CURSES_HPP_
#define _VIEW_INIT_CURSES_HPP_

namespace viewCurses {
extern int initCursesDone;
void initCurses();
void terminateCurses();
void terminateAllCurses();
}  // namespace viewCurses

#endif  // _VIEW_INIT_CURSES_HPP_
