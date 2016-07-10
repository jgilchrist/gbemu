#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen(uint magnification = 4);
    ~SFMLScreen() override = default;

    void draw(const FrameBuffer& buffer) override;
    bool is_open() override;

private:
    const uint magnification;
    const uint width;
    const uint height;
    const uint pixel_size;

    sf::RenderWindow window;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    void set_pixels(const FrameBuffer& buffer);
    void set_large_pixel(uint x, uint y, sf::Color color);
    sf::Color get_color(Color color);
};
