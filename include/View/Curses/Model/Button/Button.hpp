#ifndef _VIEW_BUTTONS_CURSES_HPP_
#define _VIEW_BUTTONS_CURSES_HPP_

#include <memory>
#include <string>
#include <utility>

#include "View/Curses/Model/ModelImpl/Picture/Picture.hpp"

namespace viewCurses {

class ButtonException : public PictureException {
   public:
    using PictureException::PictureException;
    using PictureException::what;
};

enum class BUTTON_STYLE { NONE, RECTANGLE, ZIGZAG };
enum class BUTTON_MODE{ DEFAULT, SELECTED, SET };

struct buttonColorScheme {
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

struct ButtonNone final : Button {
    explicit ButtonNone(const Picture&);
    void draw(std::pair<size_t, size_t> TL) const override;
};

struct ButtonRectangle final : Button {
    explicit ButtonRectangle(const Picture&,
            size_t upperMargin = 1,
            size_t bottomMargin = 1,
            size_t leftMargin = 5,
            size_t rightMargin = 5
            );
    void draw(std::pair<size_t,size_t> TL) const override;

   private:
    const size_t upperMargin;
    const size_t bottomMargin;
    const size_t leftMargin;   // TODO align here
    const size_t rightMargin;  // TODO align here
};                                 // struct ButtonRectangle

struct ButtonZigZag final : Button {
    explicit ButtonZigZag(const Picture&);
    void draw(std::pair<size_t,size_t> TL) const override;
};  // struct ButtonZigZag

template <typename ...T>
std::shared_ptr<Button> ButtonFactory(const Picture& pic, BUTTON_STYLE style, T&&... args) {
    switch (style) {
        case BUTTON_STYLE::NONE:
            return std::make_unique<ButtonNone>(pic);
            break;
        case BUTTON_STYLE::RECTANGLE:
            return std::make_unique<ButtonRectangle>(pic, std::forward<T>(args)...);
            break;
        case BUTTON_STYLE::ZIGZAG:
            return std::make_unique<ButtonZigZag>(pic);
            break;
    }
    throw ButtonException("ButtonFactory: unknown button style");
}

}  // namespace viewCurses

#endif  // _VIEW_BUTTONS_CURSES_HPP_
