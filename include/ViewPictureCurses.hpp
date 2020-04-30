#ifndef _PICTURE_CURSES_HPP_
#define _PICTURE_CURSES_HPP_

#include <unordered_set>
#include <vector>
#include <string>

#include "ViewBase.hpp"

namespace viewCurses {

class PictureException : ViewBaseException {
    using ViewBaseException::ViewBaseException;
    using ViewBaseException::what;
};

struct Picture {
    explicit Picture(std::string ignoredChars = "`");
    explicit Picture(const std::vector<std::string>&, std::string ignoredChars = "`");
    Picture(const Picture&, bool attrOnly = 0);
    size_t maxHeight() const;
    size_t maxWidth() const;
    char& operator()(size_t y, size_t x);
    std::string& operator()(size_t y);
    //    char operator()(size_t y, size_t x) const;
    void insertLine(size_t, const std::string&);
    void pushBackLine(const std::string&);
    void addIgnoredChar(char);
    void removeIgnoredChar(char c);
    std::string getIgnoredChars() const;
    // getIgnoredChars?
    void updateState();

    std::vector<std::string>::iterator begin();
    std::vector<std::string>::iterator end();
    std::vector<std::string>::const_iterator begin() const;
    std::vector<std::string>::const_iterator end() const;

    std::vector<std::string> picture_;
    std::unordered_set<char> ignoredChars_;
    size_t maxHeight_, maxWidth_;
};  // struct Picture

}  // namespace viewCurses

#endif  // _PICTURE_CURSES_HPP_
