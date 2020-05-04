#include "ViewPictureCurses.hpp"

#include <string>

namespace viewCurses {

Picture::Picture(std::string ignoredChars, std::string backgroundChars) {
    for (auto c : ignoredChars) addIgnoredChar(c);
    for (auto c : backgroundChars) addBackgroundChar(c);
    //    updateState();
}

Picture::Picture(const std::vector<std::string>& picture,
                 std::string ignoredChars,
                 std::string backgroundChars)
        : picture_{picture} {
    for (auto c : ignoredChars) addIgnoredChar(c);
    for (auto c : backgroundChars) addBackgroundChar(c);
    //    updateState();
}

//Picture::Picture(const Picture& pic/*, bool attrOnly*/) {
////    if (!attrOnly) {
//        picture_ = pic.picture_;
////    }
//    ignoredChars_ = pic.ignoredChars_;
//    updateState();
//}

size_t Picture::maxHeight() const {
    return picture_.size();
}

size_t Picture::maxWidth() const {
    size_t maxWidth_ = 0;
    for (size_t i = 0; i < maxHeight(); ++i) maxWidth_ = std::max(maxWidth_, picture_[i].size());
    return maxWidth_;
}

// char& Picture::operator()(size_t y, size_t x) {
//     return const_cast<Picture const&>(*this).operator()(y, x);
// }
// failed to do const and non-const version
//

char& Picture::operator()(size_t y, size_t x) {
    if (picture_.size() <= y || picture_[y].size() <= x) {
        std::string what = "operator()(size_t, size_t): "
                           "Coordinates out of bound. "
                           "y = " +
                           std::to_string(y) + ", x = " + std::to_string(x);
        throw PictureException(what.c_str());
    }
    return picture_[y][x];
}

const char& Picture::operator()(size_t y, size_t x) const {
    if (picture_.size() <= y || picture_[y].size() <= x) {
        std::string what = "operator()(size_t, size_t): "
                           "Coordinates out of bound. "
                           "y = " +
                           std::to_string(y) + ", x = " + std::to_string(x);
        throw PictureException(what.c_str());
    }
    return picture_[y][x];
}

std::string& Picture::operator()(size_t y) {
    if (picture_.size() <= y) {
        std::string what = "operator()(size_t, size_t): "
                           "Index out of bound. "
                           "y = " +
                           std::to_string(y);
        throw PictureException(what.c_str());
    }
    return picture_[y];
}

const std::string& Picture::operator()(size_t y) const {
    if (picture_.size() <= y) {
        std::string what = "operator()(size_t, size_t): "
                           "Index out of bound. "
                           "y = " +
                           std::to_string(y);
        throw PictureException(what.c_str());
    }
    return picture_[y];
}

void Picture::addIgnoredChar(char c) {
    ignoredChars_.insert(c);
}

void Picture::removeIgnoredChar(char c) {
    ignoredChars_.erase(c);
}

bool Picture::isIgnoredChar(char c) const {
    return ignoredChars_.count(c);
}

std::string Picture::getIgnoredChars() const {
    std::string ignoredChars;
    for (auto i : ignoredChars_) ignoredChars += i;
    return ignoredChars;
}

void Picture::addBackgroundChar(char c) {
    backgroundChars_.insert(c);
}

void Picture::removeBackgroundChar(char c) {
    backgroundChars_.erase(c);
}

bool Picture::isBackgroundChar(char c) const {
    return backgroundChars_.count(c);
}

std::string Picture::getBackgroundChars() const {
    std::string BackgroundChars;
    for (auto i : backgroundChars_) BackgroundChars += i;
    return BackgroundChars;
}

void Picture::insertLine(size_t i, const std::string& newLine) {
    if (picture_.size() < i) {
        std::string what = "insertLine()(size_t, std::string): "
                           "Index out of bound. "
                           "i = " +
                           std::to_string(i);
        throw PictureException(what.c_str());
    }
    picture_.insert(picture_.begin() + i, newLine);
}

void Picture::pushBackLine(const std::string& newLine) {
    picture_.push_back(newLine);
}

void Picture::clearPictureContent() {
    picture_.clear();
}

//void Picture::updateState() {
//    maxHeight_ = picture_.size();
//    maxWidth_ = 0;
//    for (size_t i = 0; i < maxHeight_; ++i) maxWidth_ = std::max(maxWidth_, picture_[i].size());
//}

std::vector<std::string>::iterator Picture::begin() {
    return picture_.begin();
}

std::vector<std::string>::iterator Picture::end() {
    return picture_.end();
}

std::vector<std::string>::const_iterator Picture::begin() const {
    return picture_.cbegin();
}

std::vector<std::string>::const_iterator Picture::end() const {
    return picture_.cend();
}

}  // namespace viewCurses
