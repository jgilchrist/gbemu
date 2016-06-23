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
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    void set_pixels(const FrameBuffer& buffer);
    sf::Color get_color(Color color);
};
