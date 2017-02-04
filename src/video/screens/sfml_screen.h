#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen(uint _magnification = 4);
    ~SFMLScreen() override = default;

    void draw(const FrameBuffer& buffer, const BGPalette& bg_palette) override;
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

    void set_pixels(const FrameBuffer& buffer, const BGPalette& bg_palette);
    void set_large_pixel(uint x, uint y, sf::Color color);
    Color get_color(GBColor color, const BGPalette& bg_palette);
    sf::Color get_real_color(Color color);
};
