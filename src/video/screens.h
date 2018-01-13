#pragma once

#include "screens/null_screen.h"
#include "screens/sfml_screen.h"

#include "../util/cli.h"

std::shared_ptr<Screen> get_screen(std::shared_ptr<Input> input, Options& options);
std::shared_ptr<Screen> get_screen(std::shared_ptr<Input> input, Options& options) {
    if (options.headless) {
        return std::make_shared<NullScreen>();
    }

    return std::make_shared<SFMLScreen>(input, options.show_full_framebuffer);
}
