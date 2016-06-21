#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen();
    ~SFMLScreen();

    virtual void draw(const FrameBuffer& buffer);
    virtual bool is_open();

private:
    sf::RenderWindow window;

    void set_pixels(sf::Image& image, const FrameBuffer& buffer);
    sf::Color get_color(Color color);
};
