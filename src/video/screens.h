#pragma once

#include "screens/null_screen.h"
#include "screens/sfml_screen.h"

std::shared_ptr<Screen> get_screen(bool headless, bool show_full_framebuffer);
std::shared_ptr<Screen> get_screen(bool headless, bool show_full_framebuffer) {
    if (headless) {
        return std::make_shared<NullScreen>();
    }

    return std::make_shared<SFMLScreen>(show_full_framebuffer);
}
