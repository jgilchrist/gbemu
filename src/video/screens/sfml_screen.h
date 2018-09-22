#pragma once

#include "../../input.h"
#include "../screen.h"

#include <memory>

class SFMLScreen : public Screen {
public:
    SFMLScreen(std::shared_ptr<Input> input, bool _whole_framebuffer=false, uint _magnification = 5);
    ~SFMLScreen() override = default;

    void clear() override;
    void draw(const FrameBuffer& buffer) override;
    void process_events() override;
    bool is_open() override;

private:
    std::shared_ptr<Input> input;

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

    void set_pixels(const FrameBuffer& buffer);
    void set_large_pixel(uint x, uint y, sf::Color color);
    sf::Color get_real_color(Color color);
    GbButton get_gb_button(int keyCode);
};
