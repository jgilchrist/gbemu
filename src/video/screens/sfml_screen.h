#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen(uint _magnification = 4, bool _whole_framebuffer=false);
    ~SFMLScreen() override = default;

    void draw(const FrameBuffer& buffer, const uint scrollx, const uint scrolly, const BGPalette& bg_palette) override;
    bool is_open() override;

private:
    const uint magnification;
    bool whole_framebuffer;

    const uint logical_width;
    const uint logical_height;
    const uint width;
    const uint height;
    const uint pixel_size;

    sf::RenderWindow window;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    void set_pixels(const FrameBuffer& buffer, const uint scroll_x, const uint scroll_y, const BGPalette& bg_palette);
    void set_large_pixel(uint x, uint y, sf::Color color);
    Color get_color(GBColor color, const BGPalette& bg_palette);
    sf::Color get_real_color(Color color);
};
