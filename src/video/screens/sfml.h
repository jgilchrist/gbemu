#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen();

    virtual void draw(FrameBuffer& buffer);
    virtual bool is_open();

private:
    sf::RenderWindow window;
};
