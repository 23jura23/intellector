#include <memory.h>

#include <iostream>

#include "View/Curses/Menu/Menu.hpp"
#include "View/Curses/Menu/Multiplexer/MenuMultiplexer.hpp"
#include "View/Curses/Model/ModelImpl/Init/Init.hpp"

int main() {
    try {
        viewCurses::MenuMultiplexerCurses menuMultiplexer;
        menuMultiplexer.show();
    } catch (const ViewBaseException& e) {
        std::cout << "View error: " << e.what() << std::endl;
        return -1;
    } catch (const viewCurses::MenuException& e) {
        std::cout << "Menu error: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::exception& e) {
        std::cout << "Unknown exception: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cout << "Unknown error" << std::endl;
        return -1;
    }
    return 0;
}
