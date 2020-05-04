#ifndef _VIEW_BUTTONS_CURSES_HPP_
#define _VIEW_BUTTONS_CURSES_HPP_

#include <memory>
#include <string>

#include "ViewPictureCurses.hpp"

namespace viewCurses {

class ButtonException : public PictureException {
   public:
    using PictureException::PictureException;
    using PictureException::what;
};

enum class BUTTON_STYLE { RECTANGLE, ZIGZAG };
enum class BUTTON_MODE{ DEFAULT, SELECTED };

struct buttonColorScheme /* : localColorScheme */ {
    int text{};
    int empty{};
    int border{};
};

struct Button {
    Button(const Picture& pic);
    virtual const Picture& getPicture() const;
    virtual void draw(std::pair<size_t, size_t> TL) const = 0;
    virtual void setMode(BUTTON_MODE);

   protected:
    Picture buttonPicture;
    buttonColorScheme colorScheme;
    
};  // struct Button

struct ButtonRectangle final : Button {
    explicit ButtonRectangle(const Picture&);
    void draw(std::pair<size_t,size_t> TL) const override;

   private:
    const size_t upperMargin = 1;
    const size_t bottomMargin = 1;
    const size_t leftMargin = 5;   // TODO align here
    const size_t rightMargin = 5;  // TODO align here
};                                 // struct ButtonRectangle

struct ButtonZigZag final : Button {
    explicit ButtonZigZag(const Picture&);
    void draw(std::pair<size_t,size_t> TL) const override;
};  // struct ButtonZigZag

std::shared_ptr<Button> ButtonFactory(const Picture&, BUTTON_STYLE);

}  // namespace viewCurses

#endif  // _VIEW_BUTTONS_CURSES_HPP_
