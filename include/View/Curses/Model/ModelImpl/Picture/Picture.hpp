#ifndef _PICTURE_CURSES_HPP_
#define _PICTURE_CURSES_HPP_

#include <string>
#include <unordered_set>
#include <vector>

#include "View/Base/Base.hpp"

namespace viewCurses {

class PictureException : public ViewBaseException {
   public:
    using ViewBaseException::ViewBaseException;
    using ViewBaseException::what;
};

struct Picture {
    explicit Picture(std::string ignoredChars = "\x1E",
                     std::string backgroundChars = "\x1F");
    explicit Picture(const std::vector<std::string>&,
                     std::string ignoredChars = "\x1E",
                     std::string backgroundChars = "\x1F");
    explicit Picture(std::istream& is);
    //    Picture(const Picture&, bool attrOnly = 0);
    size_t maxHeight() const;
    size_t maxWidth() const;
    char& operator()(size_t y, size_t x);  // TODO why the fuck isn't it []? only for line, no need for separate operator for x y, because string has its own []
    const char& operator()(size_t y, size_t x) const;
    std::string& operator()(size_t y);
    const std::string& operator()(size_t y) const;
    void insertLine(size_t, const std::string&);
    void pushBackLine(const std::string&);
    void addIgnoredChar(char);
    void removeIgnoredChar(char c);
    bool isIgnoredChar(char c) const;
    std::string getIgnoredChars() const;

    void addBackgroundChar(char);
    void removeBackgroundChar(char c);
    bool isBackgroundChar(char c) const;
    std::string getBackgroundChars() const;
    // getIgnoredChars?
    void clearPictureContent();  // keeps only the attributes like ignoredChars_
                                 //    void updateState();

    std::vector<std::string>::iterator begin();
    std::vector<std::string>::iterator end();
    std::vector<std::string>::const_iterator begin() const;
    std::vector<std::string>::const_iterator end() const;

    std::vector<std::string> picture_;
    std::unordered_set<char> ignoredChars_, backgroundChars_;
};  // struct Picture

}  // namespace viewCurses

#endif  // _PICTURE_CURSES_HPP_
